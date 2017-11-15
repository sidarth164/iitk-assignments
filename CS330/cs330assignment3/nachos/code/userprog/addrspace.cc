// addrspace.cc 
//  Routines to manage address spaces (executing user programs).
//
//  In order to run a user program, you must:
//
//  1. link with the -N -T 0 option 
//  2. run coff2noff to convert the object file to Nachos format
//      (Nachos object code format is essentially just a simpler
//      version of the UNIX executable object code format)
//  3. load the NOFF file into the Nachos file system
//      (if you haven't implemented the file system yet, you
//      don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"

//----------------------------------------------------------------------
// SwapHeader
//  Do little endian to big endian conversion on the bytes in the 
//  object file header, in case the file was generated on a little
//  endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
    noffH->noffMagic = WordToHost(noffH->noffMagic);
    noffH->code.size = WordToHost(noffH->code.size);
    noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
    noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
    noffH->initData.size = WordToHost(noffH->initData.size);
    noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
    noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
    noffH->uninitData.size = WordToHost(noffH->uninitData.size);
    noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
    noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// ProcessAddressSpace::ProcessAddressSpace
//  Create an address space to run a user program.
//  Load the program from a file "executable", and set everything
//  up so that we can start executing user instructions.
//
//  Assumes that the object code file is in NOFF format.
//
//  First, set up the translation from program memory to physical 
//  memory.  For now, this is really simple (1:1), since we are
//  only uniprogramming, and we have a single unsegmented page table
//
//  "executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

ProcessAddressSpace::ProcessAddressSpace(char* filename)
{
    NoffHeader noffH;
    unsigned int i, size;
    unsigned vpn, offset;
    TranslationEntry *entry;
    unsigned int pageFrame;
    
    fileName = filename;
    openedExecutable = fileSystem->Open(fileName);
    if(openedExecutable==NULL){
        DEBUG('I',"Unable to open file from LaunchUserProcess\n");
        printf("Unable to open the file %s\n",filename);
        ASSERT(FALSE);
    }

    openedExecutable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
        (WordToHost(noffH.noffMagic) == NOFFMAGIC))
        SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
            + UserStackSize;    // we need to increase the size
                        // to leave room for the stack
    numVirtualPages = divRoundUp(size, PageSize);
    size = numVirtualPages * PageSize;

    backUp = new char[size];

//    ASSERT(numVirtualPages+numPagesAllocated <= NumPhysPages);        // check we're not trying
                                        // to run anything too big --
                                        // at least until we have
                                        // virtual memory

    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
                    numVirtualPages, size);
// first, set up the translation 
    KernelPageTable = new TranslationEntry[numVirtualPages];
    for (i = 0; i < numVirtualPages; i++) {
    KernelPageTable[i].virtualPage = i;
    KernelPageTable[i].physicalPage = -1;
    KernelPageTable[i].valid = FALSE;
    KernelPageTable[i].use = FALSE;
    KernelPageTable[i].dirty = FALSE;
    KernelPageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
                    // a separate page, we could set its 
                    // pages to be read-only
    KernelPageTable[i].shared = FALSE;  // if the page is SHARED then TRUE else FALSE 
    KernelPageTable[i].inBackUp = FALSE; 
    }
// zero out the entire address space, to zero the unitialized data segment 
// and the stack segment
    //bzero(&machine->mainMemory[numPagesAllocated*PageSize], size);
 
    //numPagesAllocated += numVirtualPages;

