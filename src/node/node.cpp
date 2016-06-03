#include "node.h"
#include "matrix.h"
#include "graph.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "assert.h"
#include "linalg.h"
#include "limits"
#include "heap.h"

Node::Node() : m_id( Graph::get_id() ) {
    std::vector<Node *> neighbors{};
    std::vector<double> value{};
    m_edges_to = neighbors;
    m_value = value;
}

Node *Node::neighbor_query(std::vector<double> &querypoint, int e_param) {
    Node * min_node{nullptr};
    double min_dist{std::numeric_limits<double>::infinity()};
    int neighbors_explored{ 0 };
    for (Node *neighbor : m_edges_to) {
        double distance{ sqdist( querypoint, neighbor->m_value ) };
        if (distance < min_dist) {
            min_node = neighbor;
            min_dist = distance;
        }
        if (neighbors_explored > e_param) 
            break;
        neighbors_explored++;
    }
    return min_node;
}

Node *Node::neighbor_query2(int k, Heap<double> &pq, std::vector<double> &querypoint, int e_param) {
    Node * min_node{nullptr};
    int neighbors_explored{0};
    double min_dist{std::numeric_limits<double>::infinity()};
    for (Node *neighbor : m_edges_to) {
        double distance{ sqdist( querypoint, neighbor->m_value ) };
        if (pq.m_nodes.size() < k) {
            pq.insert(Heapnode<double>(neighbor->get_m_id(), distance));
        } else if (distance < pq[0].m_value && !pq.has_index(neighbor->get_m_id())) {
            pq.insert(Heapnode<double>(neighbor->get_m_id(), distance));
            pq.extractmax();
        }
        if (distance < min_dist) {
            min_node = neighbor;
            min_dist = distance;
        }
        if (neighbors_explored >= e_param) {
            break;
        }
        neighbors_explored++;
    }
    return min_node;
}

void Node::add_neighbor(Node *node) {
    m_edges_to.push_back(node);
}

void Node::set_value(std::vector<double> &x) {
    m_value = x;
}

double Node::dist(Node &x) {
    return sqdist(m_value, x.m_value);
}

std::ostream& operator<<(std::ostream& os, Node& node) {
    os << "node id: " << node.m_id << std::endl;
    os << "value: ";
    for (int i  = 0; i < std::min(5,static_cast<int>(node.m_value.size())); i++) {
        os << node.m_value[i] << " ";
    }
    os << "\nneighbors: "; 
    for (Node *neighbor : node.m_edges_to) {
        os << "\n\t" << neighbor->m_id;
    }
    return os;
}
