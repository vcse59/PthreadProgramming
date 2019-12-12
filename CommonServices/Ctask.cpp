//
//  Ctask.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include "Ctask.h"
#include "CLogger.h"

Ctask::Ctask(std::string pTaskName, CQueue *pPipeline, CLogger &pLogger)
    :mLogger(pLogger), m_taskName(pTaskName), m_Pipeline(pPipeline)
{
    mLogger(DEBUG) << "Entering Ctask::constructor initialised by " << m_taskName << std::endl;
    mLogger(DEBUG) << "Existing Ctask::constructor initialised by " << m_taskName << std::endl;
}

Ctask::~Ctask()
{
    mLogger(DEBUG) << "Entering Ctask::destructor initialised by " << m_taskName << std::endl;
    mLogger(DEBUG) << "Entering Ctask::destructor initialised by " << m_taskName << std::endl;
}
