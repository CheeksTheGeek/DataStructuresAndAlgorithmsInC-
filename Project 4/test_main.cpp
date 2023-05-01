#include <iostream>

#include "illegal_exception.hpp"
#include "power_grid_graph.hpp"

int main() {
    PowerGridGraph *graph = new PowerGridGraph();
    std::string command;
    while (std::cin >> command) {
        if (command == "LOAD") {
            std::string filename;
            std::cin >> filename;
            graph->load(filename);
            std::cout << "success" << std::endl;
        } else if (command == "INSERT") {
            int station1_id, station2_id;
            long cost;
            std::cin >> station1_id >> station2_id >> cost;
            try {
                if (graph->insertConnection(station1_id, station2_id, cost)) {
                    std::cout << "success" << std::endl;
                } else {
                    std::cout << "failure" << std::endl;
                }
            } catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "PRINT") {
            int station_id;
            std::cin >> station_id;
            try {
                if (!graph->printConnectedStations(station_id)) {
                    std::cout << "failure" << std::endl;
                }
            } catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "DELETE") {
            int station_id;
            std::cin >> station_id;
            try {
                if (graph->removeStation(station_id)) {
                    std::cout << "success" << std::endl;
                } else {
                    std::cout << "failure" << std::endl;
                }
            } catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "MST") {
            if (!graph->printPrimMST()) std::cout << "failure" << std::endl;
        } else if (command == "MSTK") {
            if (!graph->printKruskalMST()) std::cout << "failure" << std::endl;
        } else if (command == "COST") {
            std::cout << "cost is " << graph->summatePrimMSTCost() << std::endl;
        } else if (command == "COSTK") {
            std::cout << "cost is " << graph->summateKruskalMSTCost() << std::endl;
        } else if (command == "WEIGHT") {
            int station1_id, station2_id;
            std::cin >> station1_id >> station2_id;
            try {
                if (graph->getWeight(station1_id, station2_id) == -1) {
                    std::cout << "failure" << std::endl;
                } else {
                    std::cout << "weight is " << graph->getWeight(station1_id, station2_id) << std::endl;
                }
            } catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "EDGES") {
            std::cout << graph->getNumberOfEdges() << std::endl;
        } else if (command == "END") {
            break;
        }

        else {
            continue;
        }
    }
    delete graph;
    graph = nullptr;
    return 0;
}
