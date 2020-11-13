#ifndef TREENODE
#define TREENODE

#include <stdio.h>
#include <iostream>

class wrongDataIn{};

template<class elemType>
class binaryTree;
template<class elemType>
class threadBinaryTree;
template<class elemType>
class tree;
template<class elemType>
class forest;

template<class elemType>
class treeNode{
    private:
        elemType data;
        treeNode* left;
        treeNode* right;
    public:
        friend class binaryTree<elemType>;
        friend class threadBinaryTree<elemType>;
        friend class tree<elemType>;
        friend class forest<elemType>;
        treeNode(const elemType &x,treeNode* l = NULL,treeNode* r = NULL){
            data = x;
            left = l;
            right = r;
        }
        treeNode(){
            left = NULL;
            right = NULL;
        }
        ~treeNode(){}
};

#endif
