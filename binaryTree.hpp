#ifndef BINARYTREE
#define BINARYTREE

#include <stdio.h>
#include <iostream>
#include "seqQueue.hpp"
#include "seqStack.hpp"
#include "treeNode.hpp"

template<class elemType>
class binaryTree{
    private:
        treeNode<elemType>* root;

        int Size(treeNode<elemType> *t) const;
        int Hight(treeNode<elemType> *t) const;
        void DelTree(treeNode<elemType> *t);
        treeNode<elemType>* BuildTreePM(const elemType* pre,int pl,int pr,const elemType* mid,int ml,int mr);
        treeNode<elemType>* BuildTreeMP(const elemType* post,int pl,int pr,const elemType* mid,int ml,int mr);
    
        void PreOrder(treeNode<elemType> *t) const;//递归实现
        void InOrder(treeNode<elemType> *t) const;
        void PostOrder(treeNode<elemType> *t) const;
        void LevelOrder(treeNode<elemType> *t) const;//非递归实现
        void PreVisit(treeNode<elemType> *t) const;
        void InVisit(treeNode<elemType> *t) const;
        void PostVisit(treeNode<elemType> *t) const;
    
        void Exchange(treeNode<elemType> *t);
    public:
        binaryTree(){root = NULL;}
        ~binaryTree(){delTree();}

        void createTree(const elemType &nullFlag);
        bool isEmpty() const {return (root == NULL);}
        treeNode<elemType>* getRoot() const {return root;}
        void buildTreePM(const elemType* pre,const elemType* mid,int size);
        void buildTreeMP(const elemType* post,const elemType* mid,int size);
        elemType* seqTree(const elemType &nullFlag);//返回树的线形存储列表

        int size() const;
        int hight() const;
        void delTree();

        void preOrder() const;
        void inOrder() const;
        void postOrder() const;
        void levelOrder() const;
        void preVisit() const;
        void inVisit() const;
        void postVisit() const;
    
        void exchange();

};