// then, copy in the code and data segments into memory
//    if (noffH.code.size > 0) {
//        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
//          noffH.code.virtualAddr, noffH.code.size);
//        //vpn = noffH.code.virtualAddr/PageSize;
//        //offset = noffH.code.virtualAddr%PageSize;
//        //entry = &KernelPageTable[vpn];
//        //pageFrame = entry->physicalPage;
//        executable->ReadAt(backUp,noffH.code.size, noffH.code.inFileAddr);
//    }
//    if (noffH.initData.size > 0) {
//        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
//          noffH.initData.virtualAddr, noffH.initData.size);
//        //vpn = noffH.initData.virtualAddr/PageSize;
//        //offset = noffH.initData.virtualAddr%PageSize;
//        //entry = &KernelPageTable[vpn];
//        //pageFrame = entry->physicalPage;
//        executable->ReadAt(backUp,noffH.initData.size, noffH.initData.inFileAddr);
//    }

}

//----------------------------------------------------------------------
// ProcessAddressSpace::ProcessAddressSpace (ProcessAddressSpace*) is called by a forked thread.
//      We need to duplicate the address space of the parent.
//----------------------------------------------------------------------

ProcessAddressSpace::ProcessAddressSpace(ProcessAddressSpace *parentSpace)
{
    numVirtualPages = parentSpace->GetNumPages();
    unsigned i, size = numVirtualPages * PageSize;

    //ASSERT(numVirtualPages+numPagesAllocated <= NumPhysPages);                // check we're not trying
                                                                                // to run anything too big --
                                                                                // at least until we have
                                                                                // virtual memory

    DEBUG('f',"Called ProcessAddressSpace Constructor to assign space to child\n");
    DEBUG('a', "Initializing address space, num pages %d, size %d\n",numVirtualPages, size);
    backUp=new char[size];
    fileName = parentSpace->fileName;
    openedExecutable = fileSystem->Open(fileName);
    if(openedExecutable == NULL){
        DEBUG('I',"Unable to open file from fork\n");
        printf("Unable to open file %s\n",openedExecutable);
        ASSERT(FALSE);
    }
    // first, set up the translation
//    TranslationEntry* parentPageTable = parentSpace->GetPageTable();
    KernelPageTable = new TranslationEntry[numVirtualPages];
//    for (i = 0; i < numVirtualPages; i++) {
//    if(parentPageTable[i].valid){
//        if(parentPageTable[i].shared == FALSE){
//            DEBUG('f',"vpn[%d] viz. valid AND not shared - to be copied from parent to child\n",i);
//            int pid = currentThread->GetPID();
//            currentThread->SortedInsertInWaitQueue(stats->totalTicks);
//            IntStatus oldLevel = interrupt->SetLevel(IntOff);
//            KernelPageTable[i].virtualPage = i;
//            DEBUG('f',"Asking for a free page\n");
//            int ppfn =  GetNextPhysPage(parentPageTable[i].physicalPage);
//            DEBUG('f',"Got a free page %d\n",ppfn);
//            KernelPageTable[i].physicalPage = ppfn;           
//            physPageIsFree[ppfn] = FALSE;
//            physPageVPN[ppfn]=i;
//            DEBUG('R',"**FORK CALL CONSTRUCTOR**\nAllocating pid[%d] to ppfn[%d]\nIt has physical page %d\n",child_pid,ppfn,KernelPageTable[i].physicalPage);
//            physPagePID[ppfn]=child_pid;
//
//
//            for(int j=0;j<PageSize;j++){
//                DEBUG('r',"Copying data from parent to child\n");
//                machine->mainMemory[ppfn*PageSize+j] = machine->mainMemory[parentPageTable[i].physicalPage*PageSize+j];
//                DEBUG('r',"SUCCESS!!\n");
//            }
//            
//            KernelPageTable[i].valid = parentPageTable[i].valid;
//            KernelPageTable[i].use = parentPageTable[i].use;
//            KernelPageTable[i].dirty = parentPageTable[i].dirty;
//            KernelPageTable[i].shared = FALSE;
//            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
//            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;    // if the code segment was entirely on
//                                                      // a separate page, we could set its
//                                                      // pages to be read-only
//            
//            (void) interrupt->SetLevel(oldLevel);
//
//        }
//        else{
//            DEBUG('f',"vpn[%d] viz. valid BUT shared - not to be copied from parent to child\n",i);
//            KernelPageTable[i].virtualPage = i;
//            KernelPageTable[i].physicalPage = parentPageTable[i].physicalPage;
//            KernelPageTable[i].valid = parentPageTable[i].valid;
//            KernelPageTable[i].use = parentPageTable[i].use;
//            KernelPageTable[i].dirty = parentPageTable[i].dirty;
//            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;    
//            KernelPageTable[i].shared = TRUE;
//            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
//            sharedCount[parentPageTable[i].physicalPage]++;
//       }
//
//    }
//    else{
//            DEBUG('f',"vpn[%d] viz. not valid - not to be copied from parent to child\n",i);
//            KernelPageTable[i].virtualPage = i;
//            KernelPageTable[i].physicalPage = -1;
//            KernelPageTable[i].valid = FALSE;
//            KernelPageTable[i].use = parentPageTable[i].use;
//            KernelPageTable[i].dirty = parentPageTable[i].dirty;
//            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;
//            KernelPageTable[i].shared = parentPageTable[i].shared;
//            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
//    }
//       // Copy bakup memory of parent to child's backup
//       if(parentPageTable[i].inBackUp==TRUE){
//           for(int j=0;j<PageSize;j++){
//                backUp[i*PageSize+j]=parentSpace->backUp[i*PageSize+j];
//           }
//       }
//    }
    
    DEBUG('f',"Child has been successfully assigned space\n");
}

