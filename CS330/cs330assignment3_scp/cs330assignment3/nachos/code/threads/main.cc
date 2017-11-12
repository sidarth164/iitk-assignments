// main.cc 
//	Bootstrap code to initialize the operating system kernel.
//
//	Allows direct calls into internal operating system functions,
//	to simplify debugging and testing.  In practice, the
//	bootstrap code would just initialize data structures,
//	and start a user program to print the login prompt.
//
// 	Most of this file is not needed until later assignments.
//
// Usage: nachos -d <debugflags> -rs <random seed #>
//		-s -x <nachos file> -c <consoleIn> <consoleOut>
//		-f -cp <unix file> <nachos file>
//		-p <nachos file> -r <nachos file> -l -D -t
//              -n <network reliability> -m <machine id>
//              -o <other machine id>
//              -z
//
//    -d causes certain debugging messages to be printed (cf. utility.h)
//    -rs causes Yield to occur at random (but repeatable) spots
//    -z prints the copyright message
//
//  USER_PROGRAM
//    -s causes user programs to be executed in single-step mode
//    -x runs a user program
//    -c tests the console
//
//  FILESYS
//    -f causes the physical disk to be formatted
//    -cp copies a file from UNIX to Nachos
//    -p prints a Nachos file to stdout
//    -r removes a Nachos file from the file system
//    -l lists the contents of the Nachos directory
//    -D prints the contents of the entire file system 
//    -t tests the performance of the Nachos file system
//
//  NETWORK
//    -n sets the network reliability
//    -m sets this machine's host id (needed for the network)
//    -o runs a simple test of the Nachos network software
//
//  NOTE -- flags are ignored until the relevant assignment.
//  Some of the flags are interpreted here; some in system.cc.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#define MAIN
#include "copyright.h"
#undef MAIN

#include "utility.h"
#include "system.h"


// External functions used by this file

extern void ThreadTest(void), Copy(char *unixFile, char *nachosFile);
extern void Print(char *file), PerformanceTest(void);
extern void LaunchUserProcess(char *file), ConsoleTest(char *in, char *out);
extern void MailTest(int networkID);

extern void ReadInputAndFork(char *file);

//----------------------------------------------------------------------
// main
// 	Bootstrap the operating system kernel.  
//	
//	Check command line arguments
//	Initialize data structures
//	(optionally) Call test procedure
//
//	"argc" is the number of command line arguments (including the name
//		of the command) -- ex: "nachos -d +" -> argc = 3 
//	"argv" is an array of strings, one for each command line argument
//		ex: "nachos -d +" -> argv = {"nachos", "-d", "+"}
//----------------------------------------------------------------------

int
main(int argc, char **argv)
{
    int argCount;			// the number of arguments 
					// for a particular command

    int schedPriority = MAX_NICE_PRIORITY;

    DEBUG('t', "Entering main");
    (void) Initialize(argc, argv);
    stats->numPhysPages = NumPhysPages;
    
#ifdef THREADS
    ThreadTest();
#endif

    for (argc--, argv++; argc > 0; argc -= argCount, argv += argCount) {
	argCount = 1;
        if (!strcmp(*argv, "-z"))               // print copyright
            printf (copyright);
#ifdef USER_PROGRAM
        if (!strcmp(*argv, "-A")) {		// read scheduling algorithm
           schedulingAlgo = atoi(*(argv + 1));
           argCount = 2;
           ASSERT((schedulingAlgo > 0) && (schedulingAlgo <= 4));
           if ((schedulingAlgo == ROUND_ROBIN) || (schedulingAlgo == UNIX_SCHED)) {
              ASSERT (SCHED_QUANTUM > 0);
           }
           if (schedulingAlgo == UNIX_SCHED) {
              currentThread->SetBasePriority(schedPriority+DEFAULT_BASE_PRIORITY);
              currentThread->SetPriority(schedPriority+DEFAULT_BASE_PRIORITY);
              currentThread->SetUsage(0);
           }
        } else if(!strcmp(*argv,"-R")) {
            pageReplacementAlgo = atoi(*(argv + 1));
            int pages = atoi(*(argv + 2));
            argCount = 3;
            //argCount = 2;
            ASSERT((pageReplacementAlgo >= 0) && (pageReplacementAlgo < 5));
            if(pageReplacementAlgo >0)
            NumPhysPages=pages;
            stats->numPhysPages = NumPhysPages;
        }else if (!strcmp(*argv, "-p")) {
            schedPriority = atoi(*(argv + 1));
            argCount = 2;
            ASSERT((schedPriority >= 0) && (schedPriority <= 100));
            currentThread->SetBasePriority(schedPriority+DEFAULT_BASE_PRIORITY);
            currentThread->SetPriority(schedPriority+DEFAULT_BASE_PRIORITY);
            currentThread->SetUsage(0);
        } else if (!strcmp(*argv, "-x")) {        	// run a user program
	    ASSERT(argc > 1);
            LaunchUserProcess(*(argv + 1));
            argCount = 2;
        } else if (!strcmp(*argv, "-c")) {      // test the console
	    if (argc == 1)
	        ConsoleTest(NULL, NULL);
	    else {
		ASSERT(argc > 2);
	        ConsoleTest(*(argv + 1), *(argv + 2));
	        argCount = 3;
	    }
	    interrupt->Halt();		// once we start the console, then 
					// nachos will loop forever waiting 
					// for console input
	} else if (!strcmp(*argv, "-f")) {	// test multiprogramming
            ASSERT (argc > 1);
            ReadInputAndFork(*(argv + 1));
            argCount = 2;
        }
#endif // user_program
#ifdef filesys
	if (!strcmp(*argv, "-cp")) { 		// copy from unix to nachos
	    assert(argc > 2);
	    copy(*(argv + 1), *(argv + 2));
	    argcount = 3;
	} else if (!strcmp(*argv, "-p")) {	// print a nachos file
	    assert(argc > 1);
	    print(*(argv + 1));
	    argcount = 2;
	} else if (!strcmp(*argv, "-r")) {	// remove nachos file
	    assert(argc > 1);
	    filesystem->remove(*(argv + 1));
	    argcount = 2;
	} else if (!strcmp(*argv, "-l")) {	// list nachos directory
            filesystem->list();
	} else if (!strcmp(*argv, "-d")) {	// print entire filesystem
            filesystem->print();
	} else if (!strcmp(*argv, "-t")) {	// performance test
            performancetest();
	}
#endif // filesys
#ifdef network
        if (!strcmp(*argv, "-o")) {
	    ASSERT(argc > 1);
            delay(2); 				// delay for 2 seconds
						// to give the user time to 
						// start up another nachos
            mailtest(atoi(*(argv + 1)));
            argCount = 2;
        }
#endif // network
    }

    currentThread->FinishThread();	// NOTE: if the procedure "main" 
				// returns, then the program "nachos"
				// will exit (as any other normal program
				// would).  But there may be other
				// threads on the ready list.  We switch
				// to those threads by saying that the
				// "main" thread is finished, preventing
				// it from returning.
    return(0);			// Not reached...
}
