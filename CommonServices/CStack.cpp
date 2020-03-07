//
//  CStack.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 3/4/20.
//  Copyright © 2020 Vivek Yadav. All rights reserved.
//

#include "CStack.h"
#include <unistd.h>
#include <cstring>
#include "CLogger.h"
#include "CommonDefs.h"

using namespace CommonServices::Container;
using namespace CommonServices::Logger;

CStack::CStack(CommonServices::Logger::CLogger& pLogger)
    :mLogger(pLogger)
{
    mLogger(DEBUG_LOG) << "Entering CStack constructor" << std::endl;
    mStackContainer = new CLinkList(mLogger);
    mLogger(DEBUG_LOG) << "Exiting CStack constructor" << std::endl;
}

CStack::~CStack()
{
    mLogger(DEBUG_LOG) << "Entering CStack destructor" << std::endl;
    if (mStackContainer != nullptr)
    {
        delete mStackContainer;
    }
    mStackContainer = nullptr;
    mLogger(DEBUG_LOG) << "Exiting CStack destructor" << std::endl;
}

bool CStack::push(char* pData)
{
    mLogger(DEBUG_LOG) << "Entering CStack::push" << std::endl;
    mStackContainer->insertNodeAtStart((void*) pData);
    mLogger(DEBUG_LOG) << "Exiting CStack::push" << std::endl;
    return true;
}

char* CStack::pop()
{
    mLogger(DEBUG_LOG) << "Entering CStack::pop" << std::endl;
    void *lData = mStackContainer->begin();
    
    if (lData == nullptr)
    {
        mLogger(ERROR_LOG) << "Stack is empty...." << std::endl;
        return nullptr;
    }
    
    if (mStackContainer->deleteNodeFromStart() == true)
    {
        mLogger(INFO_LOG) << "Stack Data is successfully popped" << std::endl;
    }
    mLogger(DEBUG_LOG) << "Exiting CStack::pop" << std::endl;
    return (char*)lData;
}

unsigned int CStack::size()
{
    mLogger(DEBUG_LOG) << "Entering CStack::size" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CStack::size" << std::endl;
    return mStackContainer->length();
}
