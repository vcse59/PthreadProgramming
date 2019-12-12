//
//  CQueue.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 1/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//
#include <unistd.h>
#include <cstring>
#include "../AppData/CPipelineDataClass.h"
#include "CQueue.h"
#include "CMutex.h"
#include "CLinkList.h"
#include "CLogger.h"

CQueue::CQueue(CLogger& pLogger)
	:mLogger(pLogger)
{
    mLogger(DEBUG) << "Entering CQueue constructor" << std::endl;
    mStopFlag = false;
    mpMutex  =  new CMutex();
    mpMutex->lockMutex();
    dQueueContainer = new CLinkList(pLogger);
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue constructor" << std::endl;
}

CQueue::~CQueue()
{
    mLogger(DEBUG) << "Entering CQueue destructor" << std::endl;
    
    mLogger(INFO) << "Total Data in Queue " << dQueueContainer->length() << std::endl;

    unsigned int lCount = 0;
    unsigned int lContainerLength = dQueueContainer->length();
    for( ; lCount < lContainerLength; lCount++)
    {
        dataContext_t *lDataContext_p = (dataContext_t*)(dQueueContainer->getDataByIndex(lCount));
        CPipelineData *lPipeLineData = (CPipelineData*)(lDataContext_p->data);
     
        mpMutex->lockMutex();
        if(lPipeLineData != NULL)
        {
            delete lPipeLineData;
        }
        lPipeLineData = NULL;
        free(lDataContext_p);
        lDataContext_p = NULL;
        mpMutex->unLockMutex();
    }
    mpMutex->lockMutex();
    if (dQueueContainer != NULL)
        delete dQueueContainer;
    dQueueContainer = NULL;
    mpMutex->unLockMutex();

    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
    mLogger(DEBUG) << "Exiting CQueue destructor" << std::endl;
}

bool CQueue::isEmpty()
{
    mLogger(DEBUG) << "Entering CQueue::isEmpty" << std::endl;
    return false;
    mLogger(DEBUG) << "Exiting CQueue::isEmpty" << std::endl;
}

unsigned int CQueue::size()
{
    mLogger(DEBUG) << "Entering CQueue::size" << std::endl;
    return dQueueContainer->length();
    mLogger(DEBUG) << "Exiting CQueue::size" << std::endl;
}

void CQueue::push_front(CPipelineData* pData, unsigned int pDataId)
{
    mLogger(DEBUG) << "Entering CQueue::push_front" << std::endl;
    // Allocate and initialize memory of dataContext_t size
    dataContext_t *lDataContext_p = (dataContext_t *)malloc(sizeof(dataContext_t));
    memset((void*)lDataContext_p, 0 , sizeof(dataContext_t));
    
    if (lDataContext_p ==  NULL)
    {
        mLogger(ERROR) << "CQueue::push_front Malloc failure : dataContext_p" << std::endl;
        return;
    }
    lDataContext_p->data = (char*)pData;
    lDataContext_p->dataId = pDataId;
    mpMutex->lockMutex();
    dQueueContainer->insertNodeAtStart((void*) lDataContext_p);
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue::push_front" << std::endl;
}

void CQueue::push_back(CPipelineData* pData, unsigned int pDataId)
{
    mLogger(DEBUG) << "Entering CQueue::push_back" << std::endl;
    // Allocate and initialize memory of dataContext_t size
    dataContext_t *lDataContext_p = (dataContext_t *)malloc(sizeof(dataContext_t));
    memset((void*)lDataContext_p, 0 , sizeof(dataContext_t));
    
    if (lDataContext_p ==  NULL)
    {
        std::cerr << "CQueue:push_back Malloc failure : dataContext_p" << std::endl;
        return;
    }
    lDataContext_p->data = (char*)pData;
    lDataContext_p->dataId = pDataId;
    mpMutex->lockMutex();
    dQueueContainer->insertNodeAtEnd((void*) lDataContext_p);
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue::push_back" << std::endl;
}

