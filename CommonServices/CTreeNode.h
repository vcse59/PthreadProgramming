//
//  CTreeNode.h
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CTreeNode_h
#define CTreeNode_h
#include "CMutex.h"

namespace CommonServices
{
    namespace Data
    {
	class CTreeNode
	{
	    public:
		CTreeNode(void* pData, unsigned int pNodeID);
		~CTreeNode();

		void* getValue();

		void setLeftNodeAddress(CTreeNode *);
		void setRightNodeAddress(CTreeNode *);

		CTreeNode* getLeftNodeAddress();
		CTreeNode* getRightNodeAddress();

		unsigned int getNodeID();

	    private:
		void  *mDataItem;
		CommonServices::Data::CTreeNode *mLeftNodePtr;
		CommonServices::Data::CTreeNode *mRightNodePtr;
		unsigned int mNodeId;
		CommonServices::Services::CMutex *mMutex;

		CTreeNode(const CTreeNode& pNode);
		CTreeNode& operator=(const CTreeNode& pNode);
	};
    }
}
#endif /* CTreeNode_h */
