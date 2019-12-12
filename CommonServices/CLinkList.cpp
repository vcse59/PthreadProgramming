//
//  LinkList.cpp
//  LinkList
//
//  Created by Vivek Yadav on 11/20/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <string>
#include "CLinkList.h"
#include "CMutex.h"
#include "CNode.h"
#include "CLogger.h"

//Contructor declaration
CLinkList::CLinkList(CLogger &pLogger)
	:mLogger(pLogger)
{
    mLogger(DEBUG) << "Entering CLinkList constructor" << std::endl;
    mListHeader = nullptr;
    mIndex = NOT_INITIALIZED;
    mpMutex  =  new CMutex();
    mLogger(DEBUG) << "Exiting CLinkList constructor" << std::endl;
}

//Destructor declaration
CLinkList::~CLinkList()
{
    mLogger(DEBUG) << "Entering CLinkList destructor" << std::endl;
    this->deleteAll();
    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
    mLogger(DEBUG) << "Exiting CLinkList destructor" << std::endl;
}

// Returns Link list length
unsigned int CLinkList::length()
{
    mLogger(DEBUG) << "Entering CLinkList::length" << std::endl;
    unsigned int lCount = 0;
    CNode *lListHeader = mListHeader;
    
    while (lListHeader != nullptr)
    {
        lListHeader = lListHeader->getNextNodeAddress();
        lCount++;
    }
    mLogger(DEBUG) << "Exiting CLinkList::length" << std::endl;
    return lCount;
}

// Insert the node
unsigned int CLinkList::insertNodeAtEnd(void* pData)
{
    mLogger(DEBUG) << "Entering CLinkList::insertNodeAtEnd" << std::endl;
    NULLCHECK(pData, false);
    unsigned int lCount = 0;
    CNode *lListHeader = mListHeader;
    CNode *lLastNode = nullptr;
    
    //Allocate the memory to new node
    CNode *node = new CNode(pData);
    node->setNextNodeAddress(nullptr);
    node->setNodeID(mIndex++);
    
    
    
    while (lListHeader != nullptr)
    {
        lLastNode = lListHeader;
        lListHeader = lListHeader->getNextNodeAddress();
        lCount++;
    }
    
    if (lCount == 0)
    {
        mListHeader = node;
    }
    else
    {
        this->mpMutex->lockMutex();
        lLastNode->setNextNodeAddress(node);
        this->mpMutex->unLockMutex();
    }
    mLogger(DEBUG) << "Exiting CLinkList insertNodeAtEnd" << std::endl;
    return node->getNodeID();
}

// Insert the node at the start
unsigned int CLinkList::insertNodeAtStart(void* pData)
{
    mLogger(DEBUG) << "Entering CLinkList::insertNodeAtStart" << std::endl;
    NULLCHECK(pData, false);
    unsigned int lCount = 0;
    CNode *lListHeader = mListHeader;
    
    //Allocate the memory to new node
    CNode *node = new CNode(pData);
    node->setNextNodeAddress(nullptr);
    node->setNodeID(++mIndex);
    
    while (lListHeader != nullptr)
    {
        lListHeader = lListHeader->getNextNodeAddress();
        lCount++;
    }
    
    if (lCount == 0)
    {
        //std::cout << "LinkList is empty" << std::endl;
        mListHeader = node;
    }
    else
    {
        this->mpMutex->lock();
        node->setNextNodeAddress(mListHeader);
        mListHeader = node;
        this->mpMutex->unlock();
    }
    mLogger(DEBUG) << "Exiting CLinkList insertNodeAtStart" << std::endl;
    return node->getNodeID();
}

// Delete the node from start
bool CLinkList::deleteNodeFromStart()
{
    mLogger(DEBUG) << "Entering CLinkList::deleteNodeFromStart" << std::endl;
    CNode *lListHeader = mListHeader;
    CNode *nextNode    = mListHeader->getNextNodeAddress();
    this->mpMutex->lock();
    mListHeader = nextNode;
    delete lListHeader;
    this->mpMutex->unlock();
    mLogger(DEBUG) << "Exiting CLinkList::deleteNodeFromStart" << std::endl;
    return true;
}

// Delete the node from end
bool CLinkList::deleteNodeFromEnd()
{
    mLogger(DEBUG) << "Entering CLinkList::deleteNodeFromEnd" << std::endl;
    CNode *lListHeader = mListHeader;
    CNode *lprevNode = lListHeader;
    
    // In case LinkList container is empty
    if(lListHeader == nullptr)
    {
        //std::cout << "Linklist container is null" << std::endl;
        return false;
    }

    // In case only one node is left
    if(lListHeader->getNextNodeAddress() == nullptr)
    {
        this->mpMutex->lock();
        delete mListHeader;
        mListHeader = nullptr;
        this->mpMutex->unlock();
        return true;
    }
    
    while (lListHeader->getNextNodeAddress() != nullptr)
    {
        lprevNode = lListHeader;
        lListHeader = lListHeader->getNextNodeAddress();
    }
    this->mpMutex->lock();
    delete lprevNode;
    this->mpMutex->unlock();
    
    mLogger(DEBUG) << "Exiting CLinkList::deleteNodeFromEnd" << std::endl;
    return true;
}

