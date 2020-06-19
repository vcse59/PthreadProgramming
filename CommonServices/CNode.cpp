//
//  Node.cpp
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <stdio.h>
#include "CommonDefs.h"
#include "CNode.h"
#include "CMutex.h"
#include <iostream>

using namespace CommonServices::Data;
using namespace CommonServices::CommonDefinitions;
using namespace CommonServices::Services;

CNode::CNode(void* pData)
:mDataItem(pData), mNodePtr(nullptr)
{
    mNodeId = NOT_INITIALIZED;
    mpMutex = new CommonServices::Services::CMutex();
}

CNode::~CNode()
{
    mDataItem = nullptr;
    mNodePtr = nullptr;
    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
}

void* CNode::getValue()
{
    return mDataItem;
}

void CNode::setNextNodeAddress(CNode *nodeAddr)
{
    mpMutex->lockMutex();
    mNodePtr = nodeAddr;
    mpMutex->unLockMutex();
}

CNode* CNode::getNextNodeAddress()
{
    return mNodePtr;
}

void CNode::setNodeID(unsigned int pNodeId)
{
    mpMutex->lockMutex();
    mNodeId = pNodeId;
    mpMutex->unLockMutex();
}

unsigned int CNode::getNodeID()
{
    return mNodeId;
}
