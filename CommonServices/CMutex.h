//
//  CMutex.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 11/11/19.
//  Copyright © 2019 Vivek Yadav. All rights reserved.
//

#ifndef CMutex_h
#define CMutex_h

#include <stdio.h>
#include <mutex>

class CMutex : public std::mutex
{
public:
    CMutex();
    ~CMutex();
    
    void lockMutex();
    void unLockMutex();
};
#endif /* CMutex_h */
