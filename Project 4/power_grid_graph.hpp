#pragma once

#include <iostream>
#include <tuple>
#include <vector>

#include "illegal_exception.hpp"

#define EDGE_I_TRIPLET std::tuple<int, int, int>  // EDGE is a tuple (station1_id, station2_id, cost)
#define RELATION_I_PAIR std::tuple<int, int>      // RELATION is a tuple (other_station_id, cost)

// This class simulates a power grid, using an adjacency list representation of the graph
class PowerGridGraph {
   private:
    std::vector<RELATION_I_PAIR> *adj_list_;  // vector of vector of tuples (station1_id, station2_id, cost)
    int outer_array_size_;
    int num_edges_;
    int valid_mst_starter_index_{0};
    // returns a vector of tuples (station1_id, station2_id, cost) representing the minimum spanning tree, by convention, station1_id is parent of station2_id
    std::vector<EDGE_I_TRIPLET> generatePrimMST();
    std::vector<EDGE_I_TRIPLET> generateKruskalMST();

    // Priority queue for edges, implemented as a min heap (priority queue), all functions definition inside edges_priority_queue.cpp
    class EdgesPriorityQueue {
       private:
        EDGE_I_TRIPLET *heap_;
        int back_{0};
        int size_;

        // heapifs subtree with root at index i
        void minHeapify(int i);

       public:
        // size value init constructor
        inline EdgesPriorityQueue(int size) : size_(size) { heap_ = new EDGE_I_TRIPLET[size]; }
        // destructor
        ~EdgesPriorityQueue() { delete[] heap_, heap_ = nullptr; }
        // inserts new element into the heap
        void insert(int node1, int node2, int weight);
        // extracts minimum element from the heap
        EDGE_I_TRIPLET extractMinimumFromTop();
        // prints the state of the heap
        void print();
        // returns true if the heap is empty
        inline bool isEmpty() { return back_ == 0; }
    };

    struct DisjointSet {
        int *representative_;  // the leader of the set
        int *rank_;            // the rank_ of the set
        int n_;                // number of nodes in the set

        // constructor
        DisjointSet(int n) : n_{n}, representative_{new int[n]}, rank_{new int[n]} {
            for (int i = 0; i < n; i++) {
                representative_[i] = i;
                rank_[i] = 0;
            }
        }
        // destructor
        ~DisjointSet() {
            delete[] representative_, delete[] rank_;
        }
        // find the representative of a node
        int findRep(int node) {
            if (representative_[node] == node) {
                return node;
            }
            return representative_[node] = findRep(representative_[node]);
        }
        // union of two nodes
        void unionSet(int node1, int node2) {
            int rep1 = findRep(node1);
            int rep2 = findRep(node2);
            if (rank_[rep1] < rank_[rep2]) {
                representative_[rep1] = rep2;
            } else if (rank_[rep1] > rank_[rep2]) {
                representative_[rep2] = rep1;
            } else {
                representative_[rep2] = rep1;
                rank_[rep1]++;
            }
        }
    };

   public:
    // default constructor: initializes the graph adjacency list with 50000 stations
    PowerGridGraph() : outer_array_size_(50000), num_edges_(0) { adj_list_ = new std::vector<RELATION_I_PAIR>[50000]; }
    // value init constructor: initializes the graph adjacency list with num_vertices stations
    PowerGridGraph(int num_vertices) : outer_array_size_{num_vertices}, num_edges_(0), adj_list_(new std::vector<RELATION_I_PAIR>[num_vertices]) {}
    // destructor
    ~PowerGridGraph() { delete[] adj_list_; }
    // load the graph from a file
    void load(std::string filename);
    // insert a connection between two stations, if either station isn't in the Grid, adds it
    bool insertConnection(int station1_id, int station2_id, int cost);
    // removes a station from the Power Grid
    bool removeStation(int station_id);
    // print all the stations connected to the given station s
    bool printConnectedStations(int station_id);
    // print the minimum spanning tree using the generateMST() function
    bool printPrimMST();
    // print the minimum spanning tree using Kruskal's algorithm
    bool printKruskalMST();
    // returns the total cost of all edges in MST from Prim's algorithm
    int summatePrimMSTCost();
    // returns the total cost of all edges in MST from Kruskal's algorithm
    int summateKruskalMSTCost();
    // returns the weight of the edge between two stations
    int getWeight(int station1_id, int station2_id);
    // returns the number of nodes in the graph
    int getNumberOfEdges() { return num_edges_; }
};
