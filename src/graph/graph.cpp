#include "graph.h"
#include <vector>
#include "matrix.h"
#include <random>
#include "knn.h"
#include <limits>
#include "heap.h"
#include <ctime>

int Graph::s_id_generator = 0;

Node* Graph::query(std::vector<double> &querypoint) {
    std::random_device rd;
    std::mt19937 mt( rd() );
    Node *node = &m_nodes[ mt() % m_nodes.size() ];
    for (int i = 0; i < 5; i++) {
        Node *new_node = node->neighbor_query(querypoint);
        if (!new_node) {
            break;
        }
        node = new_node;
    }
    return node;
}

Heap<double> Graph::query2(int k, std::vector<double> &querypoint, std::mt19937 &mt, int e_param, int step) {

    Node *node = &m_nodes[ mt() % m_nodes.size() ];
    std::vector<int> taboo_list{};
    taboo_list.reserve(step);
    Heap<double> pq{k};
    for (int i = 0; i < step; i++) {
        Node *new_node = node->neighbor_query2(k, pq, querypoint, taboo_list, e_param);
        if (!new_node) {
            break;
        }
        node = new_node;
    }
    return pq;
}

//super deprecated
Graph::Graph(Matrix adjacency) {
    long unsigned int nmb_nodes = adjacency.get_m_cols();
    m_nodes = std::vector<Node>{nmb_nodes};
    for (int i = 0; i < nmb_nodes; i++) {
        for (int j = 0; j < nmb_nodes; j++) {
            if (adjacency(i,j) == 1) {
                m_nodes[i].add_neighbor(&m_nodes[j]);
            }
        }
    }
}

Graph::Graph(int k, std::vector<std::vector<double>> &data, bool verbose) {
    time_t start{time(0)};
    long unsigned int nmb_nodes{data.size()};
    m_nodes = std::vector<Node>{nmb_nodes};
    for (int i = 0; i < nmb_nodes; i++) {
        auto neighbors{ linear_search(k+1, data[i], data) };
        for (int neighbor_index : neighbors) {
            if (neighbor_index != m_nodes[i].get_m_id()) 
                m_nodes[i].add_neighbor(&m_nodes[neighbor_index]);
        }
        if (i % 100 == 0) {
            auto aika{difftime(time(0),start)};
            if (verbose) 
                std::cout << "\tNode number " << i << " constructed at " << aika << std::endl;
        }
    }
}

Graph create_graph(int k, std::vector<std::vector<double>> values, bool verbose) {
    if (verbose) {
        std::cout << "starting to build graph" << std::endl;
    }
    auto res{ Graph( k, values, verbose ) };
    res.set_values(values);
    return res;
}

void Graph::set_values(std::vector<std::vector<double>> values) {
    for (int i = 0; i < m_nodes.size(); i++) {
        m_nodes[i].set_value( values[i] );
    }
}

void Graph::set_values(const char * file_path) {
    set_values( read_values_csv(file_path));
}

std::ostream& operator<<(std::ostream& os, Graph& graph) {
    for (Node node : graph.get_m_nodes()) {
        for (Node *edge_to : node.get_m_edges_to()) {
            std::cout << node.get_m_id() << " -> " << edge_to->get_m_id() << "\n";
        }
    } 
    return os;
}
