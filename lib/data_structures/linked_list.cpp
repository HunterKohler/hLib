#include "./linked_list.h"

template<class T> linked_list<T>::node::node(T _d, node *_n): data{_d}, next{_n} {}
template<class T> linked_list<T>::node::node(T _d): node(_d,nullptr) {}
template<class T> linked_list<T>::linked_list(): head{nullptr}, tail{nullptr} {}

template<class T>
void linked_list<T>::add(T i) {
    node *tmp = new node(i);
    if(head == nullptr) {
        head = tail = tmp;
    } else {
        tail->next = tmp;
        tail = tmp;
    }
}

template <class T>
void linked_list<T>::append(linked_list<T>& l) {
    tail->next = l.head;
    tail = l.tail;
}