void
ProcessAddressSpace::MaintainFork(ProcessAddressSpace *parentSpace,int child_pid)
{
    unsigned i, size = numVirtualPages * PageSize;

    //ASSERT(numVirtualPages+numPagesAllocated <= NumPhysPages);                // check we're not trying
                                                                                // to run anything too big --
                                                                                // at least until we have
                                                                                // virtual memory

    DEBUG('f',"MaintainFork function called\n");
  //  DEBUG('a', "Initializing address space, num pages %d, size %d\n",numVirtualPages, size);
    // first, set up the translation
    TranslationEntry* parentPageTable = parentSpace->GetPageTable();
    for (i = 0; i < numVirtualPages; i++) {
    if(parentPageTable[i].valid){
        if(parentPageTable[i].shared == FALSE){
            DEBUG('f',"vpn[%d] viz. valid AND not shared - to be copied from parent to child\n",i);
            int pid = currentThread->GetPID();
            currentThread->SortedInsertInWaitQueue(stats->totalTicks);
            IntStatus oldLevel = interrupt->SetLevel(IntOff);
            KernelPageTable[i].virtualPage = i;
            DEBUG('f',"Asking for a free page\n");
            int ppfn =  GetNextPhysPage(parentPageTable[i].physicalPage);
            DEBUG('f',"Got a free page %d\n",ppfn);
            KernelPageTable[i].physicalPage = ppfn;           
            physPageIsFree[ppfn] = FALSE;
            physPageVPN[ppfn]=i;
            DEBUG('R',"**FORK CALL CONSTRUCTOR**\nAllocating pid[%d] to ppfn[%d]\nIt has physical page %d\n",child_pid,ppfn,KernelPageTable[i].physicalPage);
            physPagePID[ppfn]=child_pid;


            for(int j=0;j<PageSize;j++){
                DEBUG('r',"Copying data from parent to child\n");
                machine->mainMemory[ppfn*PageSize+j] = machine->mainMemory[parentPageTable[i].physicalPage*PageSize+j];
                DEBUG('r',"SUCCESS!!\n");
            }
            
            KernelPageTable[i].valid = parentPageTable[i].valid;
            KernelPageTable[i].use = parentPageTable[i].use;
            KernelPageTable[i].dirty = parentPageTable[i].dirty;
            KernelPageTable[i].shared = FALSE;
            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;      // if the code segment was entirely on
                                                        // a separate page, we could set its
                                                        // pages to be read-only
            
            (void) interrupt->SetLevel(oldLevel);

        }
        else{
            DEBUG('f',"vpn[%d] viz. valid BUT shared - not to be copied from parent to child\n",i);
            KernelPageTable[i].virtualPage = i;
            KernelPageTable[i].physicalPage = parentPageTable[i].physicalPage;
            KernelPageTable[i].valid = parentPageTable[i].valid;
            KernelPageTable[i].use = parentPageTable[i].use;
            KernelPageTable[i].dirty = parentPageTable[i].dirty;
            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;      
            KernelPageTable[i].shared = TRUE;
            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
            sharedCount[parentPageTable[i].physicalPage]++;
       }

    }
    else{
            DEBUG('f',"vpn[%d] viz. not valid - not to be copied from parent to child\n",i);
            KernelPageTable[i].virtualPage = i;
            KernelPageTable[i].physicalPage = -1;
            KernelPageTable[i].valid = FALSE;
            KernelPageTable[i].use = parentPageTable[i].use;
            KernelPageTable[i].dirty = parentPageTable[i].dirty;
            KernelPageTable[i].readOnly = parentPageTable[i].readOnly;
            KernelPageTable[i].shared = parentPageTable[i].shared;
            KernelPageTable[i].inBackUp = parentPageTable[i].inBackUp;
    }
       // Copy bakup memory of parent to child's backup
       if(parentPageTable[i].inBackUp==TRUE){
           for(int j=0;j<PageSize;j++){
                backUp[i*PageSize+j]=parentSpace->backUp[i*PageSize+j];
           }
       }
    }
    
    DEBUG('f',"MaintainFork successfully performed\n");
}
//----------------------------------------------------------------------
// ProcessAddressSpace::~ProcessAddressSpace
//  Dealloate an address space.
//----------------------------------------------------------------------

