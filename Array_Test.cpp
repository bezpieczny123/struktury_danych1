#include <iostream>
#include "Array.hpp"
#include <vector>
#include <chrono>
#include <random>
#include <functional>
#include <fstream>
#include <iomanip>

struct TestResult {
    std::string testName;
    int size;
    double time_ms;
};

std::vector<TestResult> results;

template<typename Func>
void runTest(const std::string& testName,
    const std::vector<int>& sizes,
    int test_count,
    Func testFunc) {
    std::cout << "--------------------------------------------------\n";
    std::cout << "Running tests for: " << testName << "\n";
    std::cout << "--------------------------------------------------\n";

    for (int size : sizes) {
        auto total_time = std::chrono::duration<double>::zero();

        for (int j = 0; j < test_count; ++j) {
            auto start = std::chrono::high_resolution_clock::now();
            testFunc(size);
            auto end = std::chrono::high_resolution_clock::now();
            total_time += end - start;
        }

        double time_ms = total_time.count() * 1000;
        results.push_back({ testName, size, time_ms });

        std::cout << "Time taken for " << size << " operations: "
            << time_ms << " ms\n";
    }

    std::cout << "--------------------------------------------------\n";
}

void saveResultsToCSV(const std::string& filename = "benchmark_results.csv") {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    // Write CSV header
    outFile << "Test Name;Element Count;Time (ms)\n";

    // Write data with consistent precision
    outFile << std::fixed << std::setprecision(6);
    for (const auto& result : results) {
        outFile << "\"" << result.testName << "\";"
            << result.size << ";"
            << result.time_ms << "\n";
    }

    outFile.close();
    std::cout << "Results saved to " << filename << "\n";
}

void runArrayTests(
    const std::vector<int>& sizes = { 0, 10, 50, 100, 500, 1000, 5000, 10000 },
    int test_count = 200) {

    // Clear previous results
    results.clear();

    // Test addBack
    runTest("addBack", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) {
            arr.addBack(i);
        }
        });

    // Test addFront
    runTest("addFront", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) {
            arr.addFront(i);
        }
        });

    // Test removeBack
    runTest("removeBack", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) arr.addBack(i);
        for (int i = 0; i < size; ++i) arr.removeBack();
        });

    // Test removeFront
    runTest("removeFront", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) arr.addBack(i);
        for (int i = 0; i < size; ++i) arr.removeFront();
        });

    // Test addChosen (middle)
    runTest("addChosen (middle)", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) {
            arr.addChosen(i, arr.getSize() / 2);
        }
        });

    // Test removeChosen (middle)
    runTest("removeChosen (middle)", sizes, test_count, [](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) arr.addBack(i);
        for (int i = 0; i < size; ++i) {
            arr.removeChosen(arr.getSize() / 2);
        }
        });

    // Test findIndex
    std::random_device rd;
    std::mt19937 gen(rd());
    runTest("findIndex", sizes, test_count, [&gen](int size) {
        DynamicArray<int> arr(1);
        for (int i = 0; i < size; ++i) arr.addBack(i);

        if (size > 0) {
            std::uniform_int_distribution<> dist(0, size - 1);
            for (int k = 0; k < size; ++k) {
                int target = dist(gen);
                arr.findIndex(target);
            }
        }
        });

    // Save results to CSV
    saveResultsToCSV();
}

int main() {
    runArrayTests();
    return 0;
}