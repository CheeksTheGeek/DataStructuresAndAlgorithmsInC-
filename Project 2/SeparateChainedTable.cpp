#include "SeparateChainedTable.hpp"
#include <iostream>

// empty constructor
SeparateChainedTable::SeparateChainedTable() : HashPageTable(), table_(nullptr) {}

// constructor with memory size and page size
SeparateChainedTable::SeparateChainedTable(unsigned int memory_size, unsigned int page_size) : HashPageTable(
        memory_size, page_size), table_(new DynamicArrayForProcess[memory_size / page_size]) {}

// destructor
SeparateChainedTable::~SeparateChainedTable() {
    delete[] table_;
    table_ = nullptr;
}

// boolean for fullness of chains
bool SeparateChainedTable::isChainFull(unsigned int indexInPageTable) {
    return table_[indexInPageTable].getSize() == table_size_;
}

// boolean for emptiness of chain
bool SeparateChainedTable::isChainEmpty(unsigned int indexInPageTable) {
    return table_[indexInPageTable].getSize() == 0;
}

// returns the result to inequality of the index of the process in the chain to -1
// since the dual option finder function returns -1 if the process is not in the chain
bool SeparateChainedTable::isProcessInTable(unsigned int PID) {
    return getChainIndexForInsertionOrAccession(false, PID) != -1;
}

// prints the chain with spaces between the elements
void SeparateChainedTable::printChain(unsigned int indexInPageTable) {
    for (unsigned int i = 0; i < table_[indexInPageTable].getSize(); i++) {
        std::cout << table_[indexInPageTable][i].getPID() << " ";
    }
    std::cout << std::endl;
}

// inserts the process in the chain using the dual option finder function
void SeparateChainedTable::insertProcess(unsigned int PID) {
    table_[primaryHashFunction(PID)].insert(getChainIndexForInsertionOrAccession(true, PID),
                                            Process(PID, next_available_page_ * page_size_));
    page_activity_[next_available_page_] = PID;
    updateNextAvailablePage();
    number_of_pages_in_memory_++;
}

// writes the value to the address in the page
void SeparateChainedTable::writeValue(unsigned int PID, unsigned int virtual_address, int value) {
    physical_memory_[
            table_[primaryHashFunction(PID)][getChainIndexForInsertionOrAccession(false, PID)].getMemoryStart() +
            virtual_address] = value;
}

// reads the value from the address in the page
int SeparateChainedTable::readValue(unsigned int PID, unsigned int virtual_address) {
    return physical_memory_[
            table_[primaryHashFunction(PID)][getChainIndexForInsertionOrAccession(false, PID)].getMemoryStart() +
            virtual_address];
}

// deletes the process from the chain, but does not delete the page from the physical memory
void SeparateChainedTable::deleteProcess(unsigned int PID) {
    table_[primaryHashFunction(PID)].erase(getChainIndexForInsertionOrAccession(false, PID));
    page_activity_[findPhysicalIndex(PID)] = 0;
    updateNextAvailablePage();
    number_of_pages_in_memory_--;
}

// search_for_insertion_or_accession = true for getting the index of appropriate index for putting in a new process i.e. insertion
// search_for_insertion_or_accession = false  for getting the index of the PID in the chain i.e. acession
int
SeparateChainedTable::getChainIndexForInsertionOrAccession(bool search_for_insertion_or_accession, unsigned int PID) {
    unsigned int index{primaryHashFunction(PID)};
    if (search_for_insertion_or_accession) {
        for (unsigned int i = 0; i < table_[index].getSize(); i++) {
            if (table_[index][i].getPID() < PID) {
                return i;
            }
        }
        return table_[index].getSize();
    } else {
        for (unsigned int i = 0; i < table_[index].getSize(); i++) {
            if (table_[index][i].getPID() == PID) {
                return i;
            }
        }
        return -1;
    }
}

// prints the table beautifully
// ------------------------------------------
// |   Index   |    PID    | Memory  Start  |
// |    0    | |      -1      |             |
// |    1    | |      -1      |             |
// |    2    | |      -1      |             |
// |    3    | |      -1      |             |
// |    4    | |     4        |      0      |
// |    5    | |      -1      |             |
// |    6    | |      -1      |             |
// |    7    | |     7        |      2      |
// ------------------------------------------
void SeparateChainedTable::printTable() {
    int maxLengthMemoryStart{14}, maxLengthPID{11}, maxLengthIndex{7};
    auto placeBetweenTheString = [](int maxLength, int valueToPlace) {
        std::string spaces = "";
        for (unsigned int i = 0; i < (maxLength - std::to_string(valueToPlace).length()) / 2; i++) {
            spaces += " ";
        }
        return spaces + std::to_string(valueToPlace) + spaces;
    };
    auto returnStringChainAtIndex = [&](int index) {
        std::string chain = "|";
        for (unsigned int i = 0; i < table_[index].getSize(); i++) {
            chain += placeBetweenTheString(maxLengthPID, table_[index][i].getPID()) + "|";
        }
        return chain;
    };
    auto printDashLine = []() { std::cout << "-----------------------------------------" << std::endl; };
    printDashLine();
    std::cout << "|   Index   |    PID    | Memory  Start |" << std::endl;
    for (unsigned int i = 0; i < table_size_; i++) {
        std::cout << "| " << placeBetweenTheString(maxLengthIndex, i) << " | "
                  << returnStringChainAtIndex(i) << placeBetweenTheString(maxLengthMemoryStart, table_[i].getSize()
                                                                                                ? table_[i][0].getMemoryStart()
                                                                                                : -1) << "|"
                  << std::endl;
    }
    printDashLine();
}