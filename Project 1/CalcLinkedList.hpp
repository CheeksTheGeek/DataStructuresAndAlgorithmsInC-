#pragma once
#include "VarDataNode.hpp"
#include <string>

class CalcLinkedList{
    private:
        VarDataNode* p_head_;
        unsigned int number_of_nodes_;
        unsigned int list_size_;
        void redefineVariable(std::string var_name, double new_value);
    public:
        CalcLinkedList();
        CalcLinkedList(double size);
        ~CalcLinkedList();
        bool isFull();
        VarDataNode* findNodeOrBeforeThis(std::string var_name, bool this_or_before); // true = this, false = before this
        bool nodeExists(std::string var_name);
        void addNewNode(std::string var_name, double value);
        void removeNode(std::string var_name);
        void printValue(std::string var_name);
        void addSubOp(std::string first_var_name, std::string second_var_name, std::string result_var_name, bool add_or_sub); // true = add, false = sub
        void printLinkedList(); 
};