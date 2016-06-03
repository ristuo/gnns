#ifndef ARRAYUTIL_H
#define ARRAYUTIL_H
#include <vector>
#include <iostream>
#include <assert.h>
template <typename T>
int binary_search(const std::vector<T> &a, T value, int start, int end) {
    assert(end < a.size());
    assert(start <= end);

    if (start + 1 == end) {
        if (a[end] == value) 
            return end;
        return start;
    }

    int midpoint = start + (end - start) / 2;
    if (value <= a[midpoint]) {
        return binary_search(a, value, start, midpoint);
    }
    return binary_search(a, value, midpoint, end);
}

template <typename T>
T min(T a, T b) {
    if (a <= b) 
        return a;
    return b;
}

template <typename T>
void swap(T &a, T &b) {
    T tmp{a};
    a = b;
    b = tmp;
}

template <typename T>
void sort(std::vector<T> &a) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = i+1; j < a.size(); j++) {
            if (a[j] < a[i]) {
                swap(a[i], a[j]);
            }
        }
    }
}

template <typename T>
void partition(std::vector<T> &v, int i, int j) {
    T split = v[j];
}

template <typename T>
void print_vector(std::vector<T> &v) {
    for (T element : v) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
#endif
