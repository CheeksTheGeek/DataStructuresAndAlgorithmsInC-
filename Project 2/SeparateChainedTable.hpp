#pragma once

#include "HashPageTable.hpp"
#include "DynamicArrayForProcess.hpp"

// page table implemented as a ordered separate chained hash table
class SeparateChainedTable : public HashPageTable {
private:
    DynamicArrayForProcess *table_; // hash table : Array of DynamicArrayForProcess objects, meaning Array of Dynamic Array of Process objects

public:
    // constructors and destructor
    SeparateChainedTable();

    explicit SeparateChainedTable(unsigned int memory_size, unsigned int page_size);

    ~SeparateChainedTable();

    // double option finder function
    int getChainIndexForInsertionOrAccession(bool search_for_required_position_or_process, unsigned int PID);

    // status boolean functions for dealing with the chains inside the page table
    bool isChainFull(unsigned int indexInPageTable);

    bool isChainEmpty(unsigned int indexInPageTable);

    // status boolean functions for dealing with the page table
    inline bool isTableFull() override { return number_of_pages_in_memory_ == table_size_; }

    bool isProcessInTable(unsigned int PID) override;

    // critical member functions
    void insertProcess(unsigned int PID) override;

    void writeValue(unsigned int PID, unsigned int virtual_address, int value) override;

    int readValue(unsigned int PID, unsigned int virtual_address) override;

    void deleteProcess(unsigned int PID) override;

    // printer functions
    void printChain(unsigned int indexInPageTable);

    void printTable() override;
};