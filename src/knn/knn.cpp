#include "knn.h"
#include "graph.h"
#include <vector>
#include "linalg.h"
#include <limits>
#include "heap.h"
#include "arrayutil.h"
#include <algorithm>
#include "matrix.h"
#include <random>
#include <thread>
#include <future>

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

std::vector<int> knn(int k, std::vector<double> &query_point, Graph &knn_graph, int iter, std::mt19937 &mt, int e_param, int step) {
    Heap<double> pq{ knn_graph.query2(k, query_point, mt, e_param, step) };
    for (int i = 1; i < iter; i++) {
        auto qres{ knn_graph.query2(k, query_point, mt, e_param, step) };
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
    return subset_linear_search(k, querypoint, data, 0, data.size()-1); 
}

std::vector<int> subset_linear_search(int k, std::vector<double> &querypoint, std::vector<std::vector<double>> &data, int first_index, int last_index) {
    Heap<double> pq{k}; 
    for (int i = first_index; i < (first_index + k); i++) {
        pq.insert(Heapnode<double>(i, sqdist(querypoint, data[i])));
    }
    for (int i = (first_index + k); i <= last_index; i++) {
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

std::vector<int> list_linear_search(int k, std::vector<double> &querypoint, std::vector<std::vector<double>> &data, std::vector<int> &indeces) {
    Heap<double> pq{k}; 
    if (indeces.size() <= k)
        return indeces;

    for (int i = 0; i < k; i++) {
        pq.insert(Heapnode<double>(indeces[i], sqdist(querypoint, data[indeces[i]])));
    }
    for (int i = k; i <= indeces.size(); i++) {
        double distance{ sqdist(querypoint, data[indeces[i]]) };
        if (distance < pq[0].m_value) {
            pq.insert(Heapnode<double>(indeces[i], distance));
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

std::vector<int> parallel_linear_search(int k, std::vector<double> &querypoint, std::vector<std::vector<double>> &data) {
    //HUOM REFAKTOROI HARDCODED THREADLIMIT POIS
    const int max_threads{2};
    int chunk_size{ data.size()/max_threads };
    std::vector<std::future<std::vector<int>>> task_list{max_threads};
    task_list[0] = std::async(std::launch::async, subset_linear_search, k, std::ref(querypoint), std::ref(data), 0, chunk_size-1);
    for (int i = 1; i < max_threads - 1; i++) {
        task_list[i] = std::async(std::launch::async, subset_linear_search, k, std::ref(querypoint), std::ref(data), i*chunk_size, (i+1)*chunk_size - 1);
    }
    task_list[max_threads-1] = std::async(std::launch::async, subset_linear_search, k, std::ref(querypoint), std::ref(data), data.size() - chunk_size, data.size() -1);

    std::vector<int> results{max_threads*k}; 
    for (int i = 0; i < max_threads; i++) {
        auto indeces{task_list[i].get()};
        for (int j = 0; j < k; j++) { 
            results.push_back(indeces[j]);
        }
    }
    return list_linear_search(k, querypoint, data, results); 
}
