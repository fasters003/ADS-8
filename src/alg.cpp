// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string word = "";
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z') {
            word += static_cast<char>(ch + ('a' - 'A'));
        } else if (ch >= 'a' && ch <= 'z') {
            word += ch;
        } else {
            if (!word.empty()) {
                tree.add(word);
                word = "";
            }
        }
    }
    if (!word.empty()) tree.add(word);
    file.close();
}

void collect(BST<std::string>::Node* node,
             std::vector<std::pair<std::string, int>>* data) {
    if (!node) return;
    collect(node->left, data);
    data->push_back({node->value, node->count});
    collect(node->right, data);
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqData;
    collect(tree.getRoot(), &freqData);

    std::sort(freqData.begin(), freqData.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });

    std::ofstream outFile("result/freq.txt");
    for (const auto& entry : freqData) {
        if (outFile.is_open()) {
            outFile << entry.first << " " << entry.second << "\n";
        }
    }
    outFile.close();
}
