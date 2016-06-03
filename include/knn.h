#ifndef KNN_H
#define KNN_H
#include "graph.h"
#include <vector>

std::vector<int> knn(int k, std::vector<double> &querypoint, Graph &knn_graph, int iter, int e_param = 1000, int step = 5);

Matrix knn_adj_graph(int k, std::vector<std::vector<double>> data);

std::vector<int> linear_search(int k, std::vector<double> &querypoint, std::vector<std::vector<double>> &data);
#endif
