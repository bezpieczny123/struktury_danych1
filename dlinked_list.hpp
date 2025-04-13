#ifndef DLINKED_LIST_HPP
#define DLINKED_LIST_HPP

template <typename T>
class DLinkedList;

template <typename T>
class DNode {
    private:
    T elem;
    DNode *prev;
    DNode *next;
    friend class DLinkedList;
};

template <typename T>
class DLinkedList {
    public:
    DLinkedList() {
        head = new DNode<T>;
        tail = new DNode<T>;
        head->next = tail;
        tail->prev = head;
    };
    ~DLinkedList() {
        while (isEmpty()) removeFront();;
        delete head;
        delete tail;
    };
    [nodiscard] bool isEmpty() const
        { return (head->next == tail); }
    const T& front() const
        { return head->next->elem; }
    const T& back() const
        { return tail->prev->elem; }
    void addFront(const T& elem) {
        add(head->elem, elem);
    }
    void addBack(const T& elem) {
        add(tail, elem);
    }
    void removeFront()
        { remove(head->next); }
    void removeBack()
        { remove(tail->prev); }
    private:
    DNode<T> *head;
    DNode<T> *tail;
protected:
    void add(DNode<T>* v, const T& e) {
        auto* u = new DNode<T>;
        u->elem = e;
        u->next = v;
        u->prev = v->prev;
        v->prev->next = u;
    }
    void remove(DNode<T>* v) {
        DNode<T>* u = v->prev;
        DNode<T>* w = u->next;
        u->next = w;
        w->prev = u;
        delete v;
    }
};

#endif //DLINKED_LIST_HPP
