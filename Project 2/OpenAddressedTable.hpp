#pragma once

#include "HashPageTable.hpp"

// page table implemented  as a open addressed double hashed hash table
class OpenAddressedTable : public HashPageTable {
private:
    Process *table_; // hash table : Array of Process objects

public:
    // constructors and destructor
    OpenAddressedTable();

    explicit OpenAddressedTable(unsigned int memory_size, unsigned int page_size);

    ~OpenAddressedTable();

    // Secondary Hash Function used in conjunction with the primary hash function
    unsigned int secondaryHashFunctionWithCounter(unsigned int PID, unsigned int counter);

    // double option finder function
    int getIndexForInsertionOrAccession(bool search_for_empty_slot_or_process, unsigned int PID);

    // status boolean functions for dealing with the page table
    inline bool isTableFull() override { return number_of_pages_in_memory_ == table_size_; }

    bool isProcessInTable(unsigned int PID) override;

    // critical member functions
    void insertProcess(unsigned int PID) override;

    void writeValue(unsigned int PID, unsigned int virtual_address, int value) override;

    int readValue(unsigned int PID, unsigned int virtual_address) override;

    void deleteProcess(unsigned int PID) override;

    // printer function
    void printTable() override;
};