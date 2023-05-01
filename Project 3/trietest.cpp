#include <iostream>
#include "trie.hpp"
#include "illegal_exception.hpp"

int main() {
    Trie *trie = new Trie();
    std::string command;
    std::string filename = "corpus.txt";
    while (std::cin >> command) {
        if (command == "load") {
            trie->load(filename);
            std::cout << "success" << std::endl;
        } else if (command == "i") {
            std::string word;
            std::cin >> word;
            try {
                std::string status = trie->insertWord(word) ? "success" : "failure";
                std::cout << status << std::endl;
            }
            catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "c") { // count of words that are prefixed by the given word
            std::string prefix;
            std::cin >> prefix;
            try {
                unsigned int count = trie->countSuffixes(prefix);
                if (count == 0) {
                    std::cout << "not found" << std::endl;
                } else {
                    std::cout << "count is " << count << std::endl;
                }
            }
            catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "e") { // erase
            std::string word;
            std::cin >> word;
            try {
                std::string status = trie->deleteWord(word) ? "success" : "failure";
                std::cout << status << std::endl;
            }
            catch (IllegalException &e) {
                std::cout << e.what() << std::endl;
            }
        } else if (command == "p") { // print all
            trie->printTrie();
        } else if (command == "spellcheck") {
            std::string word;
            std::cin >> word;
            // try {
            if (trie->checkSpelling(word)) {
                std::cout << "correct";
            }
            std::cout << std::endl;
            // }
            // catch (IllegalException &e) {
            //     std::cout << e.what() << std::endl;
            // }
        } else if (command == "empty") {
            std::string status = trie->isEmpty() ? "1" : "0";
            std::cout << "empty " << status << std::endl;
        } else if (command == "clear") {
            trie->clear();
            std::cout << "success" << std::endl;
        } else if (command == "size") {
            std::cout << "number of words is " << trie->getNumOfWords() << std::endl;
        } else if (command == "exit") {
            break;
        } else {
            continue;
        }
    }
    delete trie;
    return 0;
}