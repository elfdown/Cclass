#ifndef SEQLIST
#define SEQLIST

#include<stdio.h>
#include<iostream>

class outOfBound{};
class IlegalSize{};
class notFound{};

template <class elemType>
class linkList{
    private:
        struct Node{
            elemType data;
            Node* next;
            Node(const elemType &x,Node *p=NULL){
                data = x;
                next = p;
            }
            Node():next(NULL){}
            ~Node(){}
        };
        Node *head;
    public:
        linkList();
        ~linkList();
        int lenth() const;
        int search(const elemType &x) const;
        elemType visit(int i) const;
        void insert(int i,const elemType &x);
        void add(const elemType &x);
        void remove(int i);
        void clear();
        void traverse() const;
};

template<class elemType>
linkList<elemType>::linkList(){
    head = new Node();
}
template<class elemType>
linkList<elemType>::~linkList(){
    clear();
    delete head;
}

template<class elemType>
int linkList<elemType>::lenth() const{
    Node* p = head->next;
    int len = 0;
    while (p){
        p = p->next;
        len += 1;
    }
    return len;
}
template<class elemType>
int  linkList<elemType>::search(const elemType &x) const{
    Node* p = head->next;
    int index = 0;
    while (p){
        if (p->data == x) return index;
        p = p->next;
        index += 1;
    }
    throw notFound();
}
template<class elemType>
elemType linkList<elemType>::visit(int i) const{
    Node *p = head->next;
    for (int index  = 0;p && index<=i;index++){
        p = p->next;
    }
    if (!p) throw outOfBound();
    return p->data;
}
template<class elemType>
void linkList<elemType>::insert(int i,const elemType &x){
    Node *p = head;
    for (int index = -1;p && index<i-1;index++){
        p = p->next;
    }
    if (!p) throw outOfBound();
    Node *temp = new Node(x,p->next);
    p->next = temp;
}
template<class elemType>
void linkList<elemType>::add(const elemType &x){
    Node *temp = new Node(x);
    Node *p = head;
    while (p->next){
        p = p->next;
    }
    p->next = temp;
    
}
template<class elemType>
void linkList<elemType>::remove(int i){
    int index = 0;
    Node *pr = head;
    Node *p = head->next;
    while (p && index<i){
        pr = pr->next;
        p = p->next;
        index += 1;
    }
    if (!p) throw outOfBound();
    pr->next = p->next;
    delete p;
}
template<class elemType>
void linkList<elemType>::clear(){
    Node *temp;
    temp = head->next;
    while (temp){
        head->next = temp->next;
        delete temp;
        temp = head->next;
    }
}
template<class elemType>
void linkList<elemType>::traverse() const{
    Node* p = head->next;
    while (p){
        std::cout<<p->data<<' ';
        p = p->next;
    }
}

#endif
