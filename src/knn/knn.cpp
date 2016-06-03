#include "knn.h"
#include "graph.h"
#include <vector>
#include "linalg.h"
#include <limits>
#include "heap.h"
#include "arrayutil.h"
#include <algorithm>
#include "matrix.h"

Matrix knn_adj_graph(int k, std::vector<std::vector<double>> data) {
    Matrix res{static_cast<int>(data.size()), static_cast<int>(data.size())};
    for (int i = 0; i < data.size(); i++) {
        auto knns{ linear_search(k, data[i], data) };  
        for (int j = 0; j < k; j++) {
            res(i,knns[j]) = 1; 
        }
    }
    return res;
}

std::vector<int> knn(int k, std::vector<double> &query_point, Graph &knn_graph, int iter, int e_param, int step) {

    Heap<double> pq{ knn_graph.query2(k, query_point, e_param, step) };
    for (int i = 1; i < iter; i++) {
        auto qres{ knn_graph.query2(k, query_point, e_param, step) };
        for (Heapnode<double> x : qres.m_nodes) {
            if (x.m_value < pq[0].m_value && !pq.has_index(x.m_index)) {
                pq.insert(x);
                pq.extractmax();
            }
        }
    }
    std::vector<int> result{};
    result.reserve(k);
    for (Heapnode<double> x : pq.m_nodes) {
        result.push_back(x.m_index);
    }
    return result;
}

std::vector<int> linear_search(int k, std::vector<double> &querypoint, std::vector<std::vector<double>> &data) {
    Heap<double> pq{k}; 
    for (int i = 0; i < k; i++) {
        pq.insert(Heapnode<double>(i, sqdist(querypoint, data[i])));
    }
    for (int i = k; i < data.size(); i++) {
        double distance{ sqdist(querypoint, data[i]) };
        if (distance < pq[0].m_value) {
            pq.insert(Heapnode<double>(i, distance));
            pq.extractmax();
        }
    }
    std::vector<int> res{};
    res.reserve(k);
    for (int i = 0; i < k; i++) {
        res.push_back(pq[i].m_index);
    }
    return res;
}
