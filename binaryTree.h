#pragma once

#include <iostream>
#include <utility>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include <random>
#include <queue>

using std::cin, std::cout, std::vector, std::queue;

class  BinTree;

class Node{
    int key;

    Node *left;
    Node *right;
    Node *parent;

public:
    explicit Node(int k = 0, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr){
        key = k; left = l; right = r; parent = p;
    }

    [[nodiscard]] inline int getKey() const {
        return key;
    }
    friend class BinTree;
};

class  BinTree{
    Node* root = nullptr;
    // Построение идеально сбалансированного дерева, n количество вершни, p предок дерева.
    Node* tree(int n, Node *p); // число вершин, от какого узла дерево.

    void copy(Node *q, Node *p, int k); // Копирование дерева с вершиной q, p куда подсоединяем // k = 0 левый потомок, k = 1 правый потомок.
public:
    BinTree(){
        root = nullptr;
    }

    explicit BinTree(int n); // количество ключей, ключи случайные.
    BinTree(vector<int> &a, int n); // n - количество ключей, ключи из массива A
    BinTree(const BinTree& second);
    ~BinTree();

    BinTree& operator=(const BinTree& second);

    void add(int k, Node* p); // Добавление узла с ключом k, в дерево с корнем p;
    void del(Node* p);
    void delRoot();

    void treeTraversalLCR(Node* p, vector<int> &a, int &n) const;
    void treeTraversalCLR(Node* p, vector<int> &a, int &n) const;
    void treeTraversalRCL(Node* p, vector<int> &a, int &n) const;

    void BFS(Node* p, vector<int> &a, int &n) const;

    void printTree(int k, Node* p) const; // Вывод дерева горизонтально. k - отступ
    void printTreeVert(Node* p, int left_border, int right_border, int y) const; // y Отступ по вертикали.

    Node* findKey(Node* p, int k) const;
    Node* findMax(Node* p) const;
    Node* findMin(Node* p) const;
    int findHeight(Node* p) const;
    int countVertex(Node* p) const;

    [[nodiscard]] inline Node* getRoot() const {return root;}
    void clearTree(); // уничтожает всё кроме корня.
};
