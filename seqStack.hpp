#ifndef SEQSTACK
#define SEQSTACK
#include<stdio.h>
#include<iostream>

class emptyStack{};

template<class elemType>
class seqStack{
    private:
        elemType *elem;
        int Top;
        int maxSize;

        void doubleSpace();
    public:
        seqStack(int initSize = 10);
        ~seqStack();

        bool isEmpty() const;
        elemType top() const;
        elemType pop();
        void push(const elemType &x);
};

template<class elemType>
void seqStack<elemType>::doubleSpace(){
    elemType *new_elem = new elemType[2*maxSize];
    for(int i=0;i<=Top;i++) new_elem[i] = elem[i];
    delete [] elem;
    elem = new_elem;
}

template<class elemType>
seqStack<elemType>::seqStack(int initSize){
    elem = new elemType[initSize];
    Top = -1;
    maxSize = initSize;
}
template<class elemType>
seqStack<elemType>::~seqStack(){
    delete [] elem;
}

template<class elemType>
bool seqStack<elemType>::isEmpty() const{
    if (Top == -1) return true;
    return false;
}
template<class elemType>
elemType seqStack<elemType>::top() const{
    if (isEmpty()) throw emptyStack();
    return elem[Top];
}
template<class elemType>
elemType seqStack<elemType>::pop(){
    if (isEmpty()) throw emptyStack();
    Top -= 1;
    return elem[Top+1];
}
template<class elemType>
void seqStack<elemType>::push(const elemType &x){
    if (Top == maxSize-1) doubleSpace();
    Top += 1;
    elem[Top] = x;
}

#endif
