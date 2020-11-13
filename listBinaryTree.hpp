#ifndef LISTBINARYTREE
#define LISTBINARYTREE

#include<iostream>
#include <stdio.h>

template<class elemType>
class listBinaryTree{
private:
    elemType* data;
    int* left;
    int* right;
    int Size;
    
    void PreOrder(int t) const;
    void PostOrder(int t) const;
    void MidOrder(int t) const;
public:
    listBinaryTree(int initSize);
    ~listBinaryTree();
    int size() const;
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void swap();
    
};
template<class elemType>
listBinaryTree<elemType>::listBinaryTree(int initSize){
    data = new elemType[initSize];
    left = new int[initSize];
    right = new int [initSize];
    Size = initSize;
    elemType elem;
    int l,r;
    for (int i=0;i<initSize;i++){
        std::cin>>elem>>l>>r;
        data[i] = elem;
        left[i] = l;
        right[i] = r;
    }
}
template<class elemType>
listBinaryTree<elemType>::~listBinaryTree(){
    delete []data;
    delete []left;
    delete []right;
}

template<class elemType>
void listBinaryTree<elemType>::PreOrder(int t) const{
    if (t == -1) return;
    std::cout<<data[t]<<' ';
    PreOrder(left[t]);
    PreOrder(right[t]);
}
template<class elemType>
void listBinaryTree<elemType>::MidOrder(int t) const{
    if (t == -1) return;
    MidOrder(left[t]);
    std::cout<<data[t]<<' ';
    MidOrder(right[t]);
}
template<class elemType>
void listBinaryTree<elemType>::PostOrder(int t) const{
    if (t == -1) return;
    PostOrder(left[t]);
    PostOrder(right[t]);
    std::cout<<data[t]<<' ';
}

template<class elemType>
int listBinaryTree<elemType>::size() const{
    return  Size;
}
template<class elemType>
void listBinaryTree<elemType>::preOrder() const{
    PreOrder(0);
}
template<class elemType>
void listBinaryTree<elemType>::midOrder() const{
    MidOrder(0);
}
template<class elemType>
void listBinaryTree<elemType>::postOrder() const{
    PostOrder(0);
}
template<class elemType>
void listBinaryTree<elemType>::swap(){
    int* temp;
    temp = left;
    left = right;
    right = temp;
}
#endif
