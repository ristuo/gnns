#ifndef GRAPH_H
#define GRAPH_H
#include "node.h"
#include <vector>
#include <iostream>
#include "matrix.h"
#include "heap.h"
#include "csvio.h"

class Graph {
    private:
        static int s_id_generator;
        std::vector<Node> m_nodes; 
    public:
        static int get_id() { return s_id_generator++;};
        std::vector<Node> get_nodes() { return m_nodes; };
        Graph(Matrix adjacency);
        Graph(char * file_path) : Graph( read_csv(file_path)) {};
        Graph( int k, std::vector<std::vector<double>>& data, bool verbose);
        std::vector<Node> get_m_nodes() { return m_nodes;};
        void set_values(std::vector<std::vector<double>> values);
        void set_values(const char * file_path);
        Node* query(std::vector<double> &querypoint);
        Heap<double> query2(int k, std::vector<double> &querypoint, int e_param = 1000, int step = 5);
    friend std::ostream& operator<<(std::ostream& os, Graph& graph);
};

        Graph create_graph(int k, std::vector<std::vector<double>> values, bool verbose=false);
#endif
