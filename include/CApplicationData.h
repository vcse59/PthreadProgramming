//
//  CApplicationData.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 2/28/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CApplicationData_h
#define CApplicationData_h

#include <string.h>

namespace ApplicationData
{
    namespace	ThreadData
    {
	typedef struct thread_struct_s
	{
	    int lDataId;
	    char* lThreadData;
	}THREAD_STRUCT;
    }
}
#endif /* CApplicationData_h */
