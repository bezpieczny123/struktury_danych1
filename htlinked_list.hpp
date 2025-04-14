#ifndef HTLinkedList_HPP
#define HTLinkedList_HPP

#include <stdexcept>

template <typename T>
class HTLinkedList;

template <typename T>
class node {
private:
    T elem;
    node<T>* next;

    friend class HTLinkedList<T>;
};

template <typename T>
class HTLinkedList {
public:
    HTLinkedList()
        : head(nullptr), tail(nullptr) {
    };
    ~HTLinkedList() {
        while (!isEmpty()) removeFront();
    }
    [[nodiscard]] bool isEmpty() const {
        return head == nullptr;
    }
    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("HTLinkedList is empty");
        }
        return head->elem;
    }
    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("HTLinkedList is empty");
        }
		return tail->elem; // bezpoœrednio przez tail
    }
    const T& chosen(const int index) const {
        if (index < 0) {
            throw std::out_of_range("Index cannot be negative");
        }
        if (index == 0) {
            return front();
        }
        node<T>* t = head;
        for (int i = 0; i < index && t != nullptr; i++) {
            t = t->next;
        }
        if (t == nullptr) {
            throw std::out_of_range("out of range");
        }
        return t->elem;
    }
    void addFront(const T& e) {
        auto* v = new node<T>;
        v->elem = e;
        v->next = head;
        head = v;
		if (tail == nullptr) { // dodajemy tail dla wczeœniej pustej listy
            tail = head;
        }
    }
    void addBack(const T& e) {
        auto* v = new node<T>;
        v->elem = e;
        v->next = nullptr;
        if (head == nullptr) {
            head = v;
            tail = v;       // ustawiamy tail na jedyny element
        }
        else {
			tail->next = v; // dodanie bezpoœrednio na koniec listy
            tail = v;
        }
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
            throw std::out_of_range("HTLinkedList is empty");
        }
        auto* newnode = new node<T>;
        newnode->elem = e;
        newnode->next = temp->next;
        temp->next = newnode;
		if (newnode->next == nullptr) { // zmiana taila na ostatni element
            tail = newnode;
        }
    }
    void removeFront() {
        if (head == nullptr) {
            throw std::out_of_range("HTLinkedList is empty");
        }
        node<T>* t = head;
        head = t->next;
        if (head == nullptr) { 
			tail = nullptr;     // usuwamy wartoœæ taila przy usuwaniu jedynego elementu
        }
        delete t;
    }
    void removeBack() {
        if (head == nullptr) {
            throw std::out_of_range("HTLinkedList is empty");
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
			tail = nullptr; // usuwamy wartoœæ taila przy usuwaniu jedynego elementu
            return;
        }
        node<T>* t = head;
        while (t->next->next != nullptr) {
            t = t->next;
        }
        delete t->next;
        t->next = nullptr;
		tail = t;           // zmiana taila przy usuwaniu ostatniego elementu
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
		if (nodeToDelete == tail) {      // zmiana taila jesli jest on usuwany
            tail = t;
        }
        delete nodeToDelete;
    }
    int findIndexOf(const T& e) const {
        node<T>* t = head;
        int index = 0;
        while (t != nullptr) {
            if (t->elem == e)
                return index;
            t = t->next;
            index++;
        }
        return -1;
    }
private:
    node<T>* head;
    node<T>* tail; // dodany tail
};

#endif //HTLinkedList_HPP