//
//  main.cpp
//  PthreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "CommonServices/Ctask.h"
#include "ProducerClass/CProducer.h"
#include "ConsumerClass/CConsumer.h"
#include "CommonServices/Cthread.h"
#include "CApplicationData.h"
#include "CommonServices/CQueue.h"
#include "DebugThread/DebugThreadClass.h"
#include "CommonServices/CMutex.h"
#include "CommonServices/CLogger.h"
#include "CommonServices/CLogLevel.h"
#include "CommonServices/CommonDefs.h"

#define MAX_CONSUMER_THREAD  20
#define MAX_PRODUCER_THREAD  10

int main(int argc, const char * argv[]) {
    // insert code here...
    // Instantiating pipeline

    CommonServices::Logger::CLogger lLogger(CommonServices::Logger::NONE);
    CommonServices::Services::Cthread thread_p(lLogger);
    CommonServices::Container::CQueue lPipeline(lLogger);
    CommonServices::Services::CMutex lMutex;

    lLogger(CommonServices::Logger::INFO) << "Main program entry" << std::endl;

    CommonServices::Services::Ctask *debugThread_p =  new DebugThread("DebugThread", lLogger, &lPipeline, NULL);
    unsigned int DebugThreadId = thread_p.addThread(debugThread_p);
    thread_p.startThread(DebugThreadId);
    
    for (unsigned int lCounter = 0; lCounter < MAX_CONSUMER_THREAD; ++lCounter)
    {
    	std::string taskName1 = std::string("CConsumer") + std::to_string(lCounter);
    	CommonServices::Services::Ctask *task1_p = new ApplicationData::Consumer::CConsumer(taskName1, lLogger, &lPipeline, NULL, lMutex);
    	unsigned int task1ThreadId = thread_p.addThread(task1_p);
    	thread_p.startThread(task1ThreadId);
    }
    
    for (unsigned int lCounter = 0; lCounter < MAX_PRODUCER_THREAD; ++lCounter)
    {
    	std::string taskName2 = std::string("CProducer") + std::to_string(lCounter);
        CommonServices::Services::Ctask *task2_p = new ApplicationData::Producer::CProducer(taskName2, lLogger, &lPipeline, NULL, lMutex);
    	unsigned int task2ThreadId = thread_p.addThread(task2_p);
    	thread_p.startThread(task2ThreadId);
    }
    
    thread_p.join();
    return 0;
}
