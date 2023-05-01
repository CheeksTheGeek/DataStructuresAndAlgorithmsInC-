#pragma once

#include "Process.hpp"

// Pure Abstract Class for  Page Table implemented as a hash table
class HashPageTable {
protected:
    int *physical_memory_;                    // physical memory
    unsigned int *page_activity_;             // stores the PIDs for the active pages in physical memory, 0 means the page is not in use
    unsigned int memory_counter_;             // keeps track of the number of active integers in physical memory
    unsigned int next_available_page_; // virtual pointer to the next available page in physical memory, moves to the next empty slot in page_activity_ when a page is removed
    unsigned int number_of_pages_in_memory_;  // keeps track of the number of active pages in physical memory
    unsigned int memory_size_;                // size of physical memory
    unsigned int page_size_;                  // size of each page
    unsigned int table_size_;                 // size of the hash table

public:
    // constructors and destructor
    HashPageTable();

    explicit HashPageTable(unsigned int memory_size,
                           unsigned int page_size); // explicit prevents implicit conversion of types
    virtual ~HashPageTable();

    // Hash Function
    inline unsigned int primaryHashFunction(unsigned int PID) const { return PID % table_size_; }

    // status boolean helper functions for dealing with physical memory
    inline bool isPhysicalMemoryFull() const { return memory_counter_ == memory_size_; }

    inline void
    writeValueToPhysicalMemory(unsigned int physical_address, int value) { physical_memory_[physical_address] = value; }

    inline bool isAddressInPageScope(unsigned int virtual_address) const { return virtual_address < page_size_; }

    // helper functions for dealing with physical memory
    void updateNextAvailablePage();

    int findPhysicalIndex(unsigned int PID);

    // status boolean functions
    virtual bool isTableFull() = 0;

    virtual bool isProcessInTable(unsigned int PID) = 0;

    // critical member functions
    virtual void insertProcess(unsigned int PID) = 0;

    virtual void writeValue(unsigned int PID, unsigned int virtual_address, int value) = 0;

    virtual int readValue(unsigned int PID, unsigned int virtual_address) = 0;

    virtual void
    deleteProcess(unsigned int PID) = 0; // this deletes the PID from the table but does not free the memory

    virtual void printTable() = 0;
};