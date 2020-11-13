#ifndef TREE
#define TREE

#include <stdio.h>
#include <iostream>
#include "seqQueue.hpp"
#include "seqStack.hpp"
#include "treeNode.hpp"

template<class elemType>
class tree{
    private:
        treeNode<elemType>* root;

        void DelTree(treeNode<elemType> *t);
        treeNode<elemType>* BuildTree(const elemType* pre,int pl,int pr,const elemType* mid,int ml,int mr);
    
        void TpOrder(treeNode<elemType> *t) const;//递归实现
        void BkOrder(treeNode<elemType> *t) const;
        void TpVisit(treeNode<elemType> *t) const;//非递归实现
        void BkVisit(treeNode<elemType> *t) const;
    
    public:
        tree(){root = NULL;}
        ~tree(){delTree();}

        void createTree(const elemType &nullFlag);
        bool isEmpty() const {return (root == NULL);}
        treeNode<elemType>* getRoot() const {return root;}
        void buildTree(const elemType* pre,const elemType* mid,int size);

        int size() const;
        int hight() const;
        void delTree();

        void tpOrder() const;
        void bkOrder() const;
        void tpVisit() const;
        void bkVisit() const;
};

//私有基础属性方法
template<class elemType>
void tree<elemType>::DelTree(treeNode<elemType> *t){
    if (!t) return;
    DelTree(t->left);
    DelTree(t->right);
    delete t;
}
template<class elemType>
treeNode<elemType>* tree<elemType>::BuildTree(const elemType* pre,int pl,int pr,const elemType* mid,int ml,int mr){
    if (pl>pr) return NULL;
    treeNode<elemType> *p,*leftRoot,*rightRoot;
    int pos = -1;
    int num = -1;
    p = new treeNode<elemType>(pre[pl]);
    for (int i = ml;i<=mr;i++){
        if (mid[i] == pre[pl]){
            pos = i;
            num = pos-ml;
            break;
        }
    }
    if (pos == -1) throw wrongDataIn();
    leftRoot = BuildTreePM(pre, pl+1, pl+num, mid, ml, pos-1);
    rightRoot = BuildTreePM(pre, pl+num+1, pr,mid, pos+1, mr);
    p->left = leftRoot;
    p->right = rightRoot;
    return p;
}
//私有遍历方法
template<class elemType>
void tree<elemType>::TpOrder(treeNode<elemType> *t) const{
    if (!t) return;
    std::cout<<t->data<<' ';
    TpOrder(t->left);
    TpOrder(t->right);
}
template<class elemType>
void tree<elemType>::BkOrder(treeNode<elemType> *t) const{
    if (!t) return;
    BkOrder(t->left);
    std::cout<<t->data<<' ';
    BkOrder(t->right);
}
template<class elemType>
void tree<elemType>::TpVisit(treeNode<elemType> *t) const{
    if (!t) return;
    
    seqStack<treeNode<elemType>*> stack;
    treeNode<elemType>* temp;
    
    stack.push(t);
    while(!stack.isEmpty()){
        temp = stack.pop();
        std::cout<<temp->data<<' ';
        if (temp->right) stack.push(temp->right);
        if (temp->left) stack.push(temp->left);
    }
    return;
}
template<class elemType>
void tree<elemType>::BkVisit(treeNode<elemType> *t) const{
    if (!t) return;
    seqStack<treeNode<elemType>*> stack;
    seqStack<int> label;
    int zero = 0;
    int one = 1;
    treeNode<elemType>* temp;
    int flag;
    
    stack.push(t);
    label.push(zero);
    
    while (!stack.isEmpty()) {
        flag = label.pop();
        temp = stack.top();
        
        if (flag){
            stack.pop();
            std::cout<<temp->data<<' ';
            if (temp->right){
                stack.push(temp->right);
                label.push(zero);
            }
        }
        else{
            label.push(one);
            if (temp->left) {
                stack.push(temp->left);
                label.push(zero);
            }
        }
    }
}
//共有基础属性方法
template<class elemType>
void tree<elemType>::createTree(const elemType& nullFlag){
    seqQueue<treeNode<elemType>*> queue;
    treeNode<elemType> *parent,*child;
    elemType e;

    std::cout<<"input the root:";
    std::cin>>e;
    if (e == nullFlag) return;
    root = new treeNode<elemType>(e);
    queue.enQueue(root);

    while (!queue.isEmpty()){
        parent = queue.deQueue();
        std::cout<<"input the children of "<<parent->data<<" (end with "<<nullFlag<<"):";
        std::cin>>e;
        if (e == nullFlag) continue;
        child = new treeNode<elemType>(e);
        parent->left = child;
        queue.enQueue(child);
        while (true){
            std::cin>>e;
            if (e == nullFlag) break;
            child->right = new treeNode<elemType>(e);
            child = child->right;
            queue.enQueue(child);
        }
    }
}
template<class elemType>
int tree<elemType>::size() const{
    return 0;
}
template<class elemType>
int tree<elemType>::hight() const{
    return 0;
}
template<class elemType>
void tree<elemType>::delTree(){
    DelTree(root);
}
//公有遍历方法
template<class elemType>
void tree<elemType>::tpOrder() const{
    TpOrder(root);
}
template<class elemType>
void tree<elemType>::bkOrder() const{
    BkOrder(root);
}
template<class elemType>
void tree<elemType>::tpVisit() const{
    TpVisit(root);
}
template<class elemType>
void tree<elemType>::bkVisit() const{
    BkVisit(root);
}
#endif
