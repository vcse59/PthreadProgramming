//
//  CPipelineDataClass.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 2/28/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CPipelineDataClass_hpp
#define CPipelineDataClass_hpp

#include <stdio.h>
#include <iostream>
#include "../CommonServices/CDataPackUnPack.h"
#include "../CApplicationData.h"

class CPipelineData : public CommonServices::Data::CPackUnpack
{
public:
    CPipelineData(std::string pTaskName, char* pThreadData);
    ~CPipelineData();
    unsigned int pack(char *pData, size_t pDataLen);
    char* unpack();
    
    std::string     mTaskName;
    char*           mThreadData;
    THREAD_STRUCT   *mData;
    bool            mIsObsolete;
};
#endif /* CPipelineDataClass_hpp */
