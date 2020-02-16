//
//  CBinarySearchTree.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 1/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//
#include <unistd.h>
#include <cstring>
#include "CBinarySearchTree.h"
#include "CLogger.h"
#include "CommonDefs.h"
#include "CQueue.h"

using namespace CommonServices::Services;
using namespace CommonServices::Logger;
using namespace CommonServices::Data;


CBinarySearchTree::CBinarySearchTree(CommonServices::Logger::CLogger &pLogger)
    :mLogger(pLogger)
{
    mLogger(DEBUG) << "Entering CBinarySearchTree constructor" << std::endl;
    mBSTRoot = nullptr;
    mLogger(DEBUG) << "Exiting CBinarySearchTree constructor" << std::endl;
}

CBinarySearchTree::~CBinarySearchTree()
{
    mLogger(DEBUG) << "Entering CBinarySearchTree destructor" << std::endl;
    mLogger(DEBUG) << "Exiting CBinarySearchTree destructor" << std::endl;
}

CTreeNode* CBinarySearchTree::getRootNode()
{
    mLogger(DEBUG) << "Entering CBinarySearchTree::getRootNode" << std::endl;
    mLogger(DEBUG) << "Exiting CBinarySearchTree::getRootNode" << std::endl;
    return mBSTRoot;
}

//Tree operations
bool CBinarySearchTree::insertData(CommonServices::Data::CTreeNode *pNode, unsigned int pNodeId)
{
    mLogger(DEBUG) << "Entering CBinarySearchTree::insertData" << std::endl;

    if (mBSTRoot == nullptr)
    {
	mBSTRoot  =  pNode;
    }
    else
    {
	CTreeNode *tempNode = mBSTRoot;
	CTreeNode* leafNode = mBSTRoot;
	unsigned int *nodePtr = (unsigned int *)pNode->getValue();
	unsigned int nodeValue = *nodePtr;

	while (tempNode != nullptr)
	{
	    leafNode = tempNode;
	    unsigned int * tempNodeValue = (unsigned int*)tempNode->getValue();
	    if (nodeValue <= (*tempNodeValue))
	    {
		tempNode = tempNode->getLeftNodeAddress();
	    }
	    else
	    {
		tempNode = tempNode->getRightNodeAddress();
	    }
	}

	unsigned int *leafNodeValue = (unsigned int*)leafNode->getValue();
	if (nodeValue <= (*leafNodeValue))
	{
	    leafNode->setLeftNodeAddress(pNode);
	}
	else
	{
	    leafNode->setRightNodeAddress(pNode);
	}
	leafNode->setNodeID(pNodeId);
    }

    mLogger(DEBUG) << "Exiting CBinarySearchTree::insertData" << std::endl;
    return true;
}

bool CBinarySearchTree::erase()
{
    mLogger(DEBUG) << "Entering CBinarySearchTree::erase" << std::endl;
    mLogger(DEBUG) << "Exiting CBinarySearchTree::erase" << std::endl;
    return true;
}

bool CBinarySearchTree::search(const CTreeNode *pNode)
{
    mLogger(DEBUG) << "Entering CBinarySearchTree::search" << std::endl;
    mLogger(DEBUG) << "Exiting CBinarySearchTree::search" << std::endl;
    return true;
}
		
bool CBinarySearchTree::eraseItem(const CTreeNode *pNode)
{
    mLogger(DEBUG) << "Entering CBinarySearchTree::eraseItem" << std::endl;
    mLogger(DEBUG) << "Exiting CBinarySearchTree eraseItem" << std::endl;
    return true;
}

//Tree traversal using recursion
void CBinarySearchTree::preorder_recursive(CTreeNode *pHeadNode)
{
    if (pHeadNode != nullptr)
    {
	unsigned int *nodePtr = (unsigned int*)pHeadNode->getValue();
	std::cout << *nodePtr << " ";
	this->preorder_recursive(pHeadNode->getLeftNodeAddress());
	this->preorder_recursive(pHeadNode->getRightNodeAddress());
    }
}

void CBinarySearchTree::inorder_recursive(CTreeNode *pHeadNode)
{
    if (pHeadNode != nullptr)
    {
	this->inorder_recursive(pHeadNode->getLeftNodeAddress());
	unsigned int *nodePtr = (unsigned int*)pHeadNode->getValue();
	std::cout << *nodePtr << " ";
	this->inorder_recursive(pHeadNode->getRightNodeAddress());
    }
}
		
void CBinarySearchTree::postorder_recursive(CTreeNode *pHeadNode)
{
    if (pHeadNode != nullptr)
    {
	this->postorder_recursive(pHeadNode->getLeftNodeAddress());
	this->postorder_recursive(pHeadNode->getRightNodeAddress());
	unsigned int *nodePtr = (unsigned int*)pHeadNode->getValue();
	std::cout << *nodePtr << " ";
    }
}

//Tree traversal using queue
void CBinarySearchTree::preorder_queue(CTreeNode *pNode)
{
}

void CBinarySearchTree::inorder_queue(CTreeNode *pNode)
{
}

void CBinarySearchTree::postorder_queue(CTreeNode *pNode)
{
}
