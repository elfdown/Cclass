#ifndef PRIORITYQUEUE
#define PRIORITYQUEUE

#include <stdio.h>
#include <iostream>

template <class elemType>
class priorityQueue {
private:
    int currentSize;
    elemType* array;
    int maxSize;
    
    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
    
public:
    priorityQueue(int capacity = 100){
        array = new elemType[capacity];
        maxSize = capacity;
        currentSize = 0;
    }
    priorityQueue(const elemType *data,int size);
    priorityQueue(const priorityQueue<elemType> &obj);
    ~priorityQueue(){delete [] array;}
    bool isEmpty() const{return currentSize == 0;}
    elemType getHead(){return array[1];}
    void enQueue(const elemType &x);
    elemType deQueue();
    void addQueue(const priorityQueue<elemType> &obj);
};
template<class elemType>
priorityQueue<elemType>::priorityQueue(const elemType *data,int size):maxSize(size+10),currentSize(size){
    array = new elemType[maxSize];
    for (int i=0;i<size;i++) array[i+1] = data[i];
    buildHeap();
}
template<class elemType>
priorityQueue<elemType>::priorityQueue(const priorityQueue<elemType> &obj){
    array = new elemType[obj.maxSize];
    for (int i=1;i<=obj.currentSize;i++) array[i] = obj.array[i];
    maxSize = obj.maxSize;
    currentSize = obj.currentSize;
}
template<class elemType>
void priorityQueue<elemType>::doubleSpace(){
    elemType* newArray = new elemType[maxSize*2];
    for (int i=1;i<maxSize;i++) newArray[i] = array[i];
    delete [] array;
    array = newArray;
    maxSize *= 2;
}
template<class elemType>
void priorityQueue<elemType>::buildHeap(){
    for(int i=currentSize/2;i>0;i--) percolateDown(i);
}
template<class elemType>
void priorityQueue<elemType>::percolateDown(int hole){
    int child;
    elemType temp = array[hole];
    for (; hole * 2 <= currentSize;hole=child)
    {
        child = hole * 2;
        if(child!=currentSize&&array[child+1]<array[child])
            child++;
        if(*array[child]<temp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = temp;
}

template<class elemType>
void priorityQueue<elemType>::enQueue(const elemType &x){
    if (currentSize == maxSize-1) doubleSpace();
    
    int hole = ++currentSize;
    for (; hole > 1 && *x < *array[hole / 2];hole/=2)
        array[hole] = array[hole / 2];
    array[hole] = x;
}
template<class elemType>
elemType priorityQueue<elemType>::deQueue(){
    elemType head = array[1];
    array[1] = array[currentSize--];
    percolateDown(1);
    return  head;
}
template<class elemType>
void priorityQueue<elemType>::addQueue(const priorityQueue<elemType> &obj){
    elemType* newArray = new elemType[maxSize + obj.maxSize];
    for (int i=1;i<=currentSize;i++) newArray[i] = array[i];
    for (int i=1;i<=obj.currentSize;i++) newArray[i+currentSize] = obj.array[i];
    delete [] array;
    array = newArray;
    maxSize += obj.maxSize;
    currentSize += obj.currentSize;
    buildHeap();
}
#endif
