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

CNode::CNode(void* pData)
:mDataItem(pData), mNodePtr(nullptr)
{
    //std::cout << "Calling CNode constructor" << std::endl;
    mNodeId = NOT_INITIALIZED;
}

CNode::~CNode()
{
    //std::cout << "Calling CNode destructor" << std::endl;
    mDataItem = nullptr;
    mNodePtr = nullptr;
}

void* CNode::getValue()
{
    return mDataItem;
}

void CNode::setNextNodeAddress(CNode *nodeAddr)
{
    mNodePtr = nodeAddr;
}

CNode* CNode::getNextNodeAddress()
{
    return mNodePtr;
}

void CNode::setNodeID(unsigned int pNodeId)
{
    mNodeId = pNodeId;
}

unsigned int CNode::getNodeID()
{
    return mNodeId;
}
