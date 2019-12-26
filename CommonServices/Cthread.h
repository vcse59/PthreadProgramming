//
//  Cthread.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef Cthread_h
#define Cthread_h

#include <stdio.h>
#include "CommonDefs.h"
#include "CMutex.h"
#include "Ctask.h"
#include "CLinkList.h"
#include "CLogger.h"

namespace CommonServices
{
    namespace Services
    {
	class Cthread
	{
	    public:
		Cthread(CommonServices::Logger::CLogger &pLogger);
		~Cthread();

		void startThread(unsigned int threadId);
		unsigned int addThread(Ctask*);
		void join();
		void stopThread(unsigned int threadId);
		static void* threadCallback(void *data);

		void printData();
		CommonServices::CommonDefinitions::threadContext_t *mThreadContext_p[32];
		unsigned int mThreadId;
		CommonServices::Services::CMutex*  mpMutex;
		CommonServices::Container::CLinkList* s_threadPool;
		CommonServices::Logger::CLogger &mLogger;
	};
    }
}
#endif /* Cthread_h */
