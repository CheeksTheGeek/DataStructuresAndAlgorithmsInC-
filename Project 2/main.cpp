// Using Google's C++ style guide
// https://google.github.io/styleguide/cppguide.html

#include <iostream>
#include <string>
#include "OpenAddressedTable.hpp"
#include "SeparateChainedTable.hpp"

void OpenAddressedTableDriver();

void ChainedTableDriver();

void printStatus(bool statusOrMessage = false, bool status = true, std::string message = "nothing");

int main() {
    std::string implementation_type;
    std::cin >> implementation_type;
    if (implementation_type == "ORDERED") {
        ChainedTableDriver();
    } else if (implementation_type == "OPEN") {
        OpenAddressedTableDriver();
    }
    return 0;
}

void OpenAddressedTableDriver() {
    OpenAddressedTable *open_addr_table{nullptr};
    std::string command;
    while (std::cin >> command) {
        if (command == "M") {
            unsigned int N, P;
            std::cin >> N >> P;
            open_addr_table = new OpenAddressedTable(N, P);
            printStatus(false, true);
        } else if (command == "INSERT") {
            unsigned int PID;
            std::cin >> PID;
            if (
                    !open_addr_table->isTableFull() &&
                    !open_addr_table->isProcessInTable(PID)) {
                open_addr_table->insertProcess(PID);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "SEARCH") {
            unsigned int PID;
            std::cin >> PID;
            if (open_addr_table->isProcessInTable(PID)) {
                printStatus(true, true, "found " + std::to_string(PID) + " in " +
                                        std::to_string(open_addr_table->getIndexForInsertionOrAccession(true, PID)));
            } else {
                printStatus(true, false, "not found");
            }
        } else if (command == "WRITE") {
            unsigned int PID, ADDR, x;
            std::cin >> PID >> ADDR >> x;
            if (open_addr_table->isProcessInTable(PID) && open_addr_table->isAddressInPageScope(ADDR)) {
                open_addr_table->writeValue(PID, ADDR, x);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "READ") {
            unsigned int PID, ADDR;
            std::cin >> PID >> ADDR;
            if (open_addr_table->isProcessInTable(PID) && open_addr_table->isAddressInPageScope(ADDR)) {
                printStatus(true, true,
                            std::to_string(ADDR) + " " + std::to_string(open_addr_table->readValue(PID, ADDR)));
            } else {
                printStatus(false, false);
            }
        } else if (command == "DELETE") {
            unsigned int PID;
            std::cin >> PID;
            if (open_addr_table->isProcessInTable(PID)) {
                open_addr_table->deleteProcess(PID);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "PRTTB") {
            open_addr_table->printTable();
        } else if (command == "END") {
            delete open_addr_table;
            break;
        }
    }
}

void ChainedTableDriver() {
    SeparateChainedTable *chained_table{nullptr};
    std::string command;
    while (std::cin >> command) {
        if (command == "M") {
            unsigned int N, P;
            std::cin >> N >> P;
            chained_table = new SeparateChainedTable(N, P);
            printStatus(false, true);
        } else if (command == "INSERT") {
            unsigned int PID;
            std::cin >> PID;
            if (!chained_table->isTableFull() && !chained_table->isProcessInTable(PID)) {
                chained_table->insertProcess(PID);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "SEARCH") {
            unsigned int PID;
            std::cin >> PID;
            if (chained_table->isProcessInTable(PID)) {
                printStatus(true, true, "found " + std::to_string(PID) + " in " +
                                        std::to_string(chained_table->primaryHashFunction(PID)));
            } else {
                printStatus(true, false, "not found");
            }
        } else if (command == "WRITE") {
            unsigned int PID, V_ADDR, x;
            std::cin >> PID >> V_ADDR >> x;
            if (chained_table->isProcessInTable(PID) && chained_table->isAddressInPageScope(V_ADDR)) {
                chained_table->writeValue(PID, V_ADDR, x);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "READ") {
            unsigned int PID, ADDR;
            std::cin >> PID >> ADDR;
            if (chained_table->isProcessInTable(PID) && chained_table->isAddressInPageScope(ADDR)) {
                printStatus(true, true,
                            std::to_string(ADDR) + " " + std::to_string(chained_table->readValue(PID, ADDR)));
            } else {
                printStatus(false, false);
            }
        } else if (command == "DELETE") {
            unsigned int PID;
            std::cin >> PID;
            if (chained_table->isProcessInTable(PID)) {
                chained_table->deleteProcess(PID);
                printStatus(false, true);
            } else {
                printStatus(false, false);
            }
        } else if (command == "PRINT") {
            unsigned int m;
            std::cin >> m;
            if (chained_table->isChainEmpty(m)) {
                printStatus(true, false, "chain is empty");
            } else {
                chained_table->printChain(m);
            }
        } else if (command == "PRTTB") {
            chained_table->printTable();
        } else if (command == "END") {
            delete chained_table;
            break;
        }
    }
}

// when statusOrMessage is false, print out status (success or failure)
// when statusOrMessage is true, print out message(given in the third argument)
void printStatus(bool statusOrMessage, bool status, std::string message) {
    if (!statusOrMessage) {
        if (status) {
            std::cout << "success" << std::endl;
        } else {
            std::cout << "failure" << std::endl;
        }
    } else {
        std::cout << message << std::endl;
    }
}