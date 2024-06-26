//
//  CProducer.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/6/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "ProducerClass/CProducer.h"
#include "AppData/CPipelineDataClass.h"

using namespace CommonServices::Logger;
using namespace ApplicationData::Producer;

CProducer::CProducer(std::string pTaskName, CommonServices::Logger::CLogger& pLogger, 
		CommonServices::Container::CQueue *pPipeline, char* pThreadData, 
		CommonServices::Services::CMutex &pMutex)
        : Ctask(pTaskName, pPipeline, pLogger), mLogger(pLogger), mThreadData(pThreadData),
	mMutex(pMutex)
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << " constructor" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << " constructor" << std::endl;
}

CProducer::~CProducer()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << " destructor" << std::endl;
    if(mThreadData != NULL)
    {
        delete mThreadData;
    }
    mThreadData = NULL;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << " destructor" << std::endl;
}

void CProducer::run()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() <<"::run()" << std::endl;
    
    mLogger(INFO_LOG) << "Starting thread : " << this->getTaskName() << std::endl;
    while(true)
    {
        if(m_Pipeline->getExecutionFlag())
        {
            mLogger(DEBUG_LOG) << "---> STOP " << this->getTaskName() << "  EXECUTION" << std::endl;
            break;
        }
        ApplicationData::PipelineData::CPipelineData *lPipeLineData 
	    = new ApplicationData::PipelineData::CPipelineData(this->getTaskName(), mThreadData);
        unsigned int lDataId = lPipeLineData->pack((char*)(this->getTaskName().c_str()), strlen("TASK"));
	mMutex.lockMutex();
        m_Pipeline->push_back((char*)lPipeLineData, lDataId);
	mMutex.unLockMutex();
	//sleep(1);
    }
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() <<"::run()" << std::endl;
}

void CProducer::cleanup()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << "::cleanup" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << "::cleanup" << std::endl;
}
