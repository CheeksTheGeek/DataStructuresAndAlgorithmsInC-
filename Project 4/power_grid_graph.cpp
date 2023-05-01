#include "power_grid_graph.hpp"

#include <fstream>

#include "illegal_exception.hpp"

void PowerGridGraph::load(std::string filename) {
    std::ifstream file(filename);
    int num_vertices_in_file;
    file >> num_vertices_in_file;
    if (!file.is_open()) return;
    int station1_id, station2_id, cost;
    while (file >> station1_id >> station2_id >> cost) {
        insertConnection(station1_id, station2_id, cost);
    }
}

std::vector<EDGE_I_TRIPLET> PowerGridGraph::generatePrimMST() {
    // Prim's algorithm
    if (num_edges_ == 0) {
        return std::vector<EDGE_I_TRIPLET>();
    }

    bool visited[outer_array_size_];
    for (int i = 0; i < outer_array_size_; i++) visited[i] = false;

    std::vector<EDGE_I_TRIPLET> minimum_spanning_tree;
    EdgesPriorityQueue* edge_pq_heap = new EdgesPriorityQueue(num_edges_ + 1);  // the priority queue is a min heap

    auto random_index_vertice = valid_mst_starter_index_;
    visited[random_index_vertice] = true;

    for (auto i : adj_list_[random_index_vertice]) {
        edge_pq_heap->insert(random_index_vertice + 1, std::get<0>(i), std::get<1>(i));
    }

    // the priority queue is now filled with all the edges of the random vertice, in the format (parent, child, cost)
    while (!edge_pq_heap->isEmpty()) {
        auto edge = edge_pq_heap->extractMinimumFromTop();
        int parent = std::get<0>(edge);
        int child = std::get<1>(edge);
        int cost = std::get<2>(edge);
        if (visited[child - 1]) continue;
        visited[child - 1] = true;
        minimum_spanning_tree.push_back(std::make_tuple(parent, child, cost));
        for (auto neighbour_of_top_child : adj_list_[child - 1]) {
            if (!visited[std::get<0>(neighbour_of_top_child) - 1]) {
                edge_pq_heap->insert(child, std::get<0>(neighbour_of_top_child), std::get<1>(neighbour_of_top_child));
            }
        }
    }
    delete edge_pq_heap;
    return minimum_spanning_tree;
}

std::vector<EDGE_I_TRIPLET> PowerGridGraph::generateKruskalMST() {
    if (num_edges_ == 0) {
        return std::vector<EDGE_I_TRIPLET>();
    }
    std::vector<EDGE_I_TRIPLET> minimum_spanning_tree;
    std::vector<EDGE_I_TRIPLET> sorted_edges;
    for (int i = 0; i < outer_array_size_; i++) {
        for (auto j : adj_list_[i]) {
            sorted_edges.push_back(std::make_tuple(i + 1, std::get<0>(j), std::get<1>(j)));
        }
    }
    std::sort(sorted_edges.begin(), sorted_edges.end(), [](const EDGE_I_TRIPLET& a, const EDGE_I_TRIPLET& b) {
        return std::get<2>(a) < std::get<2>(b);
    });
    DisjointSet* disjoint_set = new DisjointSet(outer_array_size_);
    for (auto i : sorted_edges) {
        int parent = std::get<0>(i);
        int child = std::get<1>(i);
        int cost = std::get<2>(i);
        if (disjoint_set->findRep(parent - 1) != disjoint_set->findRep(child - 1)) {
            disjoint_set->unionSet(parent - 1, child - 1);
            minimum_spanning_tree.push_back(i);
        }
    }
    delete disjoint_set;
    return minimum_spanning_tree;
}

