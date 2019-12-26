//
//  CQueue.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 1/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CQueue_h
#define CQueue_h

#include "../AppData/CPipelineDataClass.h"
#include "CMutex.h"
#include "CLinkList.h"
#include "CLogger.h"

namespace CommonServices
{
    namespace Container
    {
	class CQueue
	{

	    public:
		CQueue(CommonServices::Logger::CLogger& pLogger);
		~CQueue();

		bool isEmpty();

		unsigned int size();

		void push_front(ApplicationData::PipelineData::CPipelineData* pData, unsigned int pDataId);

		void push_back(ApplicationData::PipelineData::CPipelineData* pData, unsigned int pDataId);

		void erase(unsigned dataId);

		ApplicationData::PipelineData::CPipelineData* getQueueData(unsigned int pIndex);

		void pop_front();

		void pop_back();

		void setExecutionFlag(bool isStop);

		bool getExecutionFlag();

	    private:
		CommonServices::Logger::CLogger&	mLogger;
		CommonServices::Container::CLinkList*  dQueueContainer;
		bool        mStopFlag;
		CommonServices::Services::CMutex*     mpMutex;
	};
    }
}
#include <stdio.h>

#endif /* CQueue_h */
