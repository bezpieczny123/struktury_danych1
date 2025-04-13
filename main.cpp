#include <chrono>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "slinked_list.hpp"
#include "dynamic_array.hpp"

std::ofstream file;

std::chrono::steady_clock::time_point begin, end;

void startTimer() {
    begin = std::chrono::steady_clock::now();
}

void stopTimer() {
    end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    std::cout << duration << ", ";
    file << duration << ",";
}

#define MEASURE_SOME(function_call) \
    startTimer(); \
    function_call; \
    stopTimer();


template <template <typename> class StructureType>
void measure_structure(const std::string& structureName, const std::vector<int>& listSizes) {
    file.open(structureName + ".csv");
    file << structureName << "\n";
    file << "addFront, removeFront, addBack, removeBack, addChosen, removeChosen, findIndexOf\n"; \
    StructureType<int> List;
    for (int a = 1; a < 12; a++) {
        int n = listSizes[a];
        for(int i = 1; i < listSizes[a] - listSizes[a - 1]; i++) {
            if (structureName == "SLinkedList") {
                List.addFront(23);
            } else {
                List.addBack(23);
            }
        }
        for(int i = 0; i < 100; i++) {
            file << n << ",";
            MEASURE_SOME(List.addFront(35));
            MEASURE_SOME(List.removeFront());
            MEASURE_SOME(List.addBack(35));
            MEASURE_SOME(List.removeBack());
            MEASURE_SOME(List.addChosen(7, n / 2));
            MEASURE_SOME(List.removeChosen(n / 2));
            MEASURE_SOME(List.findIndexOf(n / 2));
            file << "\n";
            std::cout << std::endl;
        }
        file << "\n";
    }
    file.close();
}

int main() {
    std::vector<int> listSizes = {0, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000, 512000, 1024000};
    measure_structure<SLinkedList>("SLinkedList", listSizes);
    measure_structure<DynamicArray>("DynamicArray", listSizes);

    return EXIT_SUCCESS;
}