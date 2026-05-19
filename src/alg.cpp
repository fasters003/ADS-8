// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    std::string word;
    int ch;
    // Считываем посимвольно до конца файла, строго фильтруя латиницу
    while ((ch = file.get()) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            word += static_cast<char>(ch);
        } else if (ch >= 'A' && ch <= 'Z') {
            word += static_cast<char>(ch - 'A' + 'a'); // перевод в нижний регистр
        } else if (!word.empty()) {
            tree.add(word);
            word.clear();
        }
    }
    if (!word.empty()) tree.add(word);
    file.close();
}

void collect(BST<std::string>::Node* node, 
             std::vector<std::pair<std::string, int>>& data) {
    if (!node) return;
    collect(node->left, data);
    data.emplace_back(node->value, node->count);
    collect(node->right, data);
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqData;
    collect(tree.getRoot(), freqData);

    // Сортировка по убыванию частоты. Если частота одинакова — по алфавиту
    std::sort(freqData.begin(), freqData.end(), [](const auto& a, const auto& b) {
        return a.second != b.second ? a.second > b.second : a.first < b.first;
    });

    std::ofstream outFile("result/freq.txt");
    for (const auto& entry : freqData) {
        // Вывод на экран (добавлено)
        std::cout << entry.first << " " << entry.second << "\n";
        // Запись в файл
        if (outFile.is_open()) {
            outFile << entry.first << " " << entry.second << "\n";
        }
    }
    if (outFile.is_open()) {
        outFile.close();
    }
}
