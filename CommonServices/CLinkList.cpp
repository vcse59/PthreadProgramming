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
#include "CommonDefs.h"
#include "CLogger.h"

using namespace CommonServices::Container;
using namespace CommonServices::Logger;

//Contructor declaration
CommonServices::Container::CLinkList::CLinkList(CommonServices::Logger::CLogger &pLogger)
	:mLogger(pLogger)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList constructor" << std::endl;
    mListHeader = nullptr;
    mIndex = NOT_INITIALIZED;
    mpMutex  =  new CommonServices::Services::CMutex();
    mLogger(DEBUG_LOG) << "Exiting CLinkList constructor" << std::endl;
}

//Destructor declaration
CommonServices::Container::CLinkList::~CLinkList()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList destructor" << std::endl;
    this->deleteAll();
    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
    mLogger(DEBUG_LOG) << "Exiting CLinkList destructor" << std::endl;
}

// Returns Link list length
unsigned int CommonServices::Container::CLinkList::length()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::length" << std::endl;
    unsigned int lCount = 0;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    
    while (lListHeader != nullptr)
    {
        lListHeader = lListHeader->getNextNodeAddress();
        lCount++;
    }
    mLogger(DEBUG_LOG) << "Exiting CLinkList::length" << std::endl;
    return lCount;
}

// Insert the node
unsigned int CommonServices::Container::CLinkList::insertNodeAtEnd(void* pData)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::insertNodeAtEnd" << std::endl;
    NULLCHECK(pData, false);
    unsigned int lCount = 0;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *lLastNode = nullptr;
    
    //Allocate the memory to new node
    CommonServices::Data::CNode *node = new CommonServices::Data::CNode(pData);
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList insertNodeAtEnd" << std::endl;
    return node->getNodeID();
}

// Insert the node at the start
unsigned int CommonServices::Container::CLinkList::insertNodeAtStart(void* pData)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::insertNodeAtStart" << std::endl;
    NULLCHECK(pData, false);
    unsigned int lCount = 0;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    
    //Allocate the memory to new node
    CommonServices::Data::CNode *node = new CommonServices::Data::CNode(pData);
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList insertNodeAtStart" << std::endl;
    return node->getNodeID();
}

// Delete the node from start
bool CommonServices::Container::CLinkList::deleteNodeFromStart()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::deleteNodeFromStart" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *nextNode    = mListHeader->getNextNodeAddress();
    this->mpMutex->lock();
    mListHeader = nextNode;
    delete lListHeader;
    lListHeader = nullptr;
    this->mpMutex->unlock();
    mLogger(DEBUG_LOG) << "Exiting CLinkList::deleteNodeFromStart" << std::endl;
    return true;
}

// Delete the node from end
bool CommonServices::Container::CLinkList::deleteNodeFromEnd()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::deleteNodeFromEnd" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *lprevNode = lListHeader;
    
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
    
    mLogger(DEBUG_LOG) << "Exiting CLinkList::deleteNodeFromEnd" << std::endl;
    return true;
}

// Delete the node by node value
bool CommonServices::Container::CLinkList::deleteNode(unsigned int pNodeID)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::deleteNode" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *prevNode    = lListHeader;
    CommonServices::Data::CNode *nextNode    = nullptr;
    
    while (lListHeader != nullptr)
    {
        CommonServices::Data::CNode *lNodeData = (CommonServices::Data::CNode*)lListHeader;
        
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList::deleteNode" << std::endl;
    return true;
}

// Empty the complete list
void CommonServices::Container::CLinkList::deleteAll()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::deleteAll" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *nextNode    = nullptr;
    
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList::deleteAll" << std::endl;
}

//print all Link List data
std::string CommonServices::Container::CLinkList::printData()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::printData" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    unsigned int lCount = 0;
    std::string lPrintPrefix = "Link List contents are : ";
    std::string lItemString = "\n";
    while (lListHeader != nullptr)
    {
        lCount++;
        CommonServices::Data::CNode *lNodeData = (CommonServices::Data::CNode *)lListHeader;
        lItemString += "Item " + std::to_string(lCount) + " : " + std::to_string(lNodeData->getNodeID()) + "\n";
        mLogger(INFO_LOG) << lItemString << std::endl;
        lListHeader = lListHeader->getNextNodeAddress();
    }
    
    if (lCount == 0)
    {
        lItemString = "<EMPYT>\n";
    }
    mLogger(DEBUG_LOG) << "Exiting CLinkList::printData" << std::endl;
    return lPrintPrefix + lItemString;
}

// Reverse the linked list
bool CommonServices::Container::CLinkList::reverse()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::reverse" << std::endl;
    CommonServices::Data::CNode *lLinkListHeader = mListHeader;
    CommonServices::Data::CNode *lReverseList = nullptr;
    CommonServices::Data::CNode *lTempNode = nullptr;
    CommonServices::Data::CNode *lNextNode = nullptr;
    
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList::reverse" << std::endl;
    return true;
}

// Fetch the node by node ID
void * CommonServices::Container::CLinkList::fetchNode(unsigned int pNodeID)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::fetchNode" << std::endl;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *lNodeData = nullptr;
    
    while (lListHeader != nullptr)
    {
        lNodeData = (CommonServices::Data::CNode*)lListHeader;
        
        if (lNodeData->getNodeID() == pNodeID)
        {
            break;
        }
        lListHeader = lListHeader->getNextNodeAddress();
    }
    
    mLogger(DEBUG_LOG) << "Exiting CLinkList::fetchNode" << std::endl;
    if (lNodeData == nullptr)
    {
        return nullptr;
    }
    else
    {
        return lNodeData->getValue();
    }
}

// Overloading subscript operator
void * CommonServices::Container::CLinkList::getDataByIndex(const unsigned int pIndex)
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::getDataByIndex" << std::endl;
    unsigned int lCount = 0;
    CommonServices::Data::CNode *lListHeader = mListHeader;
    CommonServices::Data::CNode *lNodeData = nullptr;
    
    
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
    mLogger(DEBUG_LOG) << "Exiting CLinkList::getDataByIndex" << std::endl;
    return lNodeData->getValue();
}

// Fetch first node
void* CommonServices::Container::CLinkList::begin()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::begin" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CLinkList::begin" << std::endl;
    return (char*)(this->getDataByIndex(0));
}

// Fetch end node
void* CommonServices::Container::CLinkList::end()
{
    mLogger(DEBUG_LOG) << "Entering CLinkList::end" << std::endl;
    mLogger(DEBUG_LOG) << "Exiting CLinkList::end" << std::endl;
    return (char*)(this->getDataByIndex(this->length()-1));
}