ProcessAddressSpace::~ProcessAddressSpace()
{
    if(KernelPageTable == NULL)
        return;

    int ppfn,i;
    for(i=0;i<numVirtualPages;i++){
            ppfn = KernelPageTable[i].physicalPage;
        if(KernelPageTable[i].valid && !KernelPageTable[i].shared) {
            physPageIsFree[ppfn]=true;
            physPageVPN[ppfn]=-1;
            physPagePID[ppfn]=-1;
            ASSERT(sharedCount[ppfn]==0);
        }
        else if(KernelPageTable[i].valid && KernelPageTable[i].shared) {
            sharedCount[ppfn]--;

            if(sharedCount[ppfn]==0){
                physPageIsFree[ppfn]=true;
                physPageVPN[ppfn]=-1;
                physPagePID[ppfn]=-1;
            }

       }
    } 
   
    delete KernelPageTable;

    if(openedExecutable == NULL) return;

    delete openedExecutable;
}

//----------------------------------------------------------------------
// ProcessAddressSpace::InitUserModeCPURegisters
//  Set the initial values for the user-level register set.
//
//  We write these directly into the "machine" registers, so
//  that we can immediately jump to user code.  Note that these
//  will be saved/restored into the currentThread->userRegisters
//  when this thread is context switched out.
//----------------------------------------------------------------------

void
ProcessAddressSpace::InitUserModeCPURegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
    machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);   

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numVirtualPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numVirtualPages * PageSize - 16);
}

//----------------------------------------------------------------------
// ProcessAddressSpace::SaveContextOnSwitch
//  On a context switch, save any machine state, specific
//  to this address space, that needs saving.
//
//  For now, nothing!
//----------------------------------------------------------------------

void ProcessAddressSpace::SaveContextOnSwitch() 
{}

//----------------------------------------------------------------------
// ProcessAddressSpace::RestoreContextOnSwitch
//  On a context switch, restore the machine state so that
//  this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void ProcessAddressSpace::RestoreContextOnSwitch() 
{
    machine->KernelPageTable = KernelPageTable;
    machine->KernelPageTableSize = numVirtualPages;
}

