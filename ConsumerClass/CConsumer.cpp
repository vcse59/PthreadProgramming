//
//  CConsumer.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/8/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "CConsumer.h"
#include "../AppData/CPipelineDataClass.h"
#include "../CApplicationData.h"

using namespace CommonServices::Logger;
using namespace ApplicationData::Consumer;

CConsumer::CConsumer(std::string pTaskName, CommonServices::Logger::CLogger& pLogger, 
		CommonServices::Container::CQueue *pPipeline, char* pThreadData, 
		CommonServices::Services::CMutex &pMutex)
        : Ctask(pTaskName, pPipeline, pLogger), mLogger(pLogger), 
	mThreadData(pThreadData), mMutex(pMutex)
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " constructor" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " constructor" << std::endl;
}

CConsumer::~CConsumer()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " destructor" << std::endl;
    if(mThreadData != NULL)
    {
        delete mThreadData;
    }
    mThreadData = NULL;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " destructor" << std::endl;
}

void CConsumer::run()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() <<"::run()" << std::endl;
    
    mLogger(INFO) << "Starting thread : " << this->getTaskName() << std::endl;
    
    while(true)
    {

        if (m_Pipeline->getExecutionFlag())
        {
	    if (m_Pipeline->size() == 0)
	        {
                    mLogger(DEBUG) << "---> STOP " << this->getTaskName() << "  EXECUTION" << std::endl;
                    break;
		}
	    else
		{
		    mLogger(INFO) << this->getTaskName() << " is processing remaining Data in queue.. Size of Queue is " << m_Pipeline->size() << std::endl;
		}
        }

	mMutex.lockMutex();
        ApplicationData::PipelineData::CPipelineData *lPipeLineData 
	    = (ApplicationData::PipelineData::CPipelineData*) m_Pipeline->getQueueData(0);
        
        if (lPipeLineData != NULL)
        {
            std::string lTaskName = lPipeLineData->mTaskName;
	    ApplicationData::ThreadData::THREAD_STRUCT *msgData = lPipeLineData->mData;
            if (msgData != NULL)
            {
                mLogger(INFO) << "Processing data : "<< msgData->lDataId << " by " << this->getTaskName() << " from task : " << lTaskName<< std::endl;
            }
            m_Pipeline->pop_front();
        }
        else
        {
            //mLogger(ERROR) << "No more data in Queue for processing" << std::endl;
        }
	mMutex.unLockMutex();
	//sleep(2);
    }
    mLogger(DEBUG) << "Exiting " << this->getTaskName() <<"::run()" << std::endl;
}

void CConsumer::cleanup()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << "::cleanup" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << "::cleanup" << std::endl;
}

