#ifndef KNN_H
#define KNN_H
#include "graph.h"
#include <random>
#include <vector>

std::vector<int> knn(int k, std::vector<double> &querypoint, Graph &knn_graph,
                     int iter, std::mt19937 &mt, int e_param = 1000,
                     int step = 5);

Matrix knn_adj_graph(int k, std::vector<std::vector<double>> data);

std::vector<int> linear_search(int k, std::vector<double> &querypoint,
                               std::vector<std::vector<double>> &data);

std::vector<int> subset_linear_search(int k, std::vector<double> &querypoint,
                                      std::vector<std::vector<double>> &data,
                                      int first_index, int last_index);

std::vector<int> parallel_linear_search(int k, std::vector<double> &querypoint,
                                        std::vector<std::vector<double>> &data);
#endif
