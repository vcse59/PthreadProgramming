//
//  CLogLevel.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/12/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CLogLevel_h
#define CLogLevel_h

#include <stdio.h>
#include <string>

namespace CommonServices
{
    namespace Logger
    {
	enum LOG_LEVEL_ENUM
	{
	    NONE     =   -1,
	    ERROR    =   NONE      +   1,
	    WARNING  =   ERROR     +   1,
	    INFO     =   WARNING   +   1,
	    DEBUG    =   INFO      +   1
	};

	class CLogLevel
	{
	    public:
		std::string getLogLevelString(CommonServices::Logger::LOG_LEVEL_ENUM pLogLevel);
	};
    }
}
#endif /* CLogLevel_h */
