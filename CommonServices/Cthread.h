//
//  Cthread.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef Cthread_h
#define Cthread_h

#include <stdio.h>
#include "CommonDefs.h"
#include "CMutex.h"

class Ctask;
class CLinkList;
class CLogger;

class Cthread
{
public:
    Cthread(CLogger &pLogger);
    ~Cthread();
    
    void startThread(unsigned int threadId);
    unsigned int addThread(Ctask*);
    void join();
    void stopThread(unsigned int threadId);
    static void* threadCallback(void *data);
    
    void printData();
    threadContext_t *mThreadContext_p[32];
    unsigned int mThreadId;
    CMutex*  mpMutex;
    CLinkList* s_threadPool;
    CLogger &mLogger;
};

#endif /* Cthread_hpp */
