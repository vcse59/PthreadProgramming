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
#include "DebugThreadClass.h"
#include "../CommonServices/CQueue.h"
#include "../AppData/CPipelineDataClass.h"
#include "../CApplicationData.h"
#include "../CommonServices/CLogger.h"

DebugThread::DebugThread(std::string pTaskName, CLogger& pLogger, 
		CQueue *pPipeline, char* pThreadData)
	: Ctask(pTaskName, pPipeline, pLogger)
	, mLogger(pLogger), mThreadData(pThreadData)
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " constructor" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " constructor" << std::endl;
}

DebugThread::~DebugThread()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << " destructor" << std::endl;
    if(mThreadData != NULL)
    {
        delete mThreadData;
    }
    mThreadData = NULL;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << " destructor" << std::endl;
}

void DebugThread::run()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << "::run()" << std::endl;
    
    mLogger(INFO) << "Starting thread : " << this->getTaskName() << std::endl;
    
    while(true)
    {
        std::ifstream readFile("stopExecution.txt");
        mLogger(DEBUG) << "Data count in pipeline : " << this->m_Pipeline->size() << std::endl;
        if (readFile.is_open())
        {
            mLogger(DEBUG) << "---> STOP " << this->getTaskName() << "  EXECUTION" << std::endl;
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
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << "::run()" << std::endl;
}

void DebugThread::cleanup()
{
    mLogger(DEBUG) << "Entering " << this->getTaskName() << "::cleanup" << std::endl;
    mLogger(DEBUG) << "Exiting " << this->getTaskName() << "::cleanup" << std::endl;
}