unsigned
ProcessAddressSpace::GetNumPages()
{
   return numVirtualPages;
}

TranslationEntry*
ProcessAddressSpace::GetPageTable()
{
   return KernelPageTable;
}

//----------------------------------------------------------------------
// ProcessAddressSpace::ShmAllocate
// To allocate the entered size to a shared segment of memory
//----------------------------------------------------------------------

unsigned
ProcessAddressSpace::ShmAllocate(unsigned shmSize)
{
    unsigned numShmPages = divRoundUp(shmSize, PageSize);
    numVirtualPages += numShmPages;
    unsigned i, size = numVirtualPages * PageSize;

    //ASSERT(numVirtualPages+numPagesAllocated <= NumPhysPages);                // check we're not trying
                                                                                // to run anything too big --
                                                                                // at least until we have
                                                                                // virtual memory

    DEBUG('r', "Initializing new address space for ShmAllocate() call, num pages %d, size %d\n",
                                        numVirtualPages, size);
    DEBUG('a', "Initializing new address space for ShmAllocate() call, num pages %d, size %d\n",
                                        numVirtualPages, size);
    // first, set up the translation
    TranslationEntry* oldPageTable = KernelPageTable;
    KernelPageTable = new TranslationEntry[numVirtualPages];
    for (i = 0; i < (numVirtualPages-numShmPages) ; i++) {
        KernelPageTable[i].virtualPage = i;
        KernelPageTable[i].physicalPage = oldPageTable[i].physicalPage;
        KernelPageTable[i].valid = oldPageTable[i].valid;
        KernelPageTable[i].use = oldPageTable[i].use;
        KernelPageTable[i].dirty = oldPageTable[i].dirty;
        KernelPageTable[i].readOnly = oldPageTable[i].readOnly;     // if the code segment was entirely on
                                                    // a separate page, we could set its
                                                    // pages to be read-only
        KernelPageTable[i].shared = oldPageTable[i].shared; 
        KernelPageTable[i].inBackUp = oldPageTable[i].inBackUp;
    }

    for (; i < numVirtualPages ; i++) {
        KernelPageTable[i].virtualPage = i;
        KernelPageTable[i].physicalPage = GetNextPhysPage(-1);
        DEBUG('r',"Got a free page %d for shared memory\n",KernelPageTable[i].physicalPage);
        KernelPageTable[i].valid = TRUE;
        KernelPageTable[i].use = FALSE;
        KernelPageTable[i].dirty = FALSE;
        KernelPageTable[i].readOnly = FALSE;    // if the code segment was entirely on
                                                    // a separate page, we could set its
                                                    // pages to be read-only
        KernelPageTable[i].shared = TRUE;
        KernelPageTable[i].inBackUp = FALSE;

        if(sharedCount[KernelPageTable[i].physicalPage]==0)
            physPageIsFree[KernelPageTable[i].physicalPage] = false;
            physPageVPN[KernelPageTable[i].physicalPage]=i;

        sharedCount[KernelPageTable[i].physicalPage]++;
    }
   
    // numPagesAllocated += numShmPages;

    RestoreContextOnSwitch();
    delete oldPageTable;
    DEBUG('a',"Successfully created a new PageTable and deleted the old PageTable\n");

    return (numVirtualPages-numShmPages)*PageSize;
}

//----------------------------------------------------------------------
// ProcessAddressSpace::DemandPage
// Called when a page fault is encountered
// Allocates physical page frame on demand
//----------------------------------------------------------------------

