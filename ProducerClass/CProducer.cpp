//
//  CProducer.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/6/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include "CProducer.h"
#include <iostream>
#include <unistd.h>
#include "../CommonServices/CQueue.h"
#include "../AppData/CPipelineDataClass.h"
#include "../CommonServices/CLogLevel.h"
#include "../CommonServices/CLogger.h"

CProducer::CProducer(std::string pTaskName, CLogger& pLogger, 
		CQueue *pPipeline, char* pThreadData, CMutex &pMutex)
        : Ctask(pTaskName, pPipeline, pLogger), mLogger(pLogger), mThreadData(pThreadData),
	mMutex(pMutex)
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " constructor" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " constructor" << std::endl;
}

CProducer::~CProducer()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " destructor" << std::endl;
    if(mThreadData != NULL)
    {
        delete mThreadData;
    }
    mThreadData = NULL;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " destructor" << std::endl;
}

void CProducer::run()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() <<"::run()" << std::endl;
    
    mLogger(INFO) << "Starting thread : " << this->getTaskName() << std::endl;
    while(true)
    {
        if(m_Pipeline->getExecutionFlag())
        {
            mLogger(DEBUG) << "---> STOP " << this->getTaskName() << "  EXECUTION" << std::endl;
            break;
        }
        CPipelineData *lPipeLineData = new CPipelineData(this->getTaskName(), mThreadData);
        unsigned int lDataId = lPipeLineData->pack((char*)(this->getTaskName().c_str()), strlen("TASK"));
	mMutex.lockMutex();
        m_Pipeline->push_back(lPipeLineData, lDataId);
	mMutex.unLockMutex();
	//sleep(1);
    }
    mLogger(DEBUG) << "Exiting " << this->getTaskName() <<"::run()" << std::endl;
}

void CProducer::cleanup()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << "::cleanup" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << "::cleanup" << std::endl;
}