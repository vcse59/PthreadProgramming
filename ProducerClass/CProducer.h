//
//  CProducer.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/6/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CProducer_h
#define CProducer_h

#include <stdio.h>
#include <iostream>
#include "../CommonServices/Ctask.h"
#include "../CommonServices/CMutex.h"
#include "../CommonServices/CQueue.h"
#include "../CommonServices/CLogger.h"

namespace ApplicationData
{
    namespace Producer
    {
	class CProducer : public CommonServices::Services::Ctask
	{
	    public:
		CProducer(std::string pTaskName, CommonServices::Logger::CLogger& pLogger,
			CommonServices::Container::CQueue *pPipeline, char* pThreadData, 
			CommonServices::Services::CMutex &pMutex);
		~CProducer();

		void run();
		void cleanup();

	    private:
		CommonServices::Logger::CLogger &mLogger;
		char *mThreadData;
		CommonServices::Services::CMutex  &mMutex;
	};
    }
}

#endif /* CProducer_h */
