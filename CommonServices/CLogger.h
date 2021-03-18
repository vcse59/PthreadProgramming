//
//  CLogger.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/11/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CLogger_h
#define CLogger_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <mutex>
#include "CLogLevel.h"

namespace CommonServices
{
    namespace Logger
    {
        class CLogger
        {
            public:
                CLogger(CommonServices::Logger::LOG_LEVEL_ENUM    pAppLogLevel = DEBUG_LOG);
                ~CLogger();

                std::ostream& operator<<(const char *pLogMessageStream);
                std::ostream& operator<<(std::string pLogMessageStream);
                std::ostream& operator<<(unsigned int pLogMessageStream);
                CLogger& operator()(CommonServices::Logger::LOG_LEVEL_ENUM pLogLevel = INFO_LOG);

            protected:
                CommonServices::Logger::LOG_LEVEL_ENUM  mDefaultLogLevel;
                std::string getCurrentDateTime();
                CommonServices::Logger::CLogLevel	mLogLevel;
                std::mutex                          lMutex;
                CommonServices::Logger::LOG_LEVEL_ENUM  mAppLogLevel;
        };
    }
}
#endif /* CLogger_h */
