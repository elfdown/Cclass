#ifndef SEQUEUE
#define SEQUEUE

#include<stdio.h>
#include<iostream>

class emptyQueue{};

template<class elemType>
class seqQueue{
    private:
        elemType *elem;
        int front,rear;
        int maxSize;

        void doubleSpace();
    public:
        seqQueue(int initSize = 50);
        ~seqQueue();

        bool isEmpty() const;
        elemType getHead() const;
        void enQueue(const elemType &x);
        elemType deQueue();
};

template<class elemType>
void seqQueue<elemType>::doubleSpace(){
    elemType *new_elem = new elemType[2*maxSize];
    for (int i = 1;i<maxSize;i++){
        new_elem[i] = elem[(front+i)%maxSize];
    }
    front = 0;
    rear = maxSize-1;
    maxSize *= 2;
    delete elem;
    elem = new_elem;
}

template<class elemType>
seqQueue<elemType>::seqQueue(int initSize){
    elem = new elemType[initSize];
    maxSize = initSize;
    front = 0;
    rear = 0;
}
template<class elemType>
seqQueue<elemType>::~seqQueue(){
    delete [] elem;
}

template<class elemType>
bool seqQueue<elemType>::isEmpty() const{
    return front%maxSize == rear%maxSize;
}
template<class elemType>
elemType seqQueue<elemType>::getHead() const{
    if (isEmpty()) throw emptyQueue();
    return elem[(front+1)%maxSize];
}
template<class elemType>
void seqQueue<elemType>::enQueue(const elemType &x){
    if ((rear+1)%maxSize == front%maxSize) doubleSpace();
    rear = (rear+1)%maxSize;
    elem[rear] = x;
}
template<class elemType>
elemType seqQueue<elemType>::deQueue(){
    if (isEmpty()) throw emptyQueue();
    front = (front+1)%maxSize;
    return elem[front];
}

#endif