bool PowerGridGraph::insertConnection(int station1_id, int station2_id, int cost) {
    if (station1_id > 50000 || station2_id > 50000 || cost < 1 || station1_id < 1 || station2_id < 1) throw IllegalException();
    auto max = [](int a, int b) { return a > b ? a : b; };
    if (station1_id == station2_id) return false;
    if (max(station1_id, station2_id) > outer_array_size_) {
        int new_size = max(station1_id, station2_id);
        std::vector<RELATION_I_PAIR>* new_adj_list = new std::vector<RELATION_I_PAIR>[new_size];
        for (int i = 0; i < outer_array_size_; i++) {
            new_adj_list[i] = adj_list_[i];
        }
        delete[] adj_list_;
        adj_list_ = new_adj_list;
        outer_array_size_ = new_size;
    }
    for (auto i : adj_list_[station1_id - 1])
        if (std::get<0>(i) == station2_id) return false;

    for (auto i : adj_list_[station2_id - 1])
        if (std::get<0>(i) == station1_id) return false;

    adj_list_[station1_id - 1].push_back(std::make_tuple(station2_id, cost));
    adj_list_[station2_id - 1].push_back(std::make_tuple(station1_id, cost));
    valid_mst_starter_index_ = adj_list_[valid_mst_starter_index_].size() > max(adj_list_[station1_id - 1].size(), adj_list_[station2_id - 1].size()) ? valid_mst_starter_index_ : (adj_list_[station1_id - 1].size() > adj_list_[station2_id - 1].size() ? station1_id - 1 : station2_id - 1);
    num_edges_++;
    return true;
}

bool PowerGridGraph::removeStation(int station_id) {
    if (station_id > 50000 || station_id < 1) throw IllegalException();
    if (station_id > outer_array_size_ || adj_list_[station_id - 1].size() == 0) return false;
    bool is_valid_mst_starter = valid_mst_starter_index_ == station_id;
    for (auto i : adj_list_[station_id - 1]) {
        for (auto j = adj_list_[std::get<0>(i) - 1].begin(); j != adj_list_[std::get<0>(i) - 1].end(); j++) {
            if (std::get<0>(*j) == station_id) {
                adj_list_[std::get<0>(i) - 1].erase(j);
                num_edges_--;
                break;
            }
        }
    }
    adj_list_[station_id - 1].clear();

    for (int i = 0; i < outer_array_size_; i++) {
        if (adj_list_[i].size() > 0) {
            valid_mst_starter_index_ = i;
            break;
        }
    }
    return true;
}

bool PowerGridGraph::printConnectedStations(int station_id) {
    if (station_id > 50000 || station_id < 1) throw IllegalException();
    if (station_id > outer_array_size_ || adj_list_[station_id - 1].size() == 0) return false;
    if (num_edges_ == 0) {
        return false;
    }
    for (auto i : adj_list_[station_id - 1]) {
        std::cout << std::get<0>(i) << " ";
    }
    std::cout << std::endl;
    return true;
}

bool PowerGridGraph::printPrimMST() {
    if (num_edges_ == 0) {
        return false;
    }
    auto mst = generatePrimMST();
    for (auto i : mst) {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << " ";
    }
    std::cout << std::endl;
    return true;
}

bool PowerGridGraph::printKruskalMST() {
    if (num_edges_ == 0) {
        return false;
    }
    auto mst = generateKruskalMST();
    for (auto i : mst) {
        std::cout << std::get<0>(i) << " " << std::get<1>(i) << " " << std::get<2>(i) << " ";
    }
    std::cout << std::endl;
    return true;
}

// returns the total cost of all edges in MST
int PowerGridGraph::summatePrimMSTCost() {
    if (num_edges_ == 0) {
        return 0;
    }
    int sum = 0;
    auto mst = generatePrimMST();
    for (auto i : mst) {
        sum += std::get<2>(i);
    }
    return sum;
}

// returns the total cost of all edges in MST
int PowerGridGraph::summateKruskalMSTCost() {
    if (num_edges_ == 0) {
        return 0;
    }
    int sum = 0;
    auto mst = generateKruskalMST();
    for (auto i : mst) {
        sum += std::get<2>(i);
    }
    return sum;
}

// returns the weight of the edge between two stations
int PowerGridGraph::getWeight(int station1_id, int station2_id) {
    if (station1_id > 50000 || station2_id > 50000 || station1_id < 1 || station2_id < 1) throw IllegalException();
    if (station1_id > outer_array_size_ || station2_id > outer_array_size_) return -1;
    for (auto i : adj_list_[station1_id - 1]) {
        if (std::get<0>(i) == station2_id) return std::get<1>(i);
    }
    return -1;
}
