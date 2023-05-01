#pragma once

#include <climits>

#define EMPTY_PID 0
#define NULL_MEMORY_START UINT_MAX
#define TOMBSTONE_PID UINT_MAX

class Process {
private:
    unsigned int PID_;          // Process Identifier (PID)
    unsigned int memory_start_; // the starting index of the page given to this process in the physical memory

public:
    // constructors and destructor
    // inline Process(): PID_(0), memory_start_(0){};
    inline Process() : PID_(EMPTY_PID),
                       memory_start_(NULL_MEMORY_START) {};                              // default constructor
    inline Process(unsigned int PID, int memory_start) : PID_(PID),
                                                         memory_start_(memory_start) {}; // value-init constructor
    ~Process() = default;                                                                          // default destructor

    // getters and setters
    inline unsigned int getPID() const { return PID_; };

    inline void setPID(unsigned int PID) { PID_ = PID; };

    inline unsigned int getMemoryStart() const { return memory_start_; };

    inline void setMemoryStart(int memory_start) { memory_start_ = memory_start; };
};