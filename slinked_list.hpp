#ifndef SLINKEDLIST_HPP
#define SLINKEDLIST_HPP

#include <stdexcept>

template <typename T>
class SLinkedList;

template <typename T>
class Node {
private:
    T elem;
    Node<T>* next;

    friend class SLinkedList<T>;
};

template <typename T>
class SLinkedList {
public:
    SLinkedList()
        : head(nullptr){};
    ~SLinkedList() {
        while (!isEmpty()) removeFront();
    }
    [[nodiscard]] bool isEmpty() const {
        return head == nullptr;
    }
    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("SLinkedList is empty");
        }
        return head->elem;
    }
    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("SLinkedList is empty");
        }
        Node<T>* t = head;
        while (t->next) {
            t = t->next;
        }
        return t->elem;
    }
    const T& chosen(const int index) const {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        if (index == 0) {
            return front();
        }
        Node<T>* t = head;
        for (int i = 0; i < index && t != nullptr; i++) {
            t = t->next;
        }
        if (t == nullptr) {
            throw std::out_of_range("out of range");
        }
        return t->elem;
    }
    void addFront(const T& e) {
        auto* v = new Node<T>;
        v->elem = e;
        v->next = head;
        head = v;
    }
    void addBack(const T& e) {
        auto* v = new Node<T>;
        v->elem = e;
        v->next = nullptr;
        if (head == nullptr) {
            head = v;
            return;
        }
        auto* p = head;
        while (p->next != nullptr) {
            p = p->next;
        }
        p->next = v;
    }
    void addChosen(const T& e, int index) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        if (index == 0) {
            addFront(e);
            return;
        }
        auto* temp = head;
        for (int i = 0; i < index - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }
        if (temp == nullptr) {
            throw std::out_of_range("SLinkedList is empty");
        }
        auto* newNode = new Node<T>;
        newNode->elem = e;
        newNode->next = temp->next;
        temp->next = newNode;
    }
    void removeFront() {
        if (head == nullptr) {
            throw std::out_of_range("SLinkedList is empty");
        }
        Node<T>* t = head;
        head = t->next;
        delete t;
    }
    void removeBack() {
        if (head == nullptr) {
            throw std::out_of_range("SLinkedList is empty");
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node<T>* t = head;
        while (t->next->next != nullptr) {
            t = t->next;
        }
        delete t->next;
        t->next = nullptr;
    }
    void removeChosen(int index) {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        if (index == 0) {
            removeFront();
            return;
        }
        auto* t = head;
        for (int i = 0; i < index - 1 && t != nullptr; i++) {
            t = t->next;
        }
        if (t == nullptr || t->next == nullptr) {
            throw std::out_of_range("out of range");
        }
        auto* nodeToDelete = t->next;
        t->next = nodeToDelete->next;
        delete nodeToDelete;
    }
    int findIndex(const T& e) const {
        Node<T>* t = head;
        int index = 0;
        while (t != nullptr) {
            if (t->elem == e)
                return index;
            t = t->next;
            index++;
        }
        throw std::out_of_range("out of range");
    }
private:
    Node<T>* head;
};

#endif //SLINKEDLIST_HPP