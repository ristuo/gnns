#ifndef HEAP_H
#define HEAP_H
#include "arrayutil.h"
#include <iostream>
#include <vector>

template <typename T> class Heapnode {
public:
  int m_index;
  T m_value;
  Heapnode(int index, T value) : m_index(index), m_value(value){};

  friend bool operator<(const Heapnode<T> &x, const Heapnode<T> &y) {
    return x.m_value < y.m_value;
  }
  friend bool operator<=(const Heapnode<T> &x, const Heapnode<T> &y) {
    return x.m_value <= y.m_value;
  }
  friend bool operator>(const Heapnode<T> &x, const Heapnode<T> &y) {
    return x.m_value > y.m_value;
  }
  friend bool operator==(const Heapnode<T> &x, const Heapnode<T> &y) {
    return x.m_value == y.m_value;
  }
  friend std::ostream &operator<<(std::ostream &os, Heapnode<T> &hp) {
    os << hp.m_value;
    return os;
  }
};

template <typename T> class Heap {
public:
  std::vector<Heapnode<T>> m_nodes;

  Heapnode<T> operator[](int i) { return m_nodes[i]; }
  inline static int parent(int i) { return i >> 1; }
  inline static int left(int i) { return i << 1; }
  inline static int right(int i) { return (i << 1) + 1; }

  bool has_index(int i) {
    if (m_nodes.size() == 0) {
      return false;
    }
    for (Heapnode<T> x : m_nodes) {
      if (x.m_index == i)
        return true;
    }
    return false;
  }

  void max_heapify(int i) {
    int l{left(i)};
    int r{right(i)};
    int largest{0};
    if (l < m_nodes.size() && m_nodes[l] > m_nodes[i]) {
      largest = l;
    } else {
      largest = i;
    }
    if (r < m_nodes.size() && m_nodes[r] > m_nodes[largest]) {
      largest = r;
    }
    if (largest != i) {
      swap(m_nodes[i], m_nodes[largest]);
      max_heapify(largest);
    }
  };

  Heap(int size) {
    m_nodes = std::vector<Heapnode<T>>{};
    m_nodes.reserve(size);
  }

  int insert(Heapnode<T> x) {
    m_nodes.push_back(x);
    int i = static_cast<int>(m_nodes.size() - 1);
    while (i > 0 && m_nodes[parent(i)] < m_nodes[i]) {
      swap(m_nodes[i], m_nodes[parent(i)]);
      i = parent(i);
    }
    return 0;
  }

  Heapnode<T> extractmax() {
    Heapnode<T> max{m_nodes[0]};
    m_nodes[0] = m_nodes[static_cast<int>(m_nodes.size()) - 1];
    m_nodes.resize(static_cast<int>(m_nodes.size()) - 1, m_nodes[0]);
    max_heapify(0);
    return max;
  }

  friend std::ostream &operator<<(std::ostream &os, Heap<T> &heap) {
    for (Heapnode<T> hp : heap.m_nodes) {
      os << hp << " ";
    }
    return os;
  }
};
#endif
