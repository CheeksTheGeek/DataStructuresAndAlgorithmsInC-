#include "power_grid_graph.hpp"

#define LEFT(x) (2 * x + 1)
#define RIGHT(x) (2 * x + 2)
#define PARENT(x) ((x - 1) / 2)

void PowerGridGraph::EdgesPriorityQueue::minHeapify(int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int smallest = i;
    if (l < back_ && std::get<2>(heap_[l]) < std::get<2>(heap_[i])) smallest = l;
    if (r < back_ && std::get<2>(heap_[r]) < std::get<2>(heap_[smallest])) smallest = r;
    if (smallest != i) {
        std::swap(heap_[i], heap_[smallest]);
        minHeapify(smallest);
    }
}

void PowerGridGraph::EdgesPriorityQueue::insert(int node1, int node2, int weight) {
    EDGE_I_TRIPLET t = std::make_tuple(node1, node2, weight);
    if (back_ == size_) return;
    heap_[back_] = t;
    int i = back_;
    back_++;
    while (i != 0 && std::get<2>(heap_[PARENT(i)]) > std::get<2>(heap_[i])) {
        std::swap(heap_[i], heap_[PARENT(i)]);
        i = PARENT(i);
    }
}

EDGE_I_TRIPLET PowerGridGraph::EdgesPriorityQueue::extractMinimumFromTop() {
    if (back_ <= 0) return std::make_tuple(-1, -1, -1);
    if (back_ == 1) {
        back_--;
        return heap_[0];
    }
    EDGE_I_TRIPLET root = heap_[0];
    heap_[0] = heap_[back_ - 1];
    back_--;
    minHeapify(0);
    return root;
}

void PowerGridGraph::EdgesPriorityQueue::print() {
    std::cout << "state: " << std::endl;
    for (int i = 0; i < back_; i++) std::cout << std::get<0>(heap_[i]) << " " << std::get<1>(heap_[i]) << " " << std::get<2>(heap_[i]) << std::endl;
    std::cout << "=========" << std::endl;
}
