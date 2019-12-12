//
//  CDataEncodeDecode.hpp
//  ThreadProgramming
//
//  Created by Vivek Yadav on 2/28/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CDataPackUnPack_h
#define CDataPackUnPack_h

#include <stdio.h>

class CPackUnpack
{
public:
    CPackUnpack();
    virtual ~CPackUnpack();
    virtual unsigned int pack(char *pData, size_t pDataLen) = 0;
    virtual char* unpack() = 0;
};

#endif /* CDataEncodeDecode_hpp */