// Delete the node by node value
bool CLinkList::deleteNode(unsigned int pNodeID)
{
    mLogger(DEBUG) << "Entering CLinkList::deleteNode" << std::endl;
    CNode *lListHeader = mListHeader;
    CNode *prevNode    = lListHeader;
    CNode *nextNode    = nullptr;
    
    while (lListHeader != nullptr)
    {
        CNode *lNodeData = (CNode*)lListHeader;
        
        if (lNodeData->getNodeID() == pNodeID)
        {
            nextNode = lListHeader->getNextNodeAddress();
            this->mpMutex->lock();
            delete lListHeader;
            if (prevNode != lListHeader)
            {
                prevNode->setNextNodeAddress(nextNode);
                
            }
            else
            {
                mListHeader = nextNode;
            }
            this->mpMutex->unlock();
            break;
        }
        this->mpMutex->lock();
        prevNode = lListHeader;
        this->mpMutex->unlock();
        lListHeader = lListHeader->getNextNodeAddress();
    }
    mLogger(DEBUG) << "Exiting CLinkList::deleteNode" << std::endl;
    return true;
}

// Empty the complete list
void CLinkList::deleteAll()
{
    mLogger(DEBUG) << "Entering CLinkList::deleteAll" << std::endl;
    CNode *lListHeader = mListHeader;
    CNode *nextNode    = nullptr;
    
    while (lListHeader != nullptr)
    {
        nextNode = lListHeader->getNextNodeAddress();
        this->mpMutex->lock();
        delete lListHeader;
        lListHeader = nextNode;
        this->mpMutex->unlock();
    }
    this->mpMutex->lock();
    mListHeader = nullptr;
    this->mpMutex->unlock();
    mLogger(DEBUG) << "Exiting CLinkList::deleteAll" << std::endl;
}

//print all Link List data
std::string CLinkList::printData()
{
    mLogger(DEBUG) << "Entering CLinkList::printData" << std::endl;
    CNode *lListHeader = mListHeader;
    unsigned int lCount = 0;
    std::string lPrintPrefix = "Link List contents are : ";
    std::string lItemString = "\n";
    while (lListHeader != nullptr)
    {
        lCount++;
        CNode *lNodeData = (CNode *)lListHeader;
        lItemString += "Item " + std::to_string(lCount) + " : " + std::to_string(lNodeData->getNodeID()) + "\n";
        lListHeader = lListHeader->getNextNodeAddress();
    }
    
    if (lCount == 0)
    {
        lItemString = "<EMPYT>\n";
    }
    mLogger(DEBUG) << "Exiting CLinkList::printData" << std::endl;
    return lPrintPrefix + lItemString;
}

// Reverse the linked list
bool CLinkList::reverse()
{
    mLogger(DEBUG) << "Entering CLinkList::reverse" << std::endl;
    CNode *lLinkListHeader = mListHeader;
    CNode *lReverseList = nullptr;
    CNode *lTempNode = nullptr;
    CNode *lNextNode = nullptr;
    
    while (lLinkListHeader != nullptr)
    {
        lTempNode = lLinkListHeader->getNextNodeAddress();
        
        this->mpMutex->lock();
        // Insert the node in start in separate list
        if (lReverseList != nullptr)
        {
            lNextNode = lReverseList;
        }
        lReverseList = lLinkListHeader;
        lReverseList->setNextNodeAddress(lNextNode);
        lLinkListHeader = lTempNode;
        this->mpMutex->unlock();
    }
    
    this->mpMutex->lock();
    mListHeader = lReverseList;
    this->mpMutex->unlock();
    mLogger(DEBUG) << "Exiting CLinkList::reverse" << std::endl;
    return true;
}

// Fetch the node by node ID
void * CLinkList::fetchNode(unsigned int pNodeID)
{
    mLogger(DEBUG) << "Entering CLinkList::fetchNode" << std::endl;
    CNode *lListHeader = mListHeader;
    CNode *lNodeData = nullptr;
    
    while (lListHeader != nullptr)
    {
        lNodeData = (CNode*)lListHeader;
        
        if (lNodeData->getNodeID() == pNodeID)
        {
            break;
        }
        lListHeader = lListHeader->getNextNodeAddress();
    }
    mLogger(DEBUG) << "Exiting CLinkList::fetchNode" << std::endl;
    return lNodeData->getValue();
}

// Overloading subscript operator
void * CLinkList::getDataByIndex(const unsigned int pIndex)
{
    mLogger(DEBUG) << "Entering CLinkList::getDataByIndex" << std::endl;
    unsigned int lCount = 0;
    CNode *lListHeader = mListHeader;
    CNode *lNodeData = nullptr;
    
    
    while (lListHeader != nullptr)
    {
        lNodeData = lListHeader;
        if (lCount++ == pIndex)
        {
            break;
        }
        lListHeader = lListHeader->getNextNodeAddress();
    }
    if (lListHeader == nullptr)
    {
        return nullptr;
    }
    mLogger(DEBUG) << "Exiting CLinkList::getDataByIndex" << std::endl;
    return lNodeData->getValue();
}

// Fetch first node
void* CLinkList::begin()
{
    mLogger(DEBUG) << "Entering CLinkList::begin" << std::endl;
    mLogger(DEBUG) << "Exiting CLinkList::begin" << std::endl;
    return (char*)(this->getDataByIndex(0));
}

// Fetch end node
void* CLinkList::end()
{
    mLogger(DEBUG) << "Entering CLinkList::end" << std::endl;
    mLogger(DEBUG) << "Exiting CLinkList::end" << std::endl;
    return (char*)(this->getDataByIndex(this->length()-1));
}
