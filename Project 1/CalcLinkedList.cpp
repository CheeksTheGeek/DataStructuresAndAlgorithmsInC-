#include "CalcLinkedList.hpp"
#include <iostream>

// DEFAULT CONSTRUCTOR
CalcLinkedList::CalcLinkedList():
p_head_(nullptr), number_of_nodes_(0), list_size_(0){}

// CONSTRUCTOR WITH SIZE
CalcLinkedList::CalcLinkedList(double size):
p_head_(nullptr), number_of_nodes_(0), list_size_(size){}

// DESTRUCTOR
CalcLinkedList::~CalcLinkedList(){
    VarDataNode* temp = p_head_;
    while(temp != nullptr){
        VarDataNode* next = temp->getNext();
        delete temp;
        temp = next;
    }
}

// COMPARATOR FOR SIZE OF LIST AND NUMBER OF NODES
bool CalcLinkedList::isFull(){
    return number_of_nodes_ == list_size_;
}

// NODE SEARCH OR SEARCH FOR NODE BEFORE THE NODE REQUESTED
VarDataNode* CalcLinkedList::findNodeOrBeforeThis(std::string var_name, bool true_is_this_false_is_before_this){ // true = this, false = before
    VarDataNode* temp = p_head_;
    VarDataNode* prev = nullptr;
    while(temp != nullptr){
        if(temp->getVarName() == var_name){
            if(true_is_this_false_is_before_this){
                return temp;
            }
            else{
                return prev;
            }
        }
        prev = temp;
        temp = temp->getNext();
    }
    return nullptr;
}

// CHECK FOR NODE EXISTENCE
bool CalcLinkedList::nodeExists(std::string var_name){
    return findNodeOrBeforeThis(var_name, true) != nullptr;
}

// REDEFINITION OF NODE VALUE
void CalcLinkedList::redefineVariable(std::string var_name, double value){
    findNodeOrBeforeThis(var_name, true)->setValue(value);
}

// NEW NODE CREATION AND INSERTION AT HEAD SIDE
void CalcLinkedList::addNewNode(std::string var_name, double value){
    if(isFull()){
        return;
    }
    if(nodeExists(var_name)){
        return;
    }
    VarDataNode* new_node = new VarDataNode(var_name, value);
    if(p_head_ == nullptr){
        p_head_ = new_node;
    }
    else{
        VarDataNode* temp = p_head_;
        new_node->setNext(temp);
        p_head_ = new_node;
    }
    number_of_nodes_++;
}

// NODE REMOVAL, RECONNECTION OF LIST AND DELETION OF NODE
void CalcLinkedList::removeNode(std::string var_name){
    VarDataNode* temp = findNodeOrBeforeThis(var_name, true);
    if(findNodeOrBeforeThis(var_name, false) == nullptr){
        p_head_ = temp->getNext();
    }
    else{
    findNodeOrBeforeThis(var_name, false)->setNext(findNodeOrBeforeThis(var_name, true)->getNext());
    }
    number_of_nodes_--;
    delete temp;
}

// VARIABLE VALUE OUTPUT TO CONSOLE
void CalcLinkedList::printValue(std::string var_name){
    std::cout << findNodeOrBeforeThis(var_name, true)->getValue() << std::endl;
}

// ADDITION AND SUBTRACTION OF NODES AND REDEFINITION OF RESULT NODE VALUE
void CalcLinkedList::addSubOp(std::string first_var_name, std::string second_var_name, std::string result_var_name, bool add_or_sub){
    VarDataNode* first_node = findNodeOrBeforeThis(first_var_name, true);
    VarDataNode* second_node = findNodeOrBeforeThis(second_var_name, true);
    if(add_or_sub){
        redefineVariable(result_var_name, first_node->getValue() + second_node->getValue());
    }
    else{
        redefineVariable(result_var_name, first_node->getValue() - second_node->getValue());
    }
}



// PRINT THE LINKED LIST IN A BEATIFUL MANNER
// ----------------------------------     ----------------------------------
// |       x       |                |     |       y       |                |
// |               | 0x7ffedc000a00 | - > |               | 0x7ffedc000a50 | - > EMPTINESS
// |       5       |                |     |       10      |                |
// ----------------------------------     ----------------------------------
void CalcLinkedList::printLinkedList(){
    VarDataNode* temp = p_head_;
    while(temp != nullptr){
        std::cout<<"----------------------------------     ";
        temp = temp->getNext();
    }
    std::cout<<std::endl;
    temp = p_head_;
    while(temp != nullptr){
        std::cout<<"|       "<<temp->getVarName()<<"       |                |     ";
        temp = temp->getNext();
    }
    std::cout<<std::endl;
    temp = p_head_;
    while(temp != nullptr){
        std::cout<<"|               | "<<temp<<" | - > ";
        temp = temp->getNext();
    }   
    std::cout<< "EMPTINESS"; // end of list i.e. NULL
    std::cout<<std::endl;
    temp = p_head_;
    while(temp != nullptr){
        std::cout<<"|       "<<temp->getValue()<<"       |                |     ";
        temp = temp->getNext();
    }
    std::cout<<std::endl;
    temp = p_head_;

    while(temp != nullptr){
        std::cout<<"----------------------------------     ";
        temp = temp->getNext();
    }
    std::cout<<std::endl;
}