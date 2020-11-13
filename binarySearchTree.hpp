#ifndef BINARYSEARCHTREE
#define BINARYSEARCHTREE

#include <iostream>
#include "treeNode.hpp"
#include "seqQueue.hpp"

template<class elemType>
class binarySearchTree{
private:
    treeNode<elemType>* root;
    void Insert(const elemType &x,treeNode<elemType> *&t);
    bool Find(const elemType &x,treeNode<elemType> *t) const;
    void DelTree(treeNode<elemType> *t);
    int Hight(treeNode<elemType> *t) const;
    bool IsOld(treeNode<elemType>* t,const elemType a,const elemType b) const;
public:
    binarySearchTree(treeNode<elemType> *t = NULL){root = t;}
    ~binarySearchTree();
    bool find(const elemType &x) const;
    void insert(const elemType &x);
    elemType LCA(const elemType &a,const elemType &b,const elemType &stopFlag) const;
};

template<class elemType>
bool binarySearchTree<elemType>::Find(const elemType &x,treeNode<elemType> *t) const{
    if (!t) return false;
    else if (x<t->data) return Find(x,t->left);
    else if (x>t->data) return Find(x,t->right);
    else return true;
}
template<class elemType>
void binarySearchTree<elemType>::Insert(const elemType &x, treeNode<elemType> *&t){
    if (!t) t = new treeNode<elemType>(x,NULL,NULL);
    else if (x<t->data) Insert(x,t->left);
    else if (x>t->data) Insert(x,t->right);
}
template<class elemType>
void binarySearchTree<elemType>::DelTree(treeNode<elemType> *t){
    if (!t) return;
    DelTree(t->left);
    DelTree(t->right);
    delete t;
}
template<class elemType>
int binarySearchTree<elemType>::Hight(treeNode<elemType> *t) const{
    if (!t) return 0;
    return 1+std::max(Hight(t->left),Hight(t->right));
}
template<class elemType>
bool binarySearchTree<elemType>::IsOld(treeNode<elemType> *t, const elemType a, const elemType b) const{
    if (Find(a, t) && Find(b, t)) return true;
    else return false;
}

template<class elemType>
binarySearchTree<elemType>::~binarySearchTree(){
    DelTree(root);
}
template<class elemType>
void binarySearchTree<elemType>::insert(const elemType &x){
    Insert(x, root);
}
template<class elemType>
bool binarySearchTree<elemType>::find(const elemType &x) const{
    return Find(x, root);
}
template<class elemType>
elemType binarySearchTree<elemType>::LCA(const elemType &a, const elemType &b,const elemType &stopFlag) const{
    seqQueue<treeNode<elemType>*> queue;
    treeNode<elemType>* temp;
    int min = Hight(root)+1;
    elemType L = stopFlag;

    if (!root) return stopFlag;
    queue.enQueue(root);

    while(!queue.isEmpty()){
        temp = queue.deQueue();
        if (Hight(temp) < min && IsOld(temp, a, b)){
            min = Hight(temp);
            L = temp->data;
        }
        if (temp->left) queue.enQueue(temp->left);
        if (temp->right) queue.enQueue(temp->right);
    }
    return  L;
}
#endif
