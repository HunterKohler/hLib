struct node {
    int data;
    node *next;
    node(int _d, node *_n): data{_d}, next{_n} {}
    node(int _d): node(_d,nullptr) {}
};

struct linked_list {
    node *head, *tail;
    linked_list(): head{nullptr}, tail{nullptr} {}
    void add(int i) {
        node *tmp = new node(i);
        if(head == nullptr) {
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
