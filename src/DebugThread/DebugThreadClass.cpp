//
//  DebugThreadClass.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 3/1/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "DebugThread/DebugThreadClass.h"
#include "AppData/CPipelineDataClass.h"
#include "CApplicationData.h"

using namespace CommonServices::Logger;

DebugThread::DebugThread(std::string pTaskName, CommonServices::Logger::CLogger& pLogger, 
		CommonServices::Container::CQueue *pPipeline, char* pThreadData)
	: Ctask(pTaskName, pPipeline, pLogger)
	, mLogger(pLogger), mThreadData(pThreadData)
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << " constructor" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << " constructor" << std::endl;
}

DebugThread::~DebugThread()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << " destructor" << std::endl;
    if(mThreadData != NULL)
    {
        delete mThreadData;
    }
    mThreadData = NULL;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << " destructor" << std::endl;
}

void DebugThread::run()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << "::run()" << std::endl;
    mLogger(INFO_LOG) << "Starting thread : " << this->getTaskName() << std::endl;
    
    while(true)
    {
        std::ifstream readFile("stopExecution.txt");
        mLogger(DEBUG_LOG) << "Data count in pipeline : " << this->m_Pipeline->size() << std::endl;
        if (readFile.is_open())
        {
            mLogger(DEBUG_LOG) << "---> STOP " << this->getTaskName() << "  EXECUTION" << std::endl;
            //std::string fileContent;
            //getline(readFile,fileContent);
            
            /*CPipelineData *lPipeLineData = new CPipelineData(this->getTaskName(), mThreadData);
            char data[] = "EXIT";
            unsigned int lDataId = lPipeLineData->pack(data, strlen(data));
            m_Pipeline->push_back(lPipeLineData, lDataId);*/
            readFile.close();
            
            m_Pipeline->setExecutionFlag(true);
            break;
        }
        //sleep(2);
    }
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << "::run()" << std::endl;
}

void DebugThread::cleanup()
{
    mLogger(DEBUG_LOG) << "Entering " << this->getTaskName() << "::cleanup" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting " << this->getTaskName() << "::cleanup" << std::endl;
}

