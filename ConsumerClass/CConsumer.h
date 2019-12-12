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

class CQueue;
class CLogger;

class CConsumer : public Ctask
{
public:
    CConsumer(std::string pTaskName, CLogger& pLogger,
		    CQueue *pPipeline, char* pThreadData, CMutex &pMutex);
    ~CConsumer();
    
    void run();
    void cleanup();
    
private:
    CLogger& mLogger;
    char *mThreadData;
    CMutex &mMutex;
};

#endif /* CConsumer_h */
