#include <iostream>
#include <chrono>
#include <fstream>
#include <array>

using namespace std;
using namespace std::chrono;

int PURE_ARR[1000];
std::array<int, 1000> ARR;

void bubbleSort(void);
void selectionSort(void);
void insertionSort(void);
void quickSort(int* arr, int low, int high); // recursive function
void mergeSort(int* arr, int begin, int end); // recursive function

int main(int argc, char** argv) {
    std::ifstream fin;
    fin.open("nums.txt");
    int i;
    int j = 0;
    while (fin >> i) {
        PURE_ARR[j] = i;
        ++j;
    }
    std::copy(std::begin(PURE_ARR), std::end(PURE_ARR), std::begin(ARR));
    fin.close();
    bubbleSort();
    selectionSort();
    insertionSort();
    auto start = high_resolution_clock::now();
    int arr[1000];
    for (int i = 0; i < 1000; ++i) { arr[i] = PURE_ARR[i]; }
    quickSort(arr, 0, 999);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout << "Quick Sort: " << duration.count() << "µs\n";
    start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) { arr[i] = PURE_ARR[i]; }
    mergeSort(arr, 0, 999);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop-start);
    std::cout << "Merge Sort: " << duration.count() << "µs\n";
    return 0;
}

void bubbleSort(void) {
    auto start = high_resolution_clock::now();
    std::array<int, 1000> arr = ARR;
    for (int i = 0; i < 999; ++i) {
        for (int j = 0; j < 1000-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout << "Bubble Sort: " << duration.count() << "µs\n"; 
}

void selectionSort(void) {
    auto start = high_resolution_clock::now();
    std::array<int, 1000> arr = ARR;
    int k;
    for (int i = 0; i < 999; ++i) {
        k = i;
        for (int j = i+1; j < 1000; ++j) {
            if (arr[j] < arr[k]) {
                k = j;
            }
        }
        if (k != i) {
            int temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout << "Selection Sort: " << duration.count() << "µs\n"; 
}

void insertionSort(void) {
    auto start = high_resolution_clock::now();
    std::array<int, 1000> arr = ARR;
    int k;
    for (int i = 1; i < 1000; ++i) {
        k = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > k) {
            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = k;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop-start);
    std::cout << "Insertion Sort: " << duration.count() << "µs\n"; 
}

void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low-1;
        int temp, j;
        for (j = low; j <= high-1; ++j) {
            if (arr[j] < pivot) {
                ++i;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = arr[i];
            }
        }
        temp = arr[i+1];
        arr[i+1] = arr[j];
        arr[j] = temp;
        int pi = i+1;
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

void mergeSort(int* arr, int begin, int end) {
    if (begin >= end) { return; }
    auto mid = begin + (end-begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid+1, end);
    auto sub1 = mid - begin + 1;
    auto sub2 = end - mid;
    auto *leftArr = new int[sub1];
    auto *rightArr = new int[sub2];
    for (int i = 0; i < sub1; ++i) { leftArr[i] = arr[begin+i]; }
    for (int j = 0; j < sub2; ++j) { rightArr[j] = arr[mid+1+j]; }
    int i1 = 0, i2 = 0, imerge = begin;
    while (i1 < sub1 && i2 < sub2) {
        if (leftArr[i1] <= rightArr[i2]) {
            arr[imerge] = leftArr[i1];
            ++i1;
        } else {
            arr[imerge] = rightArr[i2];
            ++i2;
        }
        ++imerge;
    }
    while (i1 < sub1) {
        arr[imerge] = leftArr[i1];
        ++i1;
        ++imerge;
    }
    while (i2 < sub2) {
        arr[imerge] = rightArr[i2];
        ++i2;
        ++imerge;
    }
    delete[] leftArr;
    delete[] rightArr;
}