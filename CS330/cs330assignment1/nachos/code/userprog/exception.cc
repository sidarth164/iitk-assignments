// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "console.h"
#include "synch.h"
#include "stats.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------
static Semaphore *readAvail;
static Semaphore *writeDone;
static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

static void ConvertIntToHex (unsigned v, Console *console)
{
   unsigned x;
   if (v == 0) return;
   ConvertIntToHex (v/16, console);
   x = v % 16;
   if (x < 10) {
      writeDone->P() ;
      console->PutChar('0'+x);
   }
   else {
      writeDone->P() ;
      console->PutChar('a'+x-10);
   }
}

//----------------------------------------------------------------------
// void Context(int arg)
// Function which handles the initializtion of the thread in place of 
// SchedulThread
//----------------------------------------------------------------------

void
Context(int arg){
    DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());

    // If the old thread gave up the processor because it was finishing,
    // we need to delete its carcass.  Note we cannot delete the thread
    // before now (for example, in NachOSThread::FinishThread()), because up to this
    // point, we were still running on the old thread's stack!
    if (threadToBeDestroyed != NULL) {
        delete threadToBeDestroyed;
        threadToBeDestroyed = NULL;
    }

#ifdef USER_PROGRAM
    if (currentThread->space != NULL) {     // if there is an address space
        currentThread->RestoreUserState();     // to restore, do it.
        currentThread->space->RestoreContextOnSwitch();
    }

    machine->Run();
#endif
}

