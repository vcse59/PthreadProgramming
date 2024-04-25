//
//  Ctask.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef Ctask_h
#define Ctask_h

#include <stdio.h>
#include <iostream>
#include "CommonServices/CLogger.h"
#include "CommonServices/CQueue.h"

namespace CommonServices
{
    namespace Services
    {
	class Ctask
	{
	    public:
		Ctask(std::string pTaskName, CommonServices::Container::CQueue *pPipeline,
			CommonServices::Logger::CLogger &pLogger);
		virtual ~Ctask();

		//pure virtual function
		virtual void run() = 0;
		virtual void cleanup() = 0;

		inline std::string getTaskName()
		{
		    return m_taskName;
		}

	    protected:
		CommonServices::Logger::CLogger &mLogger;
		std::string m_taskName;
		CommonServices::Container::CQueue* m_Pipeline;
	};
    }
}
#endif /* Ctask_hpp */
