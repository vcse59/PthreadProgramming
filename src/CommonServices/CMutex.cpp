//
//  CMutex.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/11/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include "CommonServices/CMutex.h"

using namespace CommonServices::Services;

CMutex::CMutex() 
{
}

CMutex::~CMutex()
{
}

void CMutex::lockMutex()
{
    this->lock();
}

void CMutex::unLockMutex()
{
    this->unlock();
}
