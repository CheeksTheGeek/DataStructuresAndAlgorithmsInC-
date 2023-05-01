#include "HashPageTable.hpp"
#include <iostream>

// empty constructor
HashPageTable::HashPageTable() : physical_memory_(nullptr), page_activity_(nullptr), memory_counter_(0),
                                 next_available_page_(0), number_of_pages_in_memory_(0), memory_size_(0), page_size_(0),
                                 table_size_(0) {}

// constructor
HashPageTable::HashPageTable(unsigned int memory_size, unsigned int page_size) : physical_memory_(
        new int[memory_size]{0}), page_activity_(new unsigned int[memory_size / page_size]{0}), memory_counter_(0),
                                                                                 next_available_page_(0),
                                                                                 number_of_pages_in_memory_(0),
                                                                                 memory_size_(memory_size),
                                                                                 page_size_(page_size),
                                                                                 table_size_(memory_size / page_size) {}

// destructor
HashPageTable::~HashPageTable() {
    delete[] physical_memory_, delete[] page_activity_;
    physical_memory_ = nullptr;
    page_activity_ = nullptr;
}

// find the physical index of the page with PID
int HashPageTable::findPhysicalIndex(unsigned int PID) {
    for (unsigned int i = 0; i < table_size_; i++) {
        if (page_activity_[i] == PID) {
            return i;
        }
    }
    return -1;
}

// update the next available page number after a page is removed to the next empty slot in the page_PIDs_ array
void HashPageTable::updateNextAvailablePage() {
    for (unsigned int i = 0; i < table_size_; i++) {
        if (page_activity_[i] == 0) {
            next_available_page_ = i;
            return;
        }
    }
}
