#pragma once
#include <string>

class  VarDataNode{
    public :
        VarDataNode(std::string var_name, double value);
        ~VarDataNode() = default;
        void  setValue(double value);
        std::string  getVarName() const ;
        double getValue() const;
        void  setNext(VarDataNode* next);
        VarDataNode* getNext() const;
    private :
        std::string  var_name_;
        double value_;
        VarDataNode* p_next_node_;
};