//私有基础属性和操作
template<class elemType>
int binaryTree<elemType>::Size(treeNode<elemType> *t) const{
    if (!t) return 0;
    return 1 + Size(t->left) + Size(t->right);
}
template<class elemType>
int binaryTree<elemType>::Hight(treeNode<elemType> *t) const{
    if (!t) return 0;
    return 1+std::max(Hight(t->left),Hight(t->right));
}
template<class elemType>
void binaryTree<elemType>::DelTree(treeNode<elemType> *t){
    if (!t) return;
    DelTree(t->left);
    DelTree(t->right);
    delete t;
}
template<class elemType>
treeNode<elemType>* binaryTree<elemType>::BuildTreePM(const elemType* pre,int pl,int pr,const elemType* mid,int ml,int mr){
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
template<class elemType>
treeNode<elemType>* binaryTree<elemType>::BuildTreeMP(const elemType *post, int pl, int pr, const elemType *mid, int ml, int mr){
    if (pl>pr) return NULL;
    treeNode<elemType> *p,*leftRoot,*rightRoot;
    int pos = -1;
    int num = -1;
    p = new treeNode<elemType>(post[pr]);
    for (int i=ml;i<=mr;i++){
        if (mid[i] == post[pr]){
            pos = i;
            num = pos-ml;
            break;
        }
    }
    if (pos == -1) throw wrongDataIn();
    leftRoot = BuildTreeMP(post, pl, pl+num-1, mid, ml, pos-1);
    rightRoot = BuildTreeMP(post, pl+num, pr-1, mid, pos+1, mr);
    p->left = leftRoot;
    p->right = rightRoot;
    return p;
}

//私有遍历方法
template<class elemType>
void binaryTree<elemType>::PreOrder(treeNode<elemType> *t) const{
    if (!t) return;
    std::cout<<t->data<<' ';
    PreOrder(t->left);
    PreOrder(t->right);
}
template<class elemType>
void binaryTree<elemType>::InOrder(treeNode<elemType> *t) const{
    if (!t) return;
    InOrder(t->left);
    std::cout<<t->data<<' ';
    InOrder(t->right);
}
template<class elemType>
void binaryTree<elemType>::PostOrder(treeNode<elemType> *t) const{
    if (!t) return;
    PostOrder(t->left);
    PostOrder(t->right);
    std::cout<<t->data<<' ';
}
template<class elemType>
void binaryTree<elemType>::LevelOrder(treeNode<elemType> *t) const{
    seqQueue<treeNode<elemType>*> queue;
    treeNode<elemType>* temp;

    if (!t) return;
    queue.enQueue(t);

    while(!queue.isEmpty()){
        temp = queue.deQueue();
        std::cout<<temp->data<<' ';
        if (temp->left) queue.enQueue(temp->left);
        if (temp->right) queue.enQueue(temp->right);
    }
    return;
}
template<class elemType>
void binaryTree<elemType>::PreVisit(treeNode<elemType> *t) const{
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
void binaryTree<elemType>::InVisit(treeNode<elemType> *t) const{
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
template<class elemType>
void binaryTree<elemType>::PostVisit(treeNode<elemType> *t)const{
    if (!root) return;
    
    seqStack<treeNode<elemType>*> stack;
    seqStack<int> label;
    treeNode<elemType>* temp;
    int zero = 0;
    int one = 1;
    int two = 2;
    int flag;
    
    stack.push(t);
    label.push(zero);
    
    while (!stack.isEmpty()) {
        flag = label.pop();
        temp = stack.top();
        switch (flag) {
            case 0:
                label.push(one);
                if (temp->left){
                    stack.push(temp->left);
                    label.push(zero);
                }
                break;
            case 1:
                label.push(two);
                if (temp->right){
                    stack.push(temp->right);
                    label.push(zero);
                }
                break;
            case 2:
                stack.pop();
                std::cout<<temp->data<<' ';
                break;
            default:
                break;
        }
    }
}

template <class elemType>
void binaryTree<elemType>::Exchange(treeNode<elemType> *t){
    if (!t) return;
    treeNode<elemType>* temp;
    temp = t->left;
    t->left = t->right;
    t->right = temp;
}


//共有基础属性方法
template<class elemType>
void binaryTree<elemType>::createTree(const elemType &nullFlag){
    delTree();//del the ori tree
    seqQueue<treeNode<elemType> *> queue;
    elemType e,el,er;
    treeNode<elemType> *p,*pl,*pr;
    std::cout<<"Please input the root:";
    std::cin>>e;

    if(e == nullFlag){root = NULL;return;}

    root = new treeNode<elemType>(e);
    queue.enQueue(root);

    while (!queue.isEmpty()){
        p = queue.deQueue();

        std::cout<<"Please input the left child and the right child of "<<p->data<<" (using "<<nullFlag<<" as no child):";
        std::cin>>el>>er;

        if(el!=nullFlag){
            pl = new treeNode<elemType>(el);
            p->left = pl;
            queue.enQueue(pl);
        }
        if(er!=nullFlag){
            pr = new treeNode<elemType>(er);
            p->right = pr;
            queue.enQueue(pr);
        }
    }
}
template<class elemType>
int binaryTree<elemType>::size() const{
    return Size(root);
}
template<class elemType>
int binaryTree<elemType>::hight() const{
    return Hight(root);
}
template<class elemType>
void binaryTree<elemType>::delTree(){
    DelTree(root);
}
template<class elemType>
void binaryTree<elemType>::buildTreePM(const elemType* pre,const elemType* mid,int size){
    delTree();
    root = BuildTreePM(pre, 0, size-1, mid, 0, size-1);
}
template<class elemType>
void binaryTree<elemType>::buildTreeMP(const elemType* post,const elemType* mid,int size){
    delTree();
    root = BuildTreeMP(post, 0, size-1, mid, 0, size-1);
}
template<class elemType>
elemType* binaryTree<elemType>::seqTree(const elemType &nullFlag){
    if (!root) return NULL;
    
    int lenth = 1;
    for (int i=0;i<hight();i++) lenth*=2;
    
    elemType* seq = new elemType[lenth];
    seqQueue<treeNode<elemType>*> queue;
    treeNode<elemType>* temp;
    int index = 1;
    
    queue.enQueue(root);
    while (index<lenth && !queue.isEmpty()) {
        temp = queue.deQueue();
        if(!temp){
            seq[index] = nullFlag;
            queue.enQueue(NULL);
            queue.enQueue(NULL);
        }
        else{
            seq[index] = temp->data;
            if (temp->left) queue.enQueue(temp->left);
            else queue.enQueue(NULL);
            if (temp->right) queue.enQueue(temp->right);
            else queue.enQueue(NULL);
        }
        index += 1;
    }
    return seq;
}

//公有遍历方法
template<class elemType>
void binaryTree<elemType>::preOrder() const{
    PreOrder(root);
}
template<class elemType>
void binaryTree<elemType>::inOrder() const{
    InOrder(root);
}
template<class elemType>
void binaryTree<elemType>::postOrder() const{
    PostOrder(root);
}
template<class elemType>
void binaryTree<elemType>::levelOrder() const{
    LevelOrder(root);
}
template<class elemType>
void binaryTree<elemType>::preVisit() const{
    PreVisit(root);
}
template<class elemType>
void binaryTree<elemType>::inVisit() const{
    InVisit(root);
}
template<class elemType>
void binaryTree<elemType>::postVisit() const{
    PostVisit(root);
}

template<class elemType>
void binaryTree<elemType>::exchange(){
    Exchange(root);
}

#endif
