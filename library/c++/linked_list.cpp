struct node {
    int data;
    node *next;
    node(int _d, node *_n): next{n},data{_d} {}
    node(int _d): node(_d,NULL) {}
};

struct linked_list {
    node *head, *tail;
    linked_list(): head{NULL}, tail{NULL} {}
    void add(int i) {
        node *tmp = new node(i);
        if(head == NULL) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
    }

    void append(linked_list& l) {
        tail->next = l.head;
        tail = l.tail;
    }
};
