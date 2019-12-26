//
//  CConsumer.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/8/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CConsumer_h
#define CConsumer_h

#include <stdio.h>
#include "../CommonServices/Ctask.h"
#include "../CommonServices/CMutex.h"
#include "../CommonServices/CQueue.h"
#include "../CommonServices/CLogger.h"

class CConsumer : public CommonServices::Services::Ctask
{
public:
    CConsumer(std::string pTaskName, CommonServices::Logger::CLogger& pLogger,
		    CommonServices::Container::CQueue *pPipeline, char* pThreadData, 
		    CommonServices::Services::CMutex &pMutex);
    ~CConsumer();
    
    void run();
    void cleanup();
    
private:
    CommonServices::Logger::CLogger& mLogger;
    char *mThreadData;
    CommonServices::Services::CMutex &mMutex;
};

#endif /* CConsumer_h */
