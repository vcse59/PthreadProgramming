//
//  CTreeNode.h
//  LinkList
//
//  Created by Vivek Yadav on 11/21/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CTreeNode_h
#define CTreeNode_h

namespace CommonServices
{
    namespace Data
    {
	class CTreeNode
	{
	    public:
		CTreeNode(void* pData);
		~CTreeNode();
		
		void* getValue();

		void setLeftNodeAddress(CTreeNode *);
		void setRightNodeAddress(CTreeNode *);
		
		CTreeNode* getLeftNodeAddress();
		CTreeNode* getRightNodeAddress();

		void setNodeID(unsigned int pNodeId);
		unsigned int getNodeID();

	    private:
		void  *mDataItem;
		CommonServices::Data::CTreeNode *mLeftNodePtr;
		CommonServices::Data::CTreeNode *mRightNodePtr;
		unsigned int mNodeId;

		CTreeNode(const CTreeNode& pNode);
		CTreeNode& operator=(const CTreeNode& pNode);
	};
    }
}
#endif /* CTreeNode_h */
