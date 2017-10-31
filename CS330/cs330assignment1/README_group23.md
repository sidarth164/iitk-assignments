SysCall_GetReg:
It returns the value stored in the register #4

SysCall_GetPA:
It mainly checks if the passed virtual address is valid. If it is, then it returns the physical address.
Note that the formula for getting the physical address from virtual address is-
(((machine->KernelPageTable)[virtual_page_no]).physicalPage)*(PageSize) + virtual_address%(PageSize)

SysCall_GetPID:
We have just created a public function getPID() for the class NachOSThread in thread.cc and this function returns the value of the private member pid.

SysCall_GetPPID:
We have just created a public function getPPID() for the class NachOSThread in thread.cc and this function returns the value of the private member ppid.

SysCall_NumInstr:
Each process keep a count of number of instructions executed by it.
The thread variable numInstr is incremented in the function oneTick() in interrupt.cc


SysCall_Yield:
We first increment the PC counter and then call the YieldCPU() function.

SysCall_Time:
We just return the value of the totalTicks of stats object

SysCall_Sleep:
First increment the PC Counter.
If the value of the passed sleep_time is 0, then yield.
Otherwise, we just push this thread to the sleeping queue.
Note that the list sleeping_threads is defined by us. It stores all those threads who have been put to sleep using SysCall_Sleep. Now we have modifiefd the TimeInterruptHandler() function of system.cc such that ot regularly checks which threads in the sleeping queue have to be woken up.

SysCall_Join:
It implements the feature where the parent process waits for its child to terminate before moving further. The parent has the list of all its children (in allChildren) and all its exited child (in exitedChildren).
It then searches whether there is a thread with the given PID in the list allChildren (in this case, it sets the return regter to the required thread's exit code). If it couldn.t find any such element, then it means that either the required thread is not a child of the current thread or the child has not yet exited. In the former case we return -1 and in the latter we put the current thread to sleep.

SysCall_Exit:
The process which is to exit shuts off interrupts, checks whether it needs to wake up its parent in case the parent is waiting (using the wakeUpParent field). When a process is being destroyed, its parent's exitedChildren list is updated with the input error code.
It then updates the threadToBeDestroyed paramter so that the next process can destroy it. In case it is last process to exit, it halts the machine.

SysCall_Exec:
This creates a new process, allocates address space to it. 
for this, we just have to assign a new physical address to the current thread's "space" attribute.
Also note that the PC counter will NOT be updated here.
Also, we have made some slight changes to the constructor for ProcessAddressSpace class in addrspace.cc such that it doesn't allocate address from the starting (i.e. it doesn't remove the already allocated address) 

SysCall_Fork:
This function creates a new process running along with other process.
We have first inreased the program counter (so that the newly created child also starts from next PC state). Then we share the address space if the parent process with the child (for this we have created a new constructor for initializing address space). Then contect switch is called and the suitable PID values are updated in the return register. Also note that we have defined anew function Context() in exception.cc whose main job is to replace the scheduler for the child for the first time.
