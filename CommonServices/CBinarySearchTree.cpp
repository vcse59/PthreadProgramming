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
#include "CStack.h"

using namespace CommonServices::Services;
using namespace CommonServices::Logger;
using namespace CommonServices::Data;


CBinarySearchTree::CBinarySearchTree(CommonServices::Logger::CLogger &pLogger)
    :mLogger(pLogger)
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree constructor" << std::endl;
    mBSTRoot = nullptr;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree constructor" << std::endl;
}

CBinarySearchTree::~CBinarySearchTree()
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree destructor" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree destructor" << std::endl;
}

CTreeNode* CBinarySearchTree::getRootNode()
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree::getRootNode" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree::getRootNode" << std::endl;
    return mBSTRoot;
}

//Tree operations
bool CBinarySearchTree::insertData(CommonServices::Data::CTreeNode *pNode, unsigned int pNodeId)
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree::insertData" << std::endl;

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

    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree::insertData" << std::endl;
    return true;
}

bool CBinarySearchTree::erase()
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree::erase" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree::erase" << std::endl;
    return true;
}

bool CBinarySearchTree::search(const CTreeNode *pNode)
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree::search" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree::search" << std::endl;
    return true;
}
		
bool CBinarySearchTree::eraseItem(const CTreeNode *pNode)
{
    mLogger(DEBUG_LOG) << "Entering CBinarySearchTree::eraseItem" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CBinarySearchTree eraseItem" << std::endl;
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
void CBinarySearchTree::preorder_nonrecursive()
{
    CTreeNode *rootNode = mBSTRoot;
    CommonServices::Container::CStack*  lStackContainer = new CommonServices::Container::CStack(mLogger);

    while (true)
    {
        while (rootNode != nullptr)
        {
            unsigned int * tempNodeValue = (unsigned int*)rootNode->getValue();
            std::cout << *tempNodeValue << std::endl;
            lStackContainer->push((char*)rootNode);
            rootNode = rootNode->getLeftNodeAddress();
        }
        
        if (lStackContainer->size() == 0)
            break;
        
        CTreeNode *tempNode = (CTreeNode *) lStackContainer->pop();
        rootNode = tempNode->getRightNodeAddress();
    }
    
    if (lStackContainer != nullptr)
    {
        delete lStackContainer;
    }
    lStackContainer = nullptr;
}

void CBinarySearchTree::inorder_nonrecursive()
{
    CTreeNode *rootNode = mBSTRoot;
    CommonServices::Container::CStack*  lStackContainer = new CommonServices::Container::CStack(mLogger);

    while (true)
    {
        while (rootNode != nullptr)
        {
            lStackContainer->push((char*)rootNode);
            rootNode = rootNode->getLeftNodeAddress();
        }
        
        if (lStackContainer->size() == 0)
            break;
        
        CTreeNode *tempNode = (CTreeNode *) lStackContainer->pop();
        unsigned int * tempNodeValue = (unsigned int*)tempNode->getValue();
        std::cout << *tempNodeValue << std::endl;
        rootNode = tempNode->getRightNodeAddress();
    }
    
    if (lStackContainer != nullptr)
    {
        delete lStackContainer;
    }
    lStackContainer = nullptr;
}

void CBinarySearchTree::postorder_nonrecursive()
{
    CTreeNode *rootNode = mBSTRoot;
    CommonServices::Container::CStack*  lStackContainer = new CommonServices::Container::CStack(mLogger);
    CommonServices::Container::CStack*  lStackStorage = new CommonServices::Container::CStack(mLogger);

    while (true)
    {
        while (rootNode != nullptr)
        {
            lStackStorage->push((char*)rootNode);
            lStackContainer->push((char*)rootNode);
            rootNode = rootNode->getRightNodeAddress();
        }
        
        if (lStackContainer->size() == 0)
            break;
        
        CTreeNode *tempNode = (CTreeNode *) lStackContainer->pop();
        rootNode = tempNode->getLeftNodeAddress();
    }
    
    while (lStackStorage->size() > 0)
    {
        CTreeNode *tempNode = (CTreeNode *) lStackStorage->pop();
        unsigned int * tempNodeValue = (unsigned int*)tempNode->getValue();
        std::cout << *tempNodeValue << std::endl;
    }
    
    if (lStackContainer != nullptr)
    {
        delete lStackContainer;
    }
    lStackContainer = nullptr;
}
