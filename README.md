# Data Structures and Algorithms in C++

This repository contains C++ implementations of common data structures and algorithms completed as part of the ECE 250 course at the University of Waterloo.

## Contents

### Project 1

Implementation of a simple calculator using a linked list data structure. The program consists of two major classes - `VarDataNode` and `CalcLinkedList`.

- `VarDataNode.cpp/.hpp`: Node class to store variable values
- `CalcLinkedList.cpp/.hpp`: Linked list class to store operations
- `main.cpp`: Calculator program driver

### Project 2  

Implementation of a hashed page table using separate chaining and open addressing. The page table stores `Process` objects and maps virtual page numbers to physical frame numbers.

- `HashPageTable.cpp/.hpp`: Page table class
- `SeparateChainedTable.cpp/.hpp`: Separate chaining implementation  
- `OpenAddressedTable.cpp/.hpp`: Open addressing implementation
- `Process.cpp/.hpp`: Process class 
- `main.cpp`: Driver to test page table

### Project 3

Implementation of a prefix tree (trie) to store and search for words. The `Trie` class contains nested `Node` and `Iterator` classes.

- `Trie.cpp/.hpp`: Trie class
- `main.cpp`: Driver to test trie functions

### Project 4

Implementation of Prim's algorithm to find minimum spanning tree of a graph. Uses a priority queue to store graph edges.

- `PowerGridGraph.cpp/.hpp`: Graph representation
- `EdgesPriorityQueue.cpp/.hpp`: Priority queue  
- `main.cpp`: Driver to test algorithm

## Building and Running

Each project includes a Makefile to compile the code. Use `make` to build and `./a.out` to run.

## Documentation

The LaTeX documentation provides additional details on the class structures and algorithms.

The UML diagrams were created with PlantUML and can be re-generated from the included `.puml` files.

## Testing 

The projects were developed using test cases provided by the course staff. See the individual project readmes for details on running tests.

## Author

Chaitanya Sharma
