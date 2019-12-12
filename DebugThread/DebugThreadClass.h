//
//  DebugThreadClass.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 3/1/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef DebugThreadClass_hpp
#define DebugThreadClass_hpp

#include <stdio.h>
#include <iostream>
#include "../CommonServices/Ctask.h"

class CQueue;
class CLogger;

class DebugThread : public Ctask
{
public:
    DebugThread(std::string pTaskName, CLogger& pLogger, 
		    CQueue *pPipeline, char* pThreadData);
    ~DebugThread();
    
    void run();
    void cleanup();
    
private:
    CLogger& mLogger;
    char *mThreadData;
};

#endif /* DebugThreadClass_hpp */