//---------------------------------------------------------------------
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
    int memval, vaddr, printval, tempval, exp;
    unsigned printvalus;        // Used for printing in hex
    if (!initializedConsoleSemaphores) {
       readAvail = new Semaphore("read avail", 0);
       writeDone = new Semaphore("write done", 1);
       initializedConsoleSemaphores = true;
    }
    Console *console = new Console(NULL, NULL, ReadAvail, WriteDone, 0);;

    if ((which == SyscallException) && (type == SysCall_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    }
    else if ((which == SyscallException) && (type == SysCall_PrintInt)) {
       printval = machine->ReadRegister(4);
       if (printval == 0) {
	  writeDone->P() ;
          console->PutChar('0');
       }
       else {
          if (printval < 0) {
	     writeDone->P() ;
             console->PutChar('-');
             printval = -printval;
          }
          tempval = printval;
          exp=1;
          while (tempval != 0) {
             tempval = tempval/10;
             exp = exp*10;
          }
          exp = exp/10;
          while (exp > 0) {
	     writeDone->P() ;
             console->PutChar('0'+(printval/exp));
             printval = printval % exp;
             exp = exp/10;
          }
       }
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if ((which == SyscallException) && (type == SysCall_PrintChar)) {
	writeDone->P() ;
        console->PutChar(machine->ReadRegister(4));   // echo it!
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if ((which == SyscallException) && (type == SysCall_PrintString)) {
       vaddr = machine->ReadRegister(4);
       machine->ReadMem(vaddr, 1, &memval);
       while ((*(char*)&memval) != '\0') {
	  writeDone->P() ;
          console->PutChar(*(char*)&memval);
          vaddr++;
          machine->ReadMem(vaddr, 1, &memval);
       }
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if ((which == SyscallException) && (type == SysCall_GetReg)) {
       int reg_no = machine->ReadRegister(4);
       int data = machine->ReadRegister(reg_no);
       machine->WriteRegister(2,data);
        // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
       
    }
    else if((which == SyscallException) && (type == SysCall_GetPA)){
       unsigned int virtual_address = machine -> ReadRegister(4);
       unsigned int virtual_page_no = virtual_address/( PageSize);
       if(virtual_page_no > (machine-> pageTableSize))
          machine->WriteRegister(2,-1);
       else if(!(((machine->KernelPageTable)[virtual_page_no]).valid))
          machine->WriteRegister(2,-1);
       else if( (((machine->KernelPageTable)[virtual_page_no]).physicalPage)> NumPhysPages)
          machine->WriteRegister(2,-1);
       else
          machine->WriteRegister(2,(((machine->KernelPageTable)[virtual_page_no]).physicalPage)*(PageSize) + virtual_address%(PageSize) );
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
 
    }
    else if((which == SyscallException) && (type == SysCall_GetPID)){
       machine->WriteRegister(2,currentThread->getPID());
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if((which == SyscallException) && (type == SysCall_GetPPID)){
       machine->WriteRegister(2,currentThread->getPPID());
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if((which == SyscallException) && (type == SysCall_NumInstr)){
        machine->WriteRegister(2,currentThread->numInstr);
        // Advance program counters.
        machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
        machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
        machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if((which == SyscallException) && (type == SysCall_Yield)){
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
       currentThread->YieldCPU();
    }
    else if((which == SyscallException) && (type == SysCall_Time)){
       machine->WriteRegister(2,stats->totalTicks);
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if((which == SyscallException) && (type == SysCall_Sleep)){
       unsigned int sleep_time = machine->ReadRegister(4);

       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
        
       //printf("\nCurrent Time (before sleep): %d\n",stats->totalTicks);
       //printf("Expected wake up time: %d\n",stats->totalTicks+sleep_time);
       if(sleep_time == 0){
          currentThread->YieldCPU();
       }
       else{
          IntStatus oldLevel = interrupt->SetLevel(IntOff);
          //printf("Putting this thread to sleep...\n");  
          sleeping_threads->SortedInsert(currentThread,stats->totalTicks+sleep_time);
          currentThread->PutThreadToSleep();
          //printf("New thread obtained\n");  
          (void) interrupt->SetLevel(oldLevel);
       }
    }
    else if ((which == SyscallException) && (type == SysCall_PrintIntHex)) {
       printvalus = (unsigned)machine->ReadRegister(4);
       writeDone->P() ;
       console->PutChar('0');
       writeDone->P() ;
       console->PutChar('x');
       if (printvalus == 0) {
          writeDone->P() ;
          console->PutChar('0');
       }
       else {
          ConvertIntToHex (printvalus, console);
       }
       // Advance program counters.
       machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
       machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
       machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if ((which == SyscallException) && (type == SysCall_Exit)) {
       int exitCode =  machine->ReadRegister(4);
       if(currentThread->parent!=NULL)
       currentThread->parent->exitedChildren->SortedInsert((void *)exitCode,currentThread->getPID());
       //currentThread->parent->exitedChildren->Append(new ListElement(NULL, getPID()));
       currentThread->FinishThread();
    }

    else if ((which == SyscallException) && (type == SysCall_Join)) {
        int pid = machine->ReadRegister(4);
        NachOSThread *child;

        //printf("Joining...\n");

        IntStatus oldLevel = interrupt->SetLevel(IntOff);

        int *exitCode;
        exitCode = (int *)(currentThread->exitedChildren->Search(pid));
        
        //if(exitCode!=NULL)
        //printf("exit code = %d\n",(int)exitCode);

        // exitCode=-1 denotes that child has not exited yet or no such child is present
        if((int)exitCode == -1729){
            child = (NachOSThread *)currentThread->allChildren->Search(pid);
            
            if(child != NULL){
                child->wakeUpParent = 1;
                currentThread->PutThreadToSleep();
            }
            else{
                machine->WriteRegister(2,-1);
            }

        }
        else{
            machine->WriteRegister(2,(int)exitCode);
        }

        (void) interrupt->SetLevel(oldLevel);
        // Advance Program Counters
        machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
        machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
        machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
    }
    else if((which == SyscallException) && (type == SysCall_Exec)){
        vaddr = machine->ReadRegister(4);
        char* filename=new char[1000];
        int i=0;
        machine->ReadMem(vaddr, 1, &memval);
        while ((*(char*)&memval) != '\0') {
            filename[i]=(*(char*)&memval);
            i++;
            vaddr++;
            machine->ReadMem(vaddr, 1, &memval);
        }
        filename[i]=('\0');

        OpenFile *executable = fileSystem->Open(filename);
        ProcessAddressSpace *space;

        if (executable == NULL) {
            printf("Unable to open file %s\n", filename);
            return;
        }
        space = new ProcessAddressSpace(executable);

        if(currentThread->space!=NULL){
            delete currentThread->space;
        }

        currentThread->space = space;

        delete executable;     // close file

        space->InitUserModeCPURegisters();   // set the initial register values
        space->RestoreContextOnSwitch();   // load page table register

        machine->Run();      // jump to the user progam
                            // machine->Run never returns;
                            // the address space exits
                            // by doing the syscall "exit"       
    }
    else if((which == SyscallException) && (type == SysCall_Fork)){
        NachOSThread* forked_child = new NachOSThread("Forked_child:new");
        
        // Advance program counters.
        machine->WriteRegister(PrevPCReg, machine->ReadRegister(PCReg));
        machine->WriteRegister(PCReg, machine->ReadRegister(NextPCReg));
        machine->WriteRegister(NextPCReg, machine->ReadRegister(NextPCReg)+4);
        
        // Adding the newly created child to the list of children the current thread has
        forked_child->parent->allChildren->SortedInsert(forked_child,forked_child->getPID());
        ProcessAddressSpace *space=new ProcessAddressSpace();
        
        // Assigning the newly created space to the newly created forked child
        forked_child->space = space;
      
        // Saving the user registers of the child so that it starts executin from the next PC after being called
        forked_child->SaveUserState();
        forked_child->SetRegisters(2,0);    // return value of the child thread should be zero

        // Calling the NachOSThread::ThreadFork function
        forked_child->ThreadFork(Context,(int) forked_child);
       
        /*
        IntStatus oldLevel = interrupt->SetLevel(IntOff);
        scheduler->MoveThreadToReadyQueue(forked_child);    // MoveThreadToReadyQueue assumes that interrupts 
                    // are disabled!
        (void) interrupt->SetLevel(oldLevel);
        */

        //Setting the return value of the parent thread as the PID of the child
        machine->WriteRegister(2,forked_child->getPID());
    }
    else {
	printf("Unexpected user mode exception %d %d\n", which, type);
	ASSERT(FALSE);
    }
}
