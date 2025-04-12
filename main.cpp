#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "slinked_list.hpp"

std::ofstream measures_file;

std::chrono::steady_clock::time_point begin, end;

void startTimer() {
    begin = std::chrono::steady_clock::now();
}

void stopTimer() {
    end = std::chrono::steady_clock::now();;
    measures_file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ", ";
}

#define MEASURE_SOMETHING(function) \
    startTimer(); \
    function; \
    stopTimer();



int main() {
    measures_file.open("measures_file.txt");

    if (!measures_file.is_open()) {
        std::cerr << "Error opening measures.csv for writing!" << std::endl;
        return 1;
    }

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

    std::cout << list.findIndex(45) << std::endl << std::endl;

    MEASURE_SOMETHING(list.addFront(25));
    MEASURE_SOMETHING(list.addBack(50));

    measures_file.close();
    return EXIT_SUCCESS;
}