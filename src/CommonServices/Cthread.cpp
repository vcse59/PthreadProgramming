//
//  Cthread.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>
#include "CommonServices/Cthread.h"

using namespace std;
using namespace CommonServices::Services;
using namespace CommonServices::Logger;

Cthread::Cthread(CommonServices::Logger::CLogger &pLogger) : mLogger(pLogger)
{
    mLogger(DEBUG_LOG) << "Entering Cthread constructor" << endl;

    mpMutex  =  new CMutex();
#ifndef TEST_CODE
    s_threadPool = new CommonServices::Container::CLinkList(pLogger);
#else
    mThreadId = 0;
#endif
    mLogger(DEBUG_LOG) << "Exiting Cthread constructor" << endl;
}

Cthread::~Cthread()
{
    mLogger(DEBUG_LOG) << "Entering Cthread destructor " << endl;
    unsigned int lCount = 0;
    #ifndef TEST_CODE
    unsigned int lThreadCount = s_threadPool->length();
    #else
    unsigned int lThreadCount = mThreadId;
    #endif
    for( ; lCount < lThreadCount; ++lCount)
    {
	#ifndef TEST_CODE
        CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p =
        (CommonServices::CommonDefinitions::threadContext_t *)(s_threadPool->getDataByIndex(lCount));
	#else
        CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p = mThreadContext_p[lCount];
	#endif
        delete (lThreadContext_p->task_p);
        lThreadContext_p->task_p = nullptr;
        free(lThreadContext_p);
	#ifndef TEST_CODE
        lThreadContext_p = nullptr;
	#else
        mThreadContext_p[lCount] = nullptr;
	#endif
    }

    #ifndef TEST_CODE
    if (s_threadPool != nullptr)
        delete s_threadPool;
    s_threadPool = nullptr;
    #else
    mThreadId = 0;
    #endif
    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
    mLogger(DEBUG_LOG) << "Exiting Cthread destructor " << endl;
}

unsigned int Cthread::addThread(Ctask* pTask)
{
    mLogger(DEBUG_LOG) << "Entering Cthread::addThread" << endl;
    mLogger(INFO_LOG) << "Cthread::addThread : " << sizeof(CommonServices::CommonDefinitions::threadContext_t) << " Task name is : " << pTask->getTaskName()<< endl;
#ifdef TEST_CODE
    this->printData();
    mLogger(INFO_LOG) << "\n===== mThreadId: " << mThreadId << "\n" << endl;
#endif

    // Allocate and initialize lThreadContext_p
    CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p = 
	(CommonServices::CommonDefinitions::threadContext_t *)malloc(sizeof(CommonServices::CommonDefinitions::threadContext_t));
    memset((void*)lThreadContext_p, 0, sizeof (CommonServices::CommonDefinitions::threadContext_t));
    
    if (lThreadContext_p ==  NULL)
    {
        cerr << "Malloc failure : threadContext_p" << endl;
        return -1;
    }

    lThreadContext_p->task_p = pTask;

#ifndef TEST_CODE
    lThreadContext_p->threadId = s_threadPool->insertNodeAtEnd((void*)lThreadContext_p);
#else
    mLogger(INFO_LOG) << "\n***====*** lThreadContext_p: " << lThreadContext_p << "\n" << endl;
    mpMutex->lockMutex();
    lThreadContext_p->threadId = mThreadId;
    mThreadContext_p[mThreadId++] = lThreadContext_p;
    mpMutex->unLockMutex();
#endif
#ifdef TEST_CODE
    this->printData();
    mLogger(INFO_LOG) << "\n****** mThreadId: " << mThreadId << "\n" << endl;
#endif
    mLogger(DEBUG_LOG) << "Exiting Cthread::addThread" << endl;
    return lThreadContext_p->threadId;
}

