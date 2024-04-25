//
//  CLogLevel.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/19/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#include <stdio.h>
#include "CommonServices/CLogLevel.h"

using namespace CommonServices::Logger;

std::string LOG_LEVEL_STRING[] = {
    "ERROR  ",
    "WARNING",
    "INFO   ",
    "DEBUG  "
};

std::string CLogLevel::getLogLevelString(LOG_LEVEL_ENUM pLogLevel)
{
    return LOG_LEVEL_STRING[pLogLevel];
}
