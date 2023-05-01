#include <stdexcept>
#include "OpenAddressedTable.hpp"
#include <iostream>

// empty constructor
OpenAddressedTable::OpenAddressedTable() : HashPageTable(), table_(nullptr) {}

// constructor with memory size and page size
OpenAddressedTable::OpenAddressedTable(unsigned int memory_size, unsigned int page_size) : HashPageTable(memory_size,page_size),table_(new Process[memory_size / page_size]{Process(EMPTY_PID,NULL_MEMORY_START)}) {}
// OpenAddressedTable::OpenAddressedTable(unsigned int memory_size, unsigned int page_size) : HashPageTable(memory_size, page_size), table_(new Process[memory_size / page_size]{Process(0,0)}){}

// destructor
OpenAddressedTable::~OpenAddressedTable() {
    delete[] table_;
    table_ = nullptr;
}

// secondary hash function =
unsigned int OpenAddressedTable::secondaryHashFunctionWithCounter(unsigned int PID, unsigned int counter) {
    unsigned int h2{PID / table_size_};
    if (h2 % 2 == 0) {
        h2++;
    }
    return counter * h2;
}

// search_for_insertion_or_accession = false for getting the index of the first empty slot, i.e. insertion
// search_for_insertion_or_accession = true the index of the process with PID, i.e. accession
int OpenAddressedTable::getIndexForInsertionOrAccession(bool search_for_insertion_or_accession, unsigned int PID) {
    if (PID == UINT_MAX) {
        throw std::invalid_argument("Too large of a value");
    }
    auto index = [&](unsigned int counter) {
        return (primaryHashFunction(PID) + secondaryHashFunctionWithCounter(PID, counter)) % table_size_;
    };
    unsigned int non_empty_counter{0};
    unsigned int i{0};
    // IMPLEMENT LAZY DELETION IN WHERE TOMBSTONES ARE TREATED AS FILLED SLOTS IN ACCESSION AND TOMBSTONES ARE TREATED AS EMPTY SLOTS IN INSERTION
    // search or insert only on a hash path, where first check h1 + 0*h2  then h1 + 1*h2, then h1 + 2*h2, etc.
    // accession i.e. search for PID:
    // In this do not stop until you find the PID or an empty slot, i.e. a slot with EMPTY_PID, and treat TOMBSTONE_PID as filled slots
    // if you find the PID return the index
    // if you find an empty slot return -1
    // insertion i.e. search for EMPTY_PID:
    // In this do not stop until you find the EMPTY_PID or a TOMBSTONE_PID, i.e. a slot with PID
    // if you find the EMPTY_PID OR TOMBSTONE_PID return the index
    // IMPLEMENTATION WITH LAZY DELETION WITH NON EMPTY COUNTER COMPARISON
    while (true) {
        if (search_for_insertion_or_accession) {
            if (table_[index(i)].getPID() == PID) {
                return index(i);
            } else if (table_[index(i)].getPID() != EMPTY_PID && table_[index(i)].getPID() != TOMBSTONE_PID) {
                non_empty_counter++;
            }
        } else {
            if (table_[index(i)].getPID() == EMPTY_PID || table_[index(i)].getPID() == TOMBSTONE_PID) {
                return index(i);
            }
        }
        if (non_empty_counter == number_of_pages_in_memory_) {
            return -1;
        }
        i++;
    }

    // IMPLEMENTATION WITH NON_EMPTY_COUNTER
    //     SEARCH FOR ACCESSING
    // , when you see a nonempty spot increase a temp_counter_of_non_empty, and if it reaches the value of number_of_pages_in_memory_, then stop searching and return -1 since there wouldn't be any more possibility of finding the process, otherwise return the index found
    // Insert Search:
    // Look for an empty spot on the hash path i.e. run a while loop until index(i) PID is empty. Believe that it has been checked already if the table is not full, hence there is a spot
    // Talk about using lazy deletions vs preprocessor definitions
    // unsigned int non_empty_counter{0};
    // unsigned int i{0};
    // while ( true )
    // {
    //     if (search_for_insertion_or_accession)
    //     {
    //         if (table_[index(i)].getPID() == PID)
    //         {
    //             return index(i);
    //         }
    //         else if (table_[index(i)].getPID() != 0)
    //         {
    //             non_empty_counter++;
    //         }
    //     }
    //     else
    //     {
    //         if (table_[index(i)].getPID() == 0)
    //         {
    //             return index(i);
    //         }
    //     }
    //     if (non_empty_counter == number_of_pages_in_memory_)
    //     {
    //         return -1;
    //     }
    //     i++;
    // }
    // SAFE FOR NUMBERS NEAR UINT MAX
}

// returns the inequality of the double option finder function to -1
// since the double option finder function returns -1 if the process is not in the chain
bool OpenAddressedTable::isProcessInTable(unsigned int PID) {
    return getIndexForInsertionOrAccession(true, PID) != -1;
}

// inserts the process using the double option finder function
void OpenAddressedTable::insertProcess(unsigned int PID) {
    table_[getIndexForInsertionOrAccession(false, PID)] = Process(PID, next_available_page_ * page_size_);
    page_activity_[next_available_page_] = PID;
    updateNextAvailablePage();
    number_of_pages_in_memory_++;
}

// writes the value to the physical memory at the memory start address of
// the process with PID after adding the offset of the virtual address
void OpenAddressedTable::writeValue(unsigned int PID, unsigned int virtual_address, int value) {
    physical_memory_[table_[getIndexForInsertionOrAccession(true, PID)].getMemoryStart() + virtual_address] = value;
}

int OpenAddressedTable::readValue(unsigned int PID, unsigned int virtual_address) {
    return physical_memory_[table_[getIndexForInsertionOrAccession(true, PID)].getMemoryStart() + virtual_address];
}

// this deletes the PID from the table but does not free the physical memory
void OpenAddressedTable::deleteProcess(unsigned int PID) {
    table_[getIndexForInsertionOrAccession(true, PID)] = Process(TOMBSTONE_PID, NULL_MEMORY_START);
    // table_[getIndexForInsertionOrAccession(true, PID)] = Process(0, 0);
    page_activity_[findPhysicalIndex(PID)] = 0;
    updateNextAvailablePage();
    number_of_pages_in_memory_--;
}

// prints the table data beautifully
// ------------------------------------
// | Index |    PID    | Memory Start |
// | 0     | 231       | 0            |
// | 1     | 546       | 16            |
// | 2     | 356       | 8            |
// ------------------------------------
void OpenAddressedTable::printTable() {
    auto placeBetweenTheString = [](int maxLength, int valueToPlace) {
        std::string spaces = "";
        for (unsigned int i = 0; i < (maxLength - std::to_string(valueToPlace).length()) / 2; i++) {
            spaces += " ";
        }
        return spaces + std::to_string(valueToPlace) + spaces;
    };
    auto printDashLine = []() { std::cout << "-----------------------------------------" << std::endl; };
    printDashLine();
    int maxLengthMemoryStart{14}, maxLengthPID{11}, maxLengthIndex{7};
    std::cout << "|   Index   |    PID    | Memory  Start |" << std::endl;
    for (unsigned int i = 0; i < table_size_; i++) {
        std::cout << "| " << placeBetweenTheString(maxLengthIndex, i) << " | "
                  << placeBetweenTheString(maxLengthPID, table_[i].getPID()) << " | "
                  << placeBetweenTheString(maxLengthMemoryStart, table_[i].getMemoryStart()) << " |"
                  << std::endl;
    }
    printDashLine();
}
