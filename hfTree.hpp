#ifndef HFTREE
#define HFTREE

#include <iostream>
#include <stdio.h>

template<class elemType>
class hfTree{
private:
    struct Node{
        elemType data;
        int weight;
        int parent,left,right;
    };
    
    Node *elem;
    int length;
public:
    struct hfCode{
        elemType data;
        char* code;
    };
    hfTree(const elemType *x,const int *w,int size);
    int getLength(const elemType &x) const;
    int getTotalWeights() const;
    void getCode(hfCode* result) const;
    ~hfTree(){delete [] elem;}
};
template<class elemType>
hfTree<elemType>::hfTree(const elemType *x,const int *w,int size){
    const int MAX_INT = 32767;
    int min1,min2;//最小和次小的权值
    int x1,x2;//最小和次小的下表

    length = 2*size;
    elem = new Node[length];
    
    for (int i=size;i<length;i++){
        elem[i].weight = w[i-size];
        elem[i].data = x[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }

    for (int i = size-1;i>0;i--){
        min1 = min2 = MAX_INT;
        x1 = x2 = 0;
        for (int j=i+1;j<length;j++){
            if (elem[j].parent == 0){
                if (elem[j].weight < min1){
                    min2 = min1;
                    min1 = elem[j].weight;
                    x2 = x1;
                    x1 = j;
                }
                else if (elem[j].weight<min2){
                    min2 = elem[j].weight;
                    x2 = j;
                }
            }
        }
        elem[i].weight = min1 + min2;
        elem[i].left = x1;
        elem[i].right = x2;
        elem[i].parent = 0;
        elem[x1].parent = i;
        elem[x2].parent = i;
    }
}
template<class elemType>
int hfTree<elemType>::getLength(const elemType &x) const{
    int len = 0;
    int index = -1;
    for (int i=length-1;i>0;i--){
        if (elem[i].data == x) {
            index = i;
            break;
        }
    }
    while (index != 1) {
        len += 1;
        index = elem[index].parent;
    }
    return len;
}
template<class elemType>
int hfTree<elemType>::getTotalWeights() const{
    int total = 0;
    int index,len;
    for (int i = length/2;i<length;i++){
        index = i;
        while (index != 1) {
            len += 1;
            index = elem[index].parent;
        }
        total += elem[i].weight * len;
    }
    return total;
}

#endif
