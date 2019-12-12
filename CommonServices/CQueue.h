//
//  CQueue.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 1/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CQueue_h
#define CQueue_h

#include "CMutex.h"

class CPipelineData;
class CLinkList;
class CLogger;

class CQueue
{
    
public:
    CQueue(CLogger& pLogger);
    ~CQueue();
    
    bool isEmpty();
    
    unsigned int size();
    
    void push_front(CPipelineData* pData, unsigned int pDataId);
    
    void push_back(CPipelineData* pData, unsigned int pDataId);
    
    void erase(unsigned dataId);

    CPipelineData* getQueueData(unsigned int pIndex);
    
    void pop_front();
    
    void pop_back();
    
    void setExecutionFlag(bool isStop);
    
    bool getExecutionFlag();
    
private:
    CLogger&	mLogger;
    CLinkList*  dQueueContainer;
    bool        mStopFlag;
    CMutex*     mpMutex;
};
#include <stdio.h>

#endif /* CQueue_hpp */