bool
ProcessAddressSpace::DemandPage(unsigned badvadr,int pid){
    
    DEBUG('r',"DemandPage successfully called\n");
   int i,vpn = badvadr/PageSize;

   int ppfn = GetNextPhysPage(-1);
   DEBUG('r',"Free Page[%d] for demand obtained\n",ppfn);
   
   if(KernelPageTable[vpn].inBackUp){ // Data found in back-up
        DEBUG('r',"BackUp Found!!\n");
        for(i=0;i<PageSize;i++){
            machine->mainMemory[ppfn*PageSize + i] = backUp[vpn*PageSize + i];
        }
   }
   else{
        NoffHeader noffH;

        DEBUG('r',"Reading Data from disk...\n");
        // openedExecutable=fileSystem->Open(fileName);
        DEBUG('r',"File sucessfully opened\n");
        
        if(openedExecutable==NULL){
            DEBUG('I',"pid = %d\n",pid);
            DEBUG('I',"Unable to open file from demand\n");
            printf("Unable to open file %s\n",fileName);
            ASSERT(false);
        }
        
        openedExecutable->ReadAt((char *)&noffH, sizeof(noffH), 0);
        if ((noffH.noffMagic != NOFFMAGIC) && 
            (WordToHost(noffH.noffMagic) == NOFFMAGIC))
            SwapHeader(&noffH);
        ASSERT(noffH.noffMagic == NOFFMAGIC);
        DEBUG('r',"Successfully read data from disk to noffH\n");
    
        DEBUG('r',"Goint to copy data from noff at %d with address in mainMemory at %d while size of code is %d\n",vpn*PageSize,ppfn*PageSize,noffH.code.size);
        openedExecutable->ReadAt(&(machine->mainMemory[ppfn*PageSize]),PageSize,noffH.code.inFileAddr+vpn*PageSize);
        DEBUG('r',"SUCCESS\n");

   }
    
   KernelPageTable[vpn].virtualPage = vpn;
   KernelPageTable[vpn].valid = TRUE;
   KernelPageTable[vpn].physicalPage = ppfn;

   sharedCount[ppfn]=0;
   physPageIsFree[ppfn]=false;
   physPageVPN[ppfn] = vpn;
   physPagePID[ppfn] = pid;
   DEBUG('R',"**DEMAND PAGE**\nAllocating pid[%d] to ppfn[%d]\nIt has physical page %d\n",pid,ppfn,threadArray[pid]->space->KernelPageTable[vpn].physicalPage);
   
   return true;
}

