#ifndef SEQQLIST
#define SEQQLIST
#include <iostream>
#include <stdio.h>

class outOfBound{};
class IlegalSize{};

template <class elemType>
class seqList{
    private:
        elemType *data;
        int currentLength;
        int maxLenth;
        void doubleSpace();
        void cutSpace();
    public:
        seqList(int initSize = 1000);
        ~seqList();
        int lenth () const;
        int search(const elemType &x) const;
        elemType &visit(int i) const;
        void insert (int i,const elemType &x);
        void add (const elemType &x);  
        elemType pop ();
        elemType top () const;
        bool isEmpty() const;
        void remove (int i);
        void clear();
        void traverse() const;
};

template <class elemType>
void seqList<elemType>::doubleSpace(){
    elemType *new_data = new elemType[2*maxLenth];
    for (int i = 0;i<currentLength;i++) new_data[i] = data[i];
    maxLenth *= 2;
    delete []data;
    data = new_data;
}
template <class elemType>
void seqList<elemType>::cutSpace(){
    elemType *new_data = new elemType[maxLenth/2];
    for (int i = 0;i<currentLength;i++) new_data[i] = data[i];
    maxLenth /= 2;
    delete []data;
    data = new_data;
}

template <class elemType>
seqList<elemType>::seqList(int initSize){
    data = new elemType[initSize];
    if (!data) throw IlegalSize();
    maxLenth = initSize;
    currentLength = 0;
}
template <class elemType>
seqList<elemType>::~seqList(){
    delete [] data;
}

template <class elemType>
int seqList<elemType>::lenth() const{
    return currentLength;
}
template <class elemType>
int seqList<elemType>::search(const elemType &x) const{
    for (int i = 0;i < currentLength;i++){
        if (data[i] == x) return i;
    }
    return -1;
}
template <class elemeType>
elemeType &seqList<elemeType>::visit(int i) const{
    if (i <0 or i>=currentLength) throw outOfBound();
    return data[i];
}
template <class elemType>
void seqList<elemType>::insert (int i,const elemType &x){
    if (currentLength == maxLenth) doubleSpace();
    if (i < 0 or i >currentLength) throw outOfBound();
    int index;
    for (index=currentLength;index>i;index--) data[index] = data[index-1];
    data[i] = x;
    currentLength += 1;
}
template <class elemType>
void seqList<elemType>::remove(int i){
    if (currentLength == maxLenth/4) cutSpace();
    if (i<0 or i>=currentLength) throw outOfBound();
    int index;
    for (index=i;index<currentLength;index++) data[index] = data[index+1];
    currentLength -= 1;
}
template <class elemType>
void seqList<elemType>::clear(){
    currentLength = 0;
}
template <class elemType>
void seqList<elemType>::traverse() const{
    for (int i=0;i<currentLength;i++){
        std::cout<<data[i]<<' ';
    }
}
template <class elemType>
void seqList<elemType>::add(const elemType &x){
    insert(currentLength,x);
}
template <class elemType>
elemType seqList<elemType>::pop(){
    elemType x = visit(currentLength-1);
    currentLength -= 1;
    return x;
}
template<class elemType>
elemType seqList<elemType>::top() const{
    elemType x = visit(currentLength-1);
    return x;
}
template<class elemType>
bool seqList<elemType>::isEmpty() const{
    return (currentLength == 0);
}

#endif