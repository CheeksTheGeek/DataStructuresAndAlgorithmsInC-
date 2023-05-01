#pragma once

#include "Process.hpp"

// dynamic array for processes, alternative to vector
class DynamicArrayForProcess {
private:
    Process *dynamic_array_; // pointer to the dynamically allocated array
    unsigned int capacity_;  // number of elements that can be stored in the array, does not require a getter
    unsigned int size_;      // number of active elements in the array
public:
    // constructors and destructor
    DynamicArrayForProcess();

    explicit DynamicArrayForProcess(int capacity);

    ~DynamicArrayForProcess();

    // operator overloading for []
    inline Process &operator[](int index) { return dynamic_array_[index]; };

    // getter for element at index
    inline Process &at(int index) { return dynamic_array_[index]; }

    // getter for size
    inline unsigned int getSize() const { return size_; }

    // critical member functions
    void insert(unsigned int index, Process value);

    void erase(int index);
};