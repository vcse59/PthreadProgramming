//
//  Ctask.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#include <iostream>
#include "Ctask.h"

using namespace CommonServices::Services;
using namespace CommonServices::Logger;

Ctask::Ctask(std::string pTaskName, CommonServices::Container::CQueue *pPipeline, 
	CommonServices::Logger::CLogger &pLogger)
    :mLogger(pLogger), m_taskName(pTaskName), m_Pipeline(pPipeline)
{
    mLogger(DEBUG_LOG) << "Entering Ctask::constructor initialised by " << m_taskName << std::endl;
    mLogger(DEBUG_LOG) << "Existing Ctask::constructor initialised by " << m_taskName << std::endl;
}

Ctask::~Ctask()
{
    mLogger(DEBUG_LOG) << "Entering Ctask::destructor initialised by " << m_taskName << std::endl;
    mLogger(DEBUG_LOG) << "Entering Ctask::destructor initialised by " << m_taskName << std::endl;
}
