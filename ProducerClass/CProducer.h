//
//  CProducer.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/6/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CProducer_h
#define CProducer_h

#include <stdio.h>
#include <iostream>
#include "../CommonServices/Ctask.h"
#include "../CommonServices/CMutex.h"

class CQueue;
class CLogger;

class CProducer : public Ctask
{
public:
    CProducer(std::string pTaskName, CLogger& pLogger, CQueue *pPipeline,
		    char* pThreadData, CMutex &pMutex);
    ~CProducer();
    
    void run();
    void cleanup();
    
private:
    CLogger &mLogger;
    char *mThreadData;
    CMutex  &mMutex;
};

#endif /* CProducer_h */
