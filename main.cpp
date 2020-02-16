//
//  main.cpp
//  PthreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "CommonServices/Ctask.h"
#include "ProducerClass/CProducer.h"
#include "ConsumerClass/CConsumer.h"
#include "CommonServices/Cthread.h"
#include "CApplicationData.h"
#include "CommonServices/CQueue.h"
#include "DebugThread/DebugThreadClass.h"
#include "CommonServices/CMutex.h"
#include "CommonServices/CLogger.h"
#include "CommonServices/CLogLevel.h"
#include "CommonServices/CommonDefs.h"
#include "CommonServices/CTreeNode.h"
#include "CommonServices/CBinarySearchTree.h"

#define MAX_CONSUMER_THREAD  60
#define MAX_PRODUCER_THREAD  30

int main(int argc, const char * argv[]) {

/*****************************************************************************Thread pipeline implentation**************************************/
    // Instantiating pipeline

    /*
    CommonServices::Logger::CLogger lLogger(CommonServices::Logger::NONE);
    CommonServices::Services::Cthread thread_p(lLogger);
    CommonServices::Container::CQueue lPipeline(lLogger);
    CommonServices::Services::CMutex lMutex;

    lLogger(CommonServices::Logger::INFO) << "Main program entry" << std::endl;

    CommonServices::Services::Ctask *debugThread_p =  new DebugThread("DebugThread", lLogger, &lPipeline, NULL);
    unsigned int DebugThreadId = thread_p.addThread(debugThread_p);
    thread_p.startThread(DebugThreadId);
    
    for (unsigned int lCounter = 0; lCounter < MAX_CONSUMER_THREAD; ++lCounter)
    {
    	std::string taskName1 = std::string("CConsumer") + std::to_string(lCounter);
    	CommonServices::Services::Ctask *task1_p = new ApplicationData::Consumer::CConsumer(taskName1, lLogger, &lPipeline, NULL, lMutex);
    	unsigned int task1ThreadId = thread_p.addThread(task1_p);
    	thread_p.startThread(task1ThreadId);
    }
    
    for (unsigned int lCounter = 0; lCounter < MAX_PRODUCER_THREAD; ++lCounter)
    {
    	std::string taskName2 = std::string("CProducer") + std::to_string(lCounter);
        CommonServices::Services::Ctask *task2_p = new ApplicationData::Producer::CProducer(taskName2, lLogger, &lPipeline, NULL, lMutex);
    	unsigned int task2ThreadId = thread_p.addThread(task2_p);
    	thread_p.startThread(task2ThreadId);
    }
    
    thread_p.join();
    */
/***********************************************************************************************************************************************/


/******************************************************Binary search tree implementation********************************************************/
    CommonServices::Logger::CLogger lLogger(CommonServices::Logger::NONE);
    CommonServices::Services::CBinarySearchTree* bstTreeObj = new CommonServices::Services::CBinarySearchTree(lLogger);

    unsigned int num1 = 21;
    CommonServices::Data::CTreeNode data1((void*)&num1);
    bstTreeObj->insertData(&data1, num1);

    unsigned int num2 = 45;
    CommonServices::Data::CTreeNode data2((void*)&num2);
    bstTreeObj->insertData(&data2, num2);

    unsigned int num3 = 12;
    CommonServices::Data::CTreeNode data3((void*)&num3);
    bstTreeObj->insertData(&data3, num3);

    unsigned int num4 = 5;
    CommonServices::Data::CTreeNode data4((void*)&num4);
    bstTreeObj->insertData(&data4, num4);

    unsigned int num5 = 99;
    CommonServices::Data::CTreeNode data5((void*)&num5);
    bstTreeObj->insertData(&data5, num5);

    unsigned int num6 = 34;
    CommonServices::Data::CTreeNode data6((void*)&num6);
    bstTreeObj->insertData(&data6, num6);

    CommonServices::Data::CTreeNode* rootNode = bstTreeObj->getRootNode();
    lLogger(CommonServices::Logger::INFO) << "Recursive PreOrder traversal" << std::endl;
    bstTreeObj->preorder_recursive(rootNode);
    std::cout << std::endl;

    lLogger(CommonServices::Logger::INFO) << "Recursive InOrder traversal" << std::endl;
    bstTreeObj->inorder_recursive(rootNode);
    std::cout << std::endl;

    lLogger(CommonServices::Logger::INFO) << "Recursive PostOrder traversal" << std::endl;
    bstTreeObj->postorder_recursive(rootNode);
    std::cout << std::endl;

    if (bstTreeObj != nullptr)
    {
	delete bstTreeObj;
    }
    
    bstTreeObj = nullptr;
/**********************************************************************************************************************************************/
    return 0;
}
