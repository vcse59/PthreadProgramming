//
//  CLogger.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/11/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "CLogger.h"
#include "CLogLevel.h"


CLogger::CLogger(LOG_LEVEL_ENUM    pAppLogLevel)
	:mAppLogLevel(pAppLogLevel)
{
    this->mDefaultLogLevel  =   DEBUG;
    mpMutex  = new CMutex();
}

CLogger::~CLogger()
{
    if (mpMutex != nullptr)
    {
        delete mpMutex;
    }
    mpMutex = nullptr;
}

std::string CLogger::getCurrentDateTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[128];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%Y-%d-%m %H:%M:%S",timeinfo);
    std::string str(buffer);
    return buffer;
}

std::ostream& CLogger::operator<<(const char *pLogMessageStream)
{
    mpMutex->lockMutex();
    std::string lLogLevelStr = mLogLevel.getLogLevelString(this->mDefaultLogLevel);
    std::ostream& lOStream = std::cout << this->getCurrentDateTime() << " " << lLogLevelStr << " " << pLogMessageStream;
    mpMutex->unLockMutex();
    return lOStream;
}

std::ostream& CLogger::operator<<(unsigned int pLogMessageStream)
{
    mpMutex->lockMutex();
    std::string lLogLevelStr = mLogLevel.getLogLevelString(this->mDefaultLogLevel);
    std::ostream& lOStream = std::cout << this->getCurrentDateTime() << " " << lLogLevelStr << " " << pLogMessageStream;
    mpMutex->unLockMutex();
    return lOStream;
}

std::ostream& CLogger::operator<<(std::string pLogMessageStream)
{
    mpMutex->lockMutex();
    std::string lLogLevelStr = mLogLevel.getLogLevelString(this->mDefaultLogLevel);
    std::ostream& lOStream = std::cout << this->getCurrentDateTime() << " " << lLogLevelStr << " " << pLogMessageStream;
    mpMutex->unLockMutex();
    return lOStream;
}

CLogger& CLogger::operator()(LOG_LEVEL_ENUM pLogLevel)
{
    this->mDefaultLogLevel = pLogLevel;
    return *this;
}
