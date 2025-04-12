#include "slinked_list.hpp"


int main() {
    SLinkedList<int> list;
    list.addFront(10);
    list.addFront(13);
    list.addFront(13);
    list.addFront(13);
    list.addFront(13);
    list.addBack(21);
    list.addChosen(45, 2);
    list.removeFront();
    list.removeBack();

    for (int i = 0; i < 10; i++) {
        std::cout << list.chosenElement(i) << std::endl;
    }

    std::cout << list.findIndex(45) << std::endl;

    return 0;
}