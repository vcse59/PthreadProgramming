//
//  CTreeNode.cpp
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <stdio.h>
#include "CommonDefs.h"
#include "CTreeNode.h"
#include <iostream>

using namespace CommonServices::Data;
using namespace CommonServices::CommonDefinitions;
using namespace CommonServices::Services;

CTreeNode::CTreeNode(void* pData)
:mDataItem(pData), mLeftNodePtr(nullptr), mRightNodePtr(nullptr)
{
    mNodeId = NOT_INITIALIZED;
}

CTreeNode::~CTreeNode()
{
    mDataItem = nullptr;
    mLeftNodePtr = nullptr;
    mRightNodePtr = nullptr;
}

void* CTreeNode::getValue()
{
    return mDataItem;
}

void CTreeNode::setLeftNodeAddress(CTreeNode *nodeAddr)
{
    mLeftNodePtr = nodeAddr;
}

void CTreeNode::setRightNodeAddress(CTreeNode *nodeAddr)
{
    mRightNodePtr = nodeAddr;
}

CTreeNode* CTreeNode::getLeftNodeAddress()
{
    return mLeftNodePtr;
}

CTreeNode* CTreeNode::getRightNodeAddress()
{
    return mRightNodePtr;
}

void CTreeNode::setNodeID(unsigned int pNodeId)
{
    mNodeId = pNodeId;
}

unsigned int CTreeNode::getNodeID()
{
    return mNodeId;
}
