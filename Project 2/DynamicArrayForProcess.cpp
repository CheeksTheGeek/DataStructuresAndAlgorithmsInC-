#include "DynamicArrayForProcess.hpp"
#include "Process.hpp"

// empty constructor
DynamicArrayForProcess::DynamicArrayForProcess() : dynamic_array_(nullptr), capacity_(0), size_(0) {}

// capacity constructor
DynamicArrayForProcess::DynamicArrayForProcess(int capacity) : dynamic_array_(new Process[capacity]{Process()}),
                                                               capacity_(capacity), size_(0) {}

// destructor
DynamicArrayForProcess::~DynamicArrayForProcess() {
    delete[] dynamic_array_;
    dynamic_array_ = nullptr;
}

// inserts the given value at the given index, by creating a new array and copying
// the elements from the old array to the new one unti the index is reached, then inserting the value,
// then copying the rest of the elements
void DynamicArrayForProcess::insert(unsigned int index, Process value) {
    Process *new_array = new Process[capacity_ + 1];
    for (unsigned int i = 0; i < index; i++) {
        new_array[i] = dynamic_array_[i];
    }
    new_array[index] = value;
    for (unsigned int i = index + 1; i < size_ + 1; i++) {
        new_array[i] = dynamic_array_[i - 1];
    }
    delete[] dynamic_array_;
    dynamic_array_ = new_array;
    capacity_++;
    size_++;
}

// removes the element at the given index
void DynamicArrayForProcess::erase(int index) {
    for (unsigned int i = index; i < size_ - 1; i++) {
        dynamic_array_[i] = dynamic_array_[i + 1];
    }
    size_--;
}