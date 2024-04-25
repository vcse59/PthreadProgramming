//
//  CQueue.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 1/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CQueue_h
#define CQueue_h

#include <stdio.h>
#include "AppData/CPipelineDataClass.h"
#include "CommonServices/CMutex.h"
#include "CommonServices/CLinkList.h"
#include "CommonServices/CLogger.h"

namespace CommonServices
{
    namespace Container
    {
        class CQueue
        {

            public:
            CQueue(Logger::CLogger& pLogger);
            ~CQueue();

            bool isEmpty();

            unsigned int size();

            void push_front(char* pData, unsigned int pDataId);

            void push_back(char* pData, unsigned int pDataId);

            void erase(unsigned dataId);

            char* pop_front();

            char* pop_back();

            void setExecutionFlag(bool isStop);

            bool getExecutionFlag();

            private:
            CommonServices::Logger::CLogger&	mLogger;
            CommonServices::Container::CLinkList*  dQueueContainer;
            bool        mStopFlag;
            CommonServices::Services::CMutex*     mpMutex;
        };
    }
}

#endif /* CQueue_h */
