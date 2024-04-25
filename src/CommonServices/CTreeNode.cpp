//
//  CTreeNode.cpp
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "CommonServices/CommonDefs.h"
#include "CommonServices/CTreeNode.h"

using namespace CommonServices::Data;
using namespace CommonServices::CommonDefinitions;
using namespace CommonServices::Services;

CTreeNode::CTreeNode(void* pData, unsigned int pNodeID)
	:mDataItem(pData),
    mLeftNodePtr(nullptr),
	mRightNodePtr(nullptr),
	mNodeId(pNodeID),
    mMutex(new CommonServices::Services::CMutex())
{}

CTreeNode::~CTreeNode()
{
    mDataItem = nullptr;
    mLeftNodePtr = nullptr;
    mRightNodePtr = nullptr;

    if(mMutex != nullptr)
    {
        delete mMutex;
    }
    mMutex = nullptr;
}

void* CTreeNode::getValue()
{
    return mDataItem;
}

void CTreeNode::setLeftNodeAddress(CTreeNode *nodeAddr)
{
    mMutex->lockMutex();
    mLeftNodePtr = nodeAddr;
    mMutex->unLockMutex();
}

void CTreeNode::setRightNodeAddress(CTreeNode *nodeAddr)
{
    mMutex->lockMutex();
    mRightNodePtr = nodeAddr;
    mMutex->unLockMutex();
}

CTreeNode* CTreeNode::getLeftNodeAddress()
{
    return mLeftNodePtr;
}

CTreeNode* CTreeNode::getRightNodeAddress()
{
    return mRightNodePtr;
}

unsigned int CTreeNode::getNodeID()
{
    return mNodeId;
}
