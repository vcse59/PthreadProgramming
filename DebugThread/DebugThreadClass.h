//
//  DebugThreadClass.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 3/1/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef DebugThreadClass_hpp
#define DebugThreadClass_hpp

#include <stdio.h>
#include <iostream>
#include "../CommonServices/Ctask.h"
#include "../CommonServices/CQueue.h"
#include "../CommonServices/CLogger.h"

class DebugThread : public CommonServices::Services::Ctask
{
public:
    DebugThread(std::string pTaskName, CommonServices::Logger::CLogger& pLogger, 
		    CommonServices::Container::CQueue *pPipeline, char* pThreadData);
    ~DebugThread();
    
    void run();
    void cleanup();
    
private:
    CommonServices::Logger::CLogger& mLogger;
    char *mThreadData;
};

#endif /* DebugThreadClass_hpp */
