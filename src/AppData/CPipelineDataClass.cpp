//
//  CPipelineDataClass.cpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 2/28/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#include "AppData/CPipelineDataClass.h"

using namespace ApplicationData::PipelineData;

CPipelineData::CPipelineData(std::string pTaskName, char* pThreadData):mTaskName(pTaskName), mThreadData(pThreadData)
{
    std::cout << "CPipelineData constructor" << std::endl;
    mData = (ApplicationData::ThreadData::THREAD_STRUCT*) malloc(sizeof(ApplicationData::ThreadData::THREAD_STRUCT));
    memset(mData, 0, sizeof(ApplicationData::ThreadData::THREAD_STRUCT));
    mIsObsolete = false;
}

CPipelineData::~CPipelineData()
{
    std::cout << "CPipelineData destructor" << std::endl;
    if(mData != NULL)
    {
        if(mData->lThreadData != NULL)
            {
                delete[] mData->lThreadData;
            }
        mData->lThreadData = NULL;
        free(mData);
    }
    mData = NULL;
}

unsigned int CPipelineData::pack(char *pData, size_t pDataLen)
{
    std::cout << "CPipelineData pack : " << std::endl;
    mData->lThreadData = new char[pDataLen + 1];
    strncpy(mData->lThreadData, pData, pDataLen);
    mData->lThreadData[pDataLen] = '\0';
    mData->lDataId = rand();
    std::cout << "Packing ThreadData from : " << mTaskName << " : " << mData->lThreadData << " with DataID : " << mData->lDataId << std::endl;
    return mData->lDataId;
}

char* CPipelineData::unpack()
{
    std::cout << "CPipelineData unpack" << std::endl;
    return mData->lThreadData;
}