void CQueue::erase(unsigned int pDataId)
{
    mLogger(DEBUG) << "Entering CQueue::erase" << std::endl;
    unsigned int lThreadCount = dQueueContainer->length();
    unsigned int lCount = 0;
    
    for( ; lCount < lThreadCount; lCount++)
    {
        dQueueContainer->printData();
        dataContext_t *lDataContext_p = (dataContext_t*)(dQueueContainer->getDataByIndex(lCount));
        if(lDataContext_p->dataId == pDataId)
        {
	    mpMutex->lockMutex();
            CPipelineData *lPipeLineData = (CPipelineData*)(lDataContext_p->data);
            
            if(lPipeLineData != NULL)
            {
                delete lPipeLineData;
            }
            lPipeLineData = NULL;
            free(lDataContext_p);
            lDataContext_p = NULL;
            
            dQueueContainer->deleteNode(lCount);
    	    mpMutex->unLockMutex();
            break;
        }
    }
    mLogger(DEBUG) << "Exiting CQueue::erase" << std::endl;
}

void CQueue::pop_front()
{
    mLogger(DEBUG) << "Entering CQueue::pop_front" << std::endl;
    if(dQueueContainer->length() <= 0)
    {
        mLogger(ERROR) << "CQeueu:pop_front Queue container is empty" << std::endl;
        return;
    }
    
    mLogger(INFO) << "CQueue::pop_front Queue length : " << dQueueContainer->length() << std::endl;
    dataContext_t *lDataContext_p = (dataContext_t*)(dQueueContainer->begin());
    CPipelineData *lPipeLineData = (CPipelineData*)(lDataContext_p->data);
    
    mpMutex->lockMutex();
    if(lPipeLineData != NULL)
    {
        delete lPipeLineData;
    }
    
    lPipeLineData = NULL;
    free(lDataContext_p);
    lDataContext_p = NULL;
    dQueueContainer->deleteNodeFromStart();
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue::pop_front" << std::endl;
}

void CQueue::pop_back()
{
    mLogger(DEBUG) << "Entering CQueue::pop_back" << std::endl;
    if(dQueueContainer->length() <= 0)
    {
        mLogger(ERROR) << "CQeueue::pop_back Queue container is empty" << std::endl;
        return;
    }
    
    dataContext_t *lDataContext_p = (dataContext_t*)(dQueueContainer->end());
    CPipelineData *lPipeLineData = (CPipelineData*)(lDataContext_p->data);
    
    mpMutex->lockMutex();
    if(lPipeLineData != NULL)
    {
        delete lPipeLineData;
    }
    lPipeLineData = NULL;
    free(lDataContext_p);
    lDataContext_p = NULL;
    dQueueContainer->deleteNodeFromStart();
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue::pop_back" << std::endl;
}

CPipelineData* CQueue::getQueueData(unsigned int pIndex)
{
    mLogger(DEBUG) << "Entering CQueue::getQueueData" << std::endl;
    dataContext_t *lDataContext_p = (dataContext_t*)(dQueueContainer->getDataByIndex(pIndex));
    
    if (lDataContext_p == NULL)
        return NULL;
    mLogger(DEBUG) << "Exiting CQueue::getQueueData" << std::endl;
    return (CPipelineData*)(lDataContext_p->data);
}

void CQueue::setExecutionFlag(bool isStop)
{
    mLogger(DEBUG) << "Entering CQueue::setExecutionFlag" << std::endl;
    mpMutex->lockMutex();
    mStopFlag = isStop;
    mpMutex->unLockMutex();
    mLogger(DEBUG) << "Exiting CQueue::setExecutionFlag" << std::endl;
}

bool CQueue::getExecutionFlag()
{
    mLogger(DEBUG) << "Entering CQueue::getExecutionFlag" << std::endl;
    mLogger(DEBUG) << "Exiting CQueue::getExecutionFlag" << std::endl;
    return mStopFlag;
}
