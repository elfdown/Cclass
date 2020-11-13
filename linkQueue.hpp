#ifndef LINKQUEUE
#define LINKQUEUE

#include<stdio.h>

class emptyQueue{};

template<class elemType>
class linkQueue{
    private:
        struct Node{
            elemType data;
            Node *next;
            Node(const elemType &x,Node *p = NULL){
                data = x;
                next = p;
            }
            ~Node(){}
            Node():next(NULL){}
        };
        Node* front;
        Node* rear;
    public:
        linkQueue();
        ~linkQueue();

        bool isEmpty() const;
        elemType getHead() const;
        elemType deQueue();
        void enQueue(const elemType &x);
};

template<class elemType>
linkQueue<elemType>::linkQueue(){
    front = NULL;
    rear = NULL;
}
template<class elemType>
linkQueue<elemType>::~linkQueue(){
    Node *temp;
    while (front){
        temp = front;
        front = front->next;
        delete temp;
    }
}

template<class elemType>
bool linkQueue<elemType>::isEmpty() const{
    return front == NULL;
}
template<class elemType>
elemType linkQueue<elemType>::getHead() const{
    if (isEmpty()) throw emptyQueue();
    return front->data;
}
template<class elemType>
elemType linkQueue<elemType>::deQueue(){
    if (isEmpty()) throw emptyQueue();
    Node *temp = front;
    elemType x = front->data;
    front = front->next;
    if (!front) rear = NULL;
    delete temp;
    return x;
}
template<class elemType>
void linkQueue<elemType>::enQueue(const elemType &x){
    if (!rear) front = rear = new Node(x);
    else {
        rear -> next = new Node(x);
        rear = rear->next;
    }
}

#endif