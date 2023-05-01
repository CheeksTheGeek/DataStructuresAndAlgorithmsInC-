#include "VarDataNode.hpp"
#include <string>

VarDataNode::VarDataNode(std::string var_name, double value):
var_name_(var_name), value_(value), p_next_node_(nullptr){}

std::string VarDataNode::getVarName() const{
    return var_name_;
}
void VarDataNode::setValue(double value){
    value_ = value;
}
double VarDataNode::getValue() const {
    return value_;
}
void VarDataNode::setNext(VarDataNode* next){
    p_next_node_ = next;
}
VarDataNode* VarDataNode::getNext() const{
    return p_next_node_;
}