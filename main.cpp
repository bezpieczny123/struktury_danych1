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
    std::cout << end - begin << ", ";
    measures_file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ", ";
}

#define MEASURE_SOME(function) \
    startTimer(); \
    function; \
    stopTimer();

#define MEASURE_ALL(structure) \
    structure<int> List; \
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now(); \
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); \
\
    for(int i = 0; i < 10; i++) {\
        List.addFront(156); \
    } \
\
    for(int i = 0; i < 100; i++) { \
        MEASURE_SOME(List.addFront(35)); \
        MEASURE_SOME(List.removeFront()); \
        MEASURE_SOME(List.addBack(35)); \
        MEASURE_SOME(List.removeBack()); \
        MEASURE_SOME(List.addChosen(7, 3)); \
        MEASURE_SOME(List.removeChosen(4)); \
        MEASURE_SOME(List.front()); \
        MEASURE_SOME(List.back()); \
        MEASURE_SOME(List.chosen(3)); \
        std::cout << std::endl; \
    } \


int main() {
    measures_file.open("measures_file.txt");

    if (!measures_file.is_open()) {
        std::cerr << "Error opening measures.csv for writing!" << std::endl;
        return 1;
    }

    MEASURE_ALL(SLinkedList);

    measures_file.close();

    return EXIT_SUCCESS;
}