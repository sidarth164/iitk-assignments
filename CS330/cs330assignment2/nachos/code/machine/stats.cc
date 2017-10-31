// stats.h 
//	Routines for managing statistics about Nachos performance.
//
// DO NOT CHANGE -- these stats are maintained by the machine emulation.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "utility.h"
#include "stats.h"

//----------------------------------------------------------------------
// Statistics::Statistics
// 	Initialize performance metrics to zero, at system startup.
//----------------------------------------------------------------------

Statistics::Statistics()
{
    totalTicks = idleTicks = systemTicks = userTicks = 0;
    numDiskReads = numDiskWrites = 0;
    numConsoleCharsRead = numConsoleCharsWritten = 0;
    numPageFaults = numPacketsSent = numPacketsRecvd = 0;
    totalBurstTime=0;
    totalBurstNumber=0;
    avgBurstTime;
    maxBurstTime=0;
    minBurstTime=1000000;
    totalWaitTime=0;
    totalIOTime=0;
    numberWaits=0;
    maxThreadCompletionTime=0;
    minThreadCompletionTime=1000000;
    sumThreadCompletionTime=0;
    squaredSumThreadCompletionTime=0;
    numberOfThreads=0;
    quanta=100;
    error=0;
    algo=1;

}

//----------------------------------------------------------------------
// Statistics::Print
// 	Print performance metrics, when we've finished everything
//	at system shutdown.
//----------------------------------------------------------------------

void
Statistics::Print()
{
    avgBurstTime=totalBurstTime/totalBurstNumber;
    CPUUtilization=(float)totalBurstTime/(float)totalTicks*100;
    double variance = (float)squaredSumThreadCompletionTime/(float)numberOfThreads - ((float)sumThreadCompletionTime/(float)numberOfThreads) * ((float)sumThreadCompletionTime/(float)numberOfThreads);
    int avgWait=totalWaitTime/numberOfThreads;
    double errorRatio = (double)error/(double)totalBurstTime;
    printf("===================STATS======================\n");
    printf("Total CPU Burst Time: %d\n",totalBurstTime);
    printf("Total Number of CPU Bursts: %d\n",totalBurstNumber);
    printf("Average CPU Burst Time: %d\n",avgBurstTime);
    printf("Max CPU Burst Time: %d\n",maxBurstTime);
    printf("Min CPU Burst Time: %d\n",minBurstTime);
    printf("Total Wait Time: %d\n",totalWaitTime);
    printf("Average Wait Time: %d\n",avgWait);
    printf("Total I/O Time: %d\n",totalIOTime);
    printf("Total Execution Time: %d\n",totalTicks);
    printf("CPU Utilization: %f\%\n",CPUUtilization);
    printf("Maximum Thread Completion Time: %d\n",maxThreadCompletionTime);
    printf("Minimum Thread Completion Time: %d\n",minThreadCompletionTime);
    printf("Sum of Thread Completion Times: %llu\n",sumThreadCompletionTime);
    printf("Square of sum of Thread Completion Times: %llu\n",squaredSumThreadCompletionTime);
    printf("Number of Threads: %d\n",numberOfThreads);
    printf("Average of Thread Completion Time: %f\n",(float)sumThreadCompletionTime/(float)numberOfThreads);
    printf("Variance of Thread Completion Time: %lf\n",variance);
    if(algo==2){
    printf("Total CPU Estimation Error: %d\n",error);
    printf("Error Ratio: %lf\n",errorRatio);
    }
    printf("==============================================\n");
    printf("Ticks: total %d, idle %d, system %d, user %d\n", totalTicks, 
	idleTicks, systemTicks, userTicks);
    printf("Disk I/O: reads %d, writes %d\n", numDiskReads, numDiskWrites);
    printf("Console I/O: reads %d, writes %d\n", numConsoleCharsRead, 
	numConsoleCharsWritten);
    printf("Paging: faults %d\n", numPageFaults);
    printf("Network I/O: packets received %d, sent %d\n", numPacketsRecvd, 
	numPacketsSent);
}
