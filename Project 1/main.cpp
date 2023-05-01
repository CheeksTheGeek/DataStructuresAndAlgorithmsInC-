// Using Google's C++ style guide
// https://google.github.io/styleguide/cppguide.html

#include "CalcLinkedList.hpp"
#include <iostream>
#include <string>

void printStatus(bool status) {
    if(status){
        std::cout << "success" << std::endl;
    }
    else{
        std::cout << "failure" << std::endl;
    }
}

int main(){
    CalcLinkedList* calculator; // since we assume that all files start with a CRT command, we need to initialize a linked list here as the if conditions except the CRT command will fail without a linked list
    std::string input;
    while(std::cin >> input){
        if(input == "CRT"){
            int listSize;
            std::cin >> listSize;
            calculator = new CalcLinkedList(listSize); // initialize a linked list with given size
            printStatus(true);
        }
        else if(input == "DEF"){
            std::string var_name;
            double value;
            std::cin >> var_name >> value;
            if(!calculator->isFull() && !calculator->nodeExists(var_name)){
                calculator->addNewNode(var_name, value);
                printStatus(true);
            }
            else{
                printStatus(false);
            }
        }
        else if(input == "ADD"){
            std::string operand1, operand2, result;
            std::cin >> operand1 >> operand2 >> result;
            if(calculator->nodeExists(operand1) && calculator->nodeExists(operand2) && calculator->nodeExists(result)){
                calculator->addSubOp(operand1, operand2, result, true);
                printStatus(true);
            }
            else{
                printStatus(false);
            }

        }
        else if(input == "SUB"){
            std::string operand1, operand2, result;
            std::cin >> operand1 >> operand2 >> result;
            if(calculator->nodeExists(operand1) && calculator->nodeExists(operand2) && calculator->nodeExists(result)){
                calculator->addSubOp(operand1, operand2, result, false);
                printStatus(true);
            }
            else{
                printStatus(false);
            }
        }
        else if(input == "REM"){
            std::string var_name;
            std::cin >> var_name;
            if(calculator->nodeExists(var_name)){
                calculator->removeNode(var_name);
                printStatus(true);
            }
            else{
                printStatus(false);
            }
        }
        else if(input == "PRT"){
            std::string var_name;
            std::cin >> var_name;
            if(calculator->nodeExists(var_name)){
                calculator->printValue(var_name);
            }
            else{
                std::cout << "variable " << var_name << " not found" << std::endl;
            }
        }
        else if(input == "LST"){
            calculator->printLinkedList();
        }
        else if(input == "END"){
            delete calculator;
            break;
        }
    }
    return 0;
}