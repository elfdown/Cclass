#ifndef THREADBINARYTREE
#define THREADBINARYTREE

#include<stdio.h>
#include<iostream>
#include "seqQueue.hpp"
#include "seqStack.hpp"
#include "treeNode.hpp"

template<class elemType>
class threadBinaryTree{
    private:
        treeNode<elemType>* root;
        treeNode<elemType>* threadRoot;
        elemType stopFlag;        

        int Size(treeNode<elemType> *t) const;
        int Hight(treeNode<elemType> *t) const;
        void DelTree(treeNode<elemType> *t);
        void ThreadMid();
    
    public:
        threadBinaryTree(){root = NULL;}
        ~threadBinaryTree(){delTree();}

        void createTree(const elemType &flag);
        bool isEmpty() const {return (root == NULL);}
        treeNode<elemType>* getRoot() const {return root;}

        int size() const;
        int hight() const;
        void delTree();

        void threadPreVisit() const;
        void threadInVisit() const;
};

template<class elemType>
int threadBinaryTree<elemType>::Size(treeNode<elemType> *t) const{
    int leftSize,rightSize;
    if (t->leftFlag) leftSize = 0;
    else leftSize = Size(t->left);
    if (t->rightFlag) rightSize = 0;
    else rightSize = Size(t->right);
    return 1 + leftSize + rightSize;
}
template<class elemType>
int threadBinaryTree<elemType>::Hight(treeNode<elemType> *t) const{
    int leftHight,rightHight;
    if (t->leftFlag) leftHight = 0;
    else leftHight = Hight(t->left);
    if (t->rightFlag) rightHight = 0;
    else rightHight = Hight(t->right);
    return 1+std::max(leftHight,rightHight);
}
template<class elemType>
void threadBinaryTree<elemType>::DelTree(treeNode<elemType> *t){
    if (!t) return;
    if (!t->leftFlag) DelTree(t->left);
    if (!t->rightFlag) DelTree(t->right);
    delete t;
}
template<class elemType>
void threadBinaryTree<elemType>::ThreadMid(){
    if (!root) return;
    seqStack<treeNode<elemType>*> stack;
    seqStack<int> label;
    int zero = 0;
    int one = 1;
    treeNode<elemType>* temp = NULL;
    treeNode<elemType>* tempre = NULL;
    treeNode<elemType>* first = NULL;
    int flag;

    stack.push(root);
    label.push(zero);

    while (!stack.isEmpty()) {
        flag = label.pop();
        temp = stack.top();

        if (flag){
            stack.pop();
    //            std::cout<<temp->data<<' ';
            if(!first) first = temp;
            if (!temp->rightFlag && temp->right){
                stack.push(temp->right);
                label.push(zero);
            }
            if (!temp->left){
                temp->leftFlag = 1;
                temp->left = tempre;
            }
            if (tempre && (!tempre->right)){
                tempre->rightFlag=1;
                tempre->right = temp;
            }
            tempre = temp;
        }
        else{
            label.push(one);
            if (!temp->leftFlag && temp->left) {
                stack.push(temp->left);
                label.push(zero);
            }
        }
    }
    temp->rightFlag = 1;
    threadRoot = first;
}


template<class elemType>
void threadBinaryTree<elemType>::createTree(const elemType &flag){
    seqQueue<treeNode<elemType> *> queue;
    elemType e,el,er;
    treeNode<elemType> *p,*pl,*pr;
    
    stopFlag = flag;
    std::cout<<"Please input the root:";
    std::cin>>e;

    if(e == flag){root = NULL;return;}

    p = new treeNode<elemType>(e);
    root = p;
    queue.enQueue(p);

    while (!queue.isEmpty()){
        p = queue.deQueue();

        std::cout<<"Please input the left child and the right child of "<<p->data<<" (using "<<flag<<" as no child):";
        std::cin>>el>>er;

        if(el!=flag){
            pl = new treeNode<elemType>(el);
            p->left = pl;
            queue.enQueue(pl);
        }
        if(er!=flag){
            pr = new treeNode<elemType>(er);
            p->right = pr;
            queue.enQueue(pr);
        }
    }
    ThreadMid();
}
template<class elemType>
int threadBinaryTree<elemType>::size() const{
    return Size(root);
}
template<class elemType>
int threadBinaryTree<elemType>::hight() const{
    return Hight(root);
}
template<class elemType>
void threadBinaryTree<elemType>::delTree(){
    DelTree(root);
}


template<class elemType>
void threadBinaryTree<elemType>::threadPreVisit() const{
    treeNode<elemType>* temp;
    temp = root;
    while (temp) {
        std::cout<<temp->data<<' ';
        if (!temp->leftFlag) temp = temp->left;
        else {
            if(!temp->rightFlag) temp = temp->right;
            else {
                while (temp&&temp->rightFlag) temp = temp->right;
                if (!temp) return;
                temp = temp->right;
            }
        }
    }
    return;
}
template<class elemType>
void threadBinaryTree<elemType>::threadInVisit() const{
    if (!threadRoot) return;
    treeNode<elemType>* temp;

    temp = threadRoot;
    while (temp) {
        std::cout<<temp->data<<' ';
        if (!temp->rightFlag){
            temp = temp->right;
            while (!temp->leftFlag && temp->left) temp = temp->left;
        }
        else temp = temp->right;
    }
    return;
}

#endif
