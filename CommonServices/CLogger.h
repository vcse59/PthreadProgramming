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
#include "CMutex.h"
#include "CLogLevel.h"

#define	LOG_PRINT(logMessage)	\
    mpMutex->lockMutex();	\
    std::string lLogLevelStr = mLogLevel.getLogLevelString(this->mDefaultLogLevel);	\
    std::ostream& lOStream = std::cout << this->getCurrentDateTime() << " "	\
    << lLogLevelStr << " " << logMessage;	\
    mpMutex->unLockMutex();	\
    return lOStream;

class CLogger
{
public:

    CLogger(LOG_LEVEL_ENUM    pAppLogLevel = DEBUG);
    ~CLogger();
    
    std::ostream& operator<<(const char *pLogMessageStream);
    std::ostream& operator<<(std::string pLogMessageStream);
    std::ostream& operator<<(unsigned int pLogMessageStream);
    CLogger& operator()(LOG_LEVEL_ENUM pLogLevel = INFO);

protected:
    LOG_LEVEL_ENUM  mDefaultLogLevel;
    std::string getCurrentDateTime();
    CLogLevel	mLogLevel;
    CMutex*     mpMutex;
    LOG_LEVEL_ENUM  mAppLogLevel;
};
#endif /* CLogger_h */
