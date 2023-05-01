#include "trie.hpp"

#include <fstream>
#include <iostream>

#include "illegal_exception.hpp"

void Trie::load(std::string &filename) {
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        insertWord(word);
    }
}

Trie::~Trie() {
    delete root_;
    root_ = nullptr;
}
Trie::NASIS Trie::search(std::string &word) const {
    Node *current_node = root_;
    int x = 0;
    for (auto i: word) {
        if (current_node->children_[i - 'A'] == nullptr) {
            return NASIS(current_node, x);
        }
        current_node = current_node->children_[i - 'A'];
        x++;
    }
    return NASIS(current_node, x);
}
bool Trie::insertWord(std::string &word) {
        for (auto i : word) {
        if (i < 'A' || i > 'Z') {
            throw IllegalException();
        }
    }
    NASIS nasi_pair = search(word);
    Node *last_found_valid_node = nasi_pair.last_active_node_;
    unsigned long x = nasi_pair.string_index_;
    if (x == word.length()) {
        if (last_found_valid_node->is_word_here_) {
            return false;
        }
        last_found_valid_node->is_word_here_ = true;
        num_of_words_++;
        return true;
    }
    std::string word_not_in_trie = word.substr(x);
    Node *current_node = last_found_valid_node;
    for (auto i : word_not_in_trie) {
        current_node->children_[i - 'A'] = new Node(i, current_node, false, current_node->lineage_ + i);
        current_node = current_node->children_[i - 'A'];
    }
    current_node->is_word_here_ = true;
    num_of_words_++;
    return true;
}

bool Trie::deleteWord(std::string &word) {
    for (auto i : word) {
        if (i < 'A' || i > 'Z') {
            throw IllegalException();
        }
    }
    NASIS nasi_pair = search(word);  // gives me r if or exists in trie but orange doesnt
    Node *last_found_valid_node = nasi_pair.last_active_node_;
    // Node *last_important_node = nasi_pair.last_important_node_;
    unsigned long x = nasi_pair.string_index_;
    // case 1: the sequence doesnt exist or the last node isn't a word enabled node
    if (x < word.length() || !last_found_valid_node->is_word_here_) {
        return false;
    }

    last_found_valid_node->is_word_here_ = false;
    num_of_words_--;
    // case 2: checks if all children are null
    for (auto i : last_found_valid_node->children_) {
        if (i != nullptr) {
            return true;
        }
    }

    std::string new_word{word};
    Node *current_node = last_found_valid_node;
    while (current_node != root_ && !current_node->is_word_here_) {
        current_node = current_node->parent_;
        delete current_node->children_[new_word.back() - 'A'];
        current_node->children_[new_word.back() - 'A'] = nullptr;
        new_word.pop_back();
        for (auto i : current_node->children_) {
            if (i != nullptr) {
                return true;
            }
        }
    }    
    return true;
}

int Trie::countSuffixes(std::string &word) const {
    Node *current_node = root_;
    for (char i : word) {
        if (i < 'A' || i > 'Z') {
            throw IllegalException();
        }
        if (current_node->children_[i - 'A'] == nullptr) {
            return 0;
        }
        current_node = current_node->children_[i - 'A'];
    }
    return countWordsBelowThisNode(current_node);
}

int Trie::countWordsBelowThisNode(Node *node) const {
    int count = 0;
    if (node->is_word_here_) {
        count++;
    }
    for (auto &i : node->children_) {
        if (i != nullptr) {
            count += countWordsBelowThisNode(i);
        }
    }
    return count;
}

void Trie::printTrie() const {
    // prints the trie
    printTrieBelowThisNode(root_);
    if (num_of_words_ != 0) {
        std::cout << std::endl;
    }
}

void Trie::printTrieBelowThisNode(Node *node) const {
    if (node->is_word_here_) {
        std::cout << node->lineage_ << " ";
    }
    for (auto &i : node->children_) {
        if (i != nullptr) {
            printTrieBelowThisNode(i);
        }
    }
}

bool Trie::checkSpelling(std::string &word) const {
    if (root_->children_[word[0] - 'A'] == nullptr) {
        return false;
    }
    NASIS nasi_pair = search(word);
    Node *last_found_valid_node = nasi_pair.last_active_node_;

    unsigned long x = nasi_pair.string_index_;
    if (last_found_valid_node->is_word_here_ && x == word.length()) {
        return true;
    }
    auto num_child = [](Node *node) {
        int count = 0;
        for (auto i : node->children_) {
            if (i != nullptr) {
                count++;
            }
        }
        return count;
    };
    if (num_child(last_found_valid_node) > 1) {
        possibleWordsBelow(last_found_valid_node);
        return false;
    }
    while (last_found_valid_node != root_) {
        if (num_child(last_found_valid_node) > 0 || last_found_valid_node->is_word_here_) {
            possibleWordsBelow(last_found_valid_node);
            return false;
        }
        last_found_valid_node = last_found_valid_node->parent_;
    }
    return false;
}

void Trie::possibleWordsBelow(Node *node) const {
    if (node->is_word_here_) {
        std::cout << node->lineage_ << " ";
    }
    for (auto &i : node->children_) {
        if (i != nullptr) {
            printTrieBelowThisNode(i);
        }
    }
}

void Trie::clear() {
    delete root_;
    root_ = new Node();
    num_of_words_ = 0;
}
