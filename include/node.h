#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>
#include "heap.h"
class Node {
    private:
        int m_id;
        std::vector<Node *> m_edges_to;
    public:
        Node();
        std::vector<double> m_value;
        double dist(Node &x);
        void add_neighbor(Node *node);
        void set_value(std::vector<double> &x);
        std::vector<Node *> get_m_edges_to() { return m_edges_to;};
        int get_m_id() { return m_id;};
        Node* neighbor_query(std::vector<double> &querypoint, int e_param = 1000);
        Node* neighbor_query2(int k, Heap<double> &pq, std::vector<double> &querypoint, std::vector<int> &taboo_list, int e_param = 1000);
    friend std::ostream& operator<<(std::ostream& os, Node& node);
};
#endif