int
ProcessAddressSpace::GetNextPhysPage(int parentPhysPage){
    // This function is called only when a page fault is encountered
    stats->numPageFaults++;
   
    DEBUG('r',"Getting a free physical page\n");
    DEBUG('R',"Getting a free physical page and parent page = %d\n",parentPhysPage);
    int i=0,ppfn=-1;
    for(i=0;i<NumPhysPages;i++){
        if(physPageIsFree[i]==true){
            ASSERT(physPageVPN[i]==-1);
            DEBUG('u',"Got an Empty Page %d\n",i);
            bzero(&machine->mainMemory[i*PageSize], PageSize);
            physPageFIFO[i] = stats->totalTicks;
            physPageLRU[i] = stats->totalTicks;
            LRULock[i] = TRUE;
            if(parentPhysPage!=-1) {physPageLRU[parentPhysPage]=stats->totalTicks-1;LRULock[parentPhysPage]=TRUE;}
            DEBUG('r',"Returning\n");
            return i;
        }
    }
    //ASSERT(FALSE);
    DEBUG('r',"No Free Page Found. Finding a Replacement using Algo#%d\n",pageReplacementAlgo);

    if(pageReplacementAlgo == 1){
        ppfn = Random()%NumPhysPages;
        while(ppfn==parentPhysPage || sharedCount[ppfn]!=0){
            ppfn = Random()%NumPhysPages;
        }
    } else if (pageReplacementAlgo == 2){
        int i,min=stats->totalTicks+1;
        for(i=0;i<NumPhysPages;i++){
            if(sharedCount[i]==0 && i!=parentPhysPage)
            if(min>physPageFIFO[i] && physPageFIFO[i]!=-1){
                min = physPageFIFO[i];
                ppfn = i;
            }
        }
    } else if (pageReplacementAlgo == 3){
        int i,min=stats->totalTicks+1;
        for(i=0;i<NumPhysPages;i++){
            if(sharedCount[i]==0 && i!=parentPhysPage)
            if(min>physPageLRU[i] && physPageLRU[i]!=-1){
                min = physPageLRU[i];
                ppfn = i;
            }
        }
         
    } else if (pageReplacementAlgo == 4){
       LRUClockPointer=(LRUClockPointer+1)%NumPhysPages; 
       
       while(sharedCount[LRUClockPointer] || LRULock[LRUClockPointer] || LRUClockPointer == parentPhysPage){
            if(LRULock[LRUClockPointer]){
                LRULock[LRUClockPointer] = FALSE;
            }
            LRUClockPointer = (LRUClockPointer+1)%NumPhysPages;
       }
       ppfn = LRUClockPointer;
    } else {
        ASSERT(FALSE);
    }
    
    ASSERT(ppfn>=0);
    DEBUG('r',"Page Selected to be Replaced: %d\n",ppfn);

    PageReplace(ppfn);
    DEBUG('r',"Page %d successfully Replaced\n",ppfn);

    physPageFIFO[ppfn] = stats->totalTicks;
    physPageLRU[ppfn] = stats->totalTicks;
    LRULock[ppfn]=TRUE;
    DEBUG('1',"Total Ticks in Fork = %d\n",stats->totalTicks);
    if(parentPhysPage!=-1) {physPageLRU[parentPhysPage]=stats->totalTicks-1;LRULock[parentPhysPage]=TRUE;}
    return ppfn;
}

void
ProcessAddressSpace::PageReplace(int ppfn){
    int pid = physPagePID[ppfn];
    int vpn = physPageVPN[ppfn]; 
    DEBUG('R',"PageReplace() called for ppfn %d\nIt's pid=%d %d and vpn=%d\n",ppfn,pid,threadArray[pid]->GetPID(),vpn);
    int i;
    
    ProcessAddressSpace *replaceSpace = threadArray[pid]->space;
    DEBUG('R',"CHECK\n");
    if(replaceSpace==NULL){
        DEBUG('R',"Something Went Wrong...\n");
    }
    ASSERT(replaceSpace!=NULL);
    
    if(replaceSpace->KernelPageTable[vpn].physicalPage!=ppfn) DEBUG('R',"Something Went Wrong with thread[%d]\n%d!=%d\n",pid,replaceSpace->KernelPageTable[vpn].physicalPage,ppfn);
    else DEBUG('R',"Correct space identified for page %d, thread[%d]\n",ppfn,pid);
    ASSERT(replaceSpace->KernelPageTable[vpn].physicalPage==ppfn);
    
    if(replaceSpace->KernelPageTable[vpn].dirty && replaceSpace->KernelPageTable[vpn].valid){
        DEBUG('R',"Dirty bit found for vpn=%d, ppfn=%d\n",vpn,ppfn);
        for(i=0;i<PageSize;i++){
            replaceSpace->backUp[vpn*PageSize + i] = machine->mainMemory[ppfn*PageSize + i];
        }
        replaceSpace->KernelPageTable[vpn].inBackUp = TRUE;
    }
    else{
        DEBUG('R',"Dirty bit not found for vpn=%d, ppfn=%d\n",vpn,ppfn);
    }
    bzero(&machine->mainMemory[ppfn*PageSize], PageSize);
    replaceSpace->KernelPageTable[vpn].valid = FALSE;
    replaceSpace->KernelPageTable[vpn].dirty = FALSE;
    physPageIsFree[ppfn] = TRUE;
    physPageVPN[ppfn]=-1;
    physPagePID[ppfn]=-1;
}

