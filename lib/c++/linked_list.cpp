#include "linked_list.hpp"

int main() {}

template<class T> linked_list<T>::node::node(T _d, node *_n): data{_d}, next{_n} {}
template<class T> linked_list<T>::node::node(T _d): node(_d,nullptr) {}
template<class T> linked_list<T>::linked_list(): _head{nullptr}, _tail{nullptr} {}

template<class T>
void linked_list<T>::add(T i) {
    node *tmp = new node(i);
    if(_head == nullptr) {
        _head = _tail = tmp;
    } else {
        _tail->next = tmp;
        _tail = tmp;
    }
}

template <class T>
void linked_list<T>::append(linked_list<T>& l) {
    _tail->next = l._head;
    _tail = l._tail;
}
