#ifndef LINKSTACK
#define LINKSTACK

#include<stdio.h>
#include<iostream>
class emptyStack{};
template<class elemType>
class linkStack{
    private:
        struct Node{
            elemType data;
            Node* next;
            Node(const elemType &x,Node *p = NULL){
                data = x;
                next = p;
            }
            ~Node(){}
            Node():next(NULL){}
        };
        Node *Top;
    public:
        linkStack();
        ~linkStack();

        bool isEmpty() const;
        elemType top() const;
        elemType pop();
        void push(const elemType &x);
        void clear();
};

template<class elemType>
linkStack<elemType>::linkStack(){
    Top = NULL;
}
template<class elemType>
linkStack<elemType>::~linkStack(){
    Node *temp;
    while (Top){
        temp = Top;
        Top = Top->next;
        delete temp;
    }
}

template<class elemType>
bool linkStack<elemType>::isEmpty() const{
    return Top == NULL;
}
template<class elemType>
elemType linkStack<elemType>::top() const{
    if (isEmpty()) throw emptyStack();
    return Top->data;
}
template<class elemType>
elemType linkStack<elemType>::pop(){
    if (isEmpty()) throw emptyStack();
    Node *temp = Top;
    elemType x = Top->data;
    Top = Top->next;
    delete temp;
    return x;
}
template<class elemType>
void linkStack<elemType>::push(const elemType &x){
    Top = new Node(x,Top);
}

#endif