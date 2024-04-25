//
//  CommonDefs.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/5/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CommonDefs_h
#define CommonDefs_h
#include "CommonServices/Ctask.h"
#include <pthread.h>

namespace CommonServices
{
    namespace CommonDefinitions
    {
	typedef struct threadContext_s
	{
	    unsigned int threadId;
	    CommonServices::Services::Ctask*  task_p;
	    pthread_t mThreadStruct;
	} threadContext_t;

	typedef struct dataContext_s
	{
	    unsigned int dataId;
	    char* data;
	} dataContext_t;

#define NULLCHECK(X, RET_VAL)    \
	if(X == nullptr)    \
	{   \
	    std::cout << #X << " is NULL" << std::endl; \
	    return RET_VAL; \
	}

#define     MAX_THREAD_POOL_SIZE    1024
#define     NOT_INITIALIZED         0
    }
}
#endif /* CommonDefs_h */
