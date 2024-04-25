//
//  CBinarySearchTree.h
//  ThreadProgramming
//
//  Created by Vivek Yadav on 12/4/18.
//  Copyright © 2018 Vivek Yadav. All rights reserved.
//

#ifndef CBinarySearchTree_h
#define CBinarySearchTree_h

#include <stdio.h>
#include <iostream>
#include "CommonServices/CLogger.h"
#include "CommonServices/CTreeNode.h"
#include "CommonServices/CQueue.h"
#include "CommonServices/CMutex.h"

namespace CommonServices
{
    namespace Services
    {
        class CBinarySearchTree
        {
            public:
                CBinarySearchTree(CommonServices::Logger::CLogger &pLogger);
                ~CBinarySearchTree();
                CommonServices::Data::CTreeNode* getRootNode();

                //Tree operations
                bool	insertData(CommonServices::Data::CTreeNode *pNode);
                bool	erase();
                bool	search(const CommonServices::Data::CTreeNode *pNode);
                bool	eraseItem(const CommonServices::Data::CTreeNode *pNode);

                //Tree traversal using recursion
                void	preorder_recursive(CommonServices::Data::CTreeNode *pNode);
                void	inorder_recursive(CommonServices::Data::CTreeNode *pNode);
                void 	postorder_recursive(CommonServices::Data::CTreeNode *pNode);

                //Tree traversal using stack 
                void	preorder_nonrecursive();
                void	inorder_nonrecursive();
                void 	postorder_nonrecursive();

            private:
                CBinarySearchTree(const CBinarySearchTree&);
                CBinarySearchTree& operator=(const CBinarySearchTree&);

                CommonServices::Logger::CLogger&    mLogger;
                CommonServices::Data::CTreeNode*    mBSTRoot;
                CommonServices::Services::CMutex*   mMutex;
        };
    }
}
#endif /* CBinarySearchTree_hpp */
