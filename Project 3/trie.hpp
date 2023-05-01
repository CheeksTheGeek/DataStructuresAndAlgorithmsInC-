#pragma once

#include <string>
#include "illegal_exception.hpp"

class Trie {
private:
    class Node {
    public:
// include check for illegal characters since the value can only be between A and Z
        Node *parent_;
        Node *children_[26] = {NULL};
        bool is_word_here_;
        char value_; // value_ is the character between A and Z that the current node represents
        std::string lineage_; // lineage_ is the string appropriate child of root to the current node, if the current node is terminal then lineage_ is a full meaningful word. NOTE: DOES NOT INCLUDE ROOT SINCE ROOT HAS DEFAULT VALUE '@'

        inline Node() : parent_(nullptr), is_word_here_(false), value_('@'){
        }

        inline Node(char value, Node *parent, bool is_terminal, std::string lineage) : parent_(parent),
                                                                                       is_word_here_(is_terminal),
                                                                                       value_(value),
                                                                                       lineage_(std::move(lineage)){
            if (value < 'A' || value > 'Z') {
                throw IllegalException();
            }
        }

        ~Node() {
            for (auto &i: children_) {
                if (i != nullptr) {
                    delete i;
                    i = nullptr;
                }
            }
        }
    } *root_;

    int num_of_words_;

    class NASIS { // Nodes(Last Important and Last Active ) And String Index Set
    public:
        Node* last_active_node_;
        Node* last_important_node_;
        unsigned long string_index_;
        std::string original_word_;
        inline NASIS() : last_active_node_(nullptr), last_important_node_(nullptr), string_index_(0), original_word_("") {}
        inline NASIS(Node *node, int string_index) : last_active_node_(node), string_index_(string_index) {}
    };

    NASIS search(std::string &word) const;
public:
    inline Trie() : root_(new Node), num_of_words_(0) {}

    ~Trie(); // destructor

    void load(std::string &filename);

    bool insertWord(std::string &word);

    bool deleteWord(std::string &word);

    void printTrie() const;

    void printTrieBelowThisNode(Node *node) const;

    bool checkSpelling(std::string &word) const;

    void possibleWordsBelow(Node *last_valid_node) const;

    int countSuffixes(std::string &word) const;

    int countWordsBelowThisNode(Node *node) const;

    inline int getNumOfWords() const { return num_of_words_; }

    inline bool isEmpty() const { return num_of_words_ == 0; }

    void clear();
};