#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "slinked_list.hpp"
//#include "dynamic_arraay.hpp"

std::ofstream file;

std::chrono::steady_clock::time_point begin, end;

void startTimer() {
    begin = std::chrono::steady_clock::now();
}

void stopTimer() {
    end = std::chrono::steady_clock::now();;
    std::cout << end - begin << ", ";
    file << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << ",";
}

#define MEASURE_SOME(function) \
    startTimer(); \
    function; \
    stopTimer();

#define MEASURE_ALL(structure) \
    file.open(#structure ".csv"); \
    file << #structure << "\n"; \
    file << "addFront, removeFront, addBack, removeBack, addChosen, removeChosen, findIndexOf\n"; \
    structure<int> List; \
    begin = std::chrono::steady_clock::now(); \
    end = std::chrono::steady_clock::now(); \
    \
    std::vector<int> listSizes = {0, 10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000}; \
    for (int a = 1; a < 12; a++) {\
        int n = listSizes[a]; \
        for(int i = 1; i < listSizes[a] - listSizes[a - 1]; i++) {\
            List.addFront(156); \
        } \
        for(int i = 0; i < 100; i++) { \
            file << n << ","; \
            MEASURE_SOME(List.addFront(35)); \
            MEASURE_SOME(List.removeFront()); \
            MEASURE_SOME(List.addBack(35)); \
            MEASURE_SOME(List.removeBack()); \
            MEASURE_SOME(List.addChosen(7, n / 2)); \
            MEASURE_SOME(List.removeChosen(n / 2)); \
            MEASURE_SOME(List.findIndexOf(n / 2)); \
            file << "\n"; \
            std::cout << std::endl; \
        } \
        file << "\n"; \
    }\
    file.close();


int main() {
    MEASURE_ALL(SLinkedList);

    return EXIT_SUCCESS;
}