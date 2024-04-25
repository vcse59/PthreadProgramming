//
//  CStack.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 3/4/20.
//  Copyright © 2020 Vivek Yadav. All rights reserved.
//

#ifndef CStack_h
#define CStack_h

#include <stdio.h>
#include "AppData/CPipelineDataClass.h"
#include "CommonServices/CMutex.h"
#include "CommonServices/CLinkList.h"
#include "CommonServices/CLogger.h"

namespace CommonServices
{
    namespace Container
    {
        class CStack
        {
        public:
            CStack(CommonServices::Logger::CLogger& pLogger);
            ~CStack();
            
            bool push(char* pData);
            char* pop();
            unsigned int size();
            
        private:
            CStack(const CStack&);
            CStack& operator=(const CStack&);
            
            CommonServices::Container::CLinkList    *mStackContainer;
            CommonServices::Logger::CLogger&        mLogger;
            CommonServices::Services::CMutex*       mMutex;
        };
    }
}

#endif /* CStack_h */
