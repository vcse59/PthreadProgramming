//
//  Node.h
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef Node_h
#define Node_h

class CNode
{
public:
    CNode(void* pData);
    ~CNode();
    void* getValue();
    void setNextNodeAddress(CNode *);
    CNode* getNextNodeAddress();
    void setNodeID(unsigned int pNodeId);
    unsigned int getNodeID();
    
private:
    void  *mDataItem;
    CNode *mNodePtr;
    unsigned int mNodeId;
};
#endif /* Node_h */
