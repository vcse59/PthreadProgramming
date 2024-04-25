//
//  LinkList.hpp
//  LinkList
//
//  Created by Vivek Yadav on 11/20/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef LinkList_hpp
#define LinkList_hpp

#include <stdio.h>
#include <string>
#include "CommonServices/CLogger.h"
#include "CommonServices/CNode.h"
#include "CommonServices/CMutex.h"


namespace CommonServices
{
    namespace Container
    {
	class CLinkList
	{
	    public:
		//Contructor declaration
		CLinkList(CommonServices::Logger::CLogger &pLogger);

		//Destructor declaration
		~CLinkList();

		// Returns Link list length
		unsigned int length();

		// Insert the node at the end
		unsigned int insertNodeAtEnd(void* pData);

		// Insert the node at the start
		unsigned int insertNodeAtStart(void* pData);

		// Reverse the link list
		bool reverse();

		// Delete the node by node value
		bool deleteNode(unsigned int pNodeID);

		// Delete All Link List node
		void deleteAll();

		// Print all Link list node values
		std::string printData();

		// Fetch CNode by node_ID
		void * fetchNode(unsigned int pNodeID);

		// Overloading subscript operator
		void * getDataByIndex(const unsigned int pIndex);

		// Delete the node from start
		bool deleteNodeFromStart();

		// Delete the node from end
		bool deleteNodeFromEnd();

		// Fetch first node
		void* begin();

		// Fetch end node
		void* end();

	    private:
		CommonServices::Logger::CLogger         &mLogger;
		CommonServices::Data::CNode           *mListHeader;
		unsigned int    mIndex;
		CommonServices::Services::CMutex*        	mpMutex;
	};
    }
}
#endif /* LinkList_hpp */
