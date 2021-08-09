#ifndef LIB_DATA_STRUCTURES_LINKED_LIST_H
#define LIB_DATA_STRUCTURES_LINKED_LIST_H

// singly linked

template <class T>
class linked_list {
  public:
    class node {
      public:
        T data;
        node *next;
        node(T _d, node *_n);
        node(T _d);
    };

    linked_list();

    void add(T i);
    void append(linked_list<T>& l);
  private:
    node *head, *tail;
};

#endif