void Cthread::startThread(unsigned int threadId)
{
    mLogger(DEBUG_LOG) << "Entering Cthread::startThread" << endl;
#ifndef TEST_CODE
    CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p = 
	(CommonServices::CommonDefinitions::threadContext_t*)s_threadPool->fetchNode(threadId);
    
    unsigned int lThreadId = pthread_create(&(lThreadContext_p->mThreadStruct), NULL, Cthread::threadCallback, (void*)lThreadContext_p->task_p);
    if (lThreadId != 0)
    {
        cerr << "pthread_create failure : " <<  endl;
        return;
    }
#else
    unsigned int lThreadId = pthread_create(&(mThreadContext_p[threadId]->mThreadStruct), NULL, Cthread::threadCallback, (void*)(mThreadContext_p[threadId]->task_p));
    if (lThreadId != 0)
    {
        cerr << "pthread_create failure : " <<  endl;
        return;
    }
#endif
    mLogger(DEBUG_LOG) << "Exiting Cthread::startThread" << endl;
}

void Cthread::stopThread(unsigned int threadId)
{
    mLogger(DEBUG_LOG) << "Entering Cthread::stopThread" << endl;
#ifndef TEST_CODE
    CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p = 
	(CommonServices::CommonDefinitions::threadContext_t*)s_threadPool->fetchNode(threadId);
    lThreadContext_p->task_p->cleanup();
#else
    mpMutex->lockMutex();
    mThreadContext_p[threadId]->task_p->cleanup();
    mpMutex->unLockMutex();
#endif
    mLogger(DEBUG_LOG) << "Exiting Cthread::stopThread" << endl;
}

void* Cthread::threadCallback(void *data)
{
    Ctask *task_p = (Ctask*) data;
    task_p->run();
    return nullptr;
}

void Cthread::join()
{
    mLogger(DEBUG_LOG) << "Entering Cthread::join" << endl;
    void *ret = nullptr;
#ifndef TEST_CODE
    unsigned int lThreadCount = s_threadPool->length();
    mLogger(INFO_LOG) << "Total number of active threads : " << lThreadCount << endl;
    for(unsigned int lCount = 0 ; lCount < lThreadCount; lCount++)
    {
        s_threadPool->printData();
        CommonServices::CommonDefinitions::threadContext_t *lThreadContext_p = 
	    (CommonServices::CommonDefinitions::threadContext_t*)(s_threadPool->getDataByIndex(lCount));
        mLogger(INFO_LOG) << "Cthread::join--> Thread ID : " << lThreadContext_p->threadId<< endl;
        if (pthread_join(lThreadContext_p->mThreadStruct, &ret) != 0) {
            mLogger(ERROR_LOG) << "pthread_join() ERROR_LOG" << std::endl;
            exit(3);
        }
    }
#else
    mLogger(INFO_LOG) << "Total number of active threads : " << mThreadId << endl;
    for( unsigned int lCount = 0; lCount < mThreadId; lCount++)
    {
        CommonServices::CommonDefinitions::threadContext_t*    lThreadContext_p    =    mThreadContext_p[lCount];
        mLogger(INFO_LOG) << "lCount : " << lCount<< endl;
        mLogger(INFO_LOG) << "Cthread::join--> Thread Name : " << lThreadContext_p->task_p->getTaskName()<< endl;
        if (pthread_join(lThreadContext_p->mThreadStruct, &ret) != 0) {
            mLogger(ERROR_LOG) << "pthread_join() ERROR_LOG" << std::endl;
            exit(3);
        }
    }
#endif
    mLogger(DEBUG_LOG) << "Exiting Cthread::join" << endl;
}

#ifdef TEST_CODE
void Cthread::printData()
{
    mLogger(DEBUG_LOG) << "Entering Cthread::printData" << endl;
    for( unsigned int lCount = 0; lCount < mThreadId; lCount++)
    {
        CommonServices::CommonDefinitions::threadContext_t*    lThreadContext_p    =    mThreadContext_p[lCount];
        mLogger(INFO_LOG) << "\n+++++Thread Name : " << lThreadContext_p<< "\n" << endl;
    }
    mLogger(DEBUG_LOG) << "Exiting Cthread::printData" << endl;
}
#endif
