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
    // ���������� �������� ����������������� ������, n ���������� ������, p ������ ������.
    Node* tree(int n, Node *p); // ����� ������, �� ������ ���� ������.

    void copy(Node *q, Node *p, int k); // ����������� ������ � �������� q, p ���� ������������ // k = 0 ����� �������, k = 1 ������ �������.
public:
    BinTree(){
        root = nullptr;
    }

    explicit BinTree(int n); // ���������� ������, ����� ���������.
    BinTree(vector<int> &a, int n); // n - ���������� ������, ����� �� ������� A
    BinTree(const BinTree& second);
    ~BinTree();

    BinTree& operator=(const BinTree& second);

    void add(int k, Node* p); // ���������� ���� � ������ k, � ������ � ������ p;
    void del(Node* p);
    void delRoot();

    void treeTraversalLCR(Node* p, vector<int> &a, int &n) const;
    void treeTraversalCLR(Node* p, vector<int> &a, int &n) const;
    void treeTraversalRCL(Node* p, vector<int> &a, int &n) const;

    void BFS(Node* p, vector<int> &a, int &n) const;

    void printTree(int k, Node* p) const; // ����� ������ �������������. k - ������
    void printTreeVert(Node* p, int left_border, int right_border, int y) const; // y ������ �� ���������.

    Node* findKey(Node* p, int k) const;
    Node* findMax(Node* p) const;
    Node* findMin(Node* p) const;
    int findHeight(Node* p) const;
    int countVertex(Node* p) const;

    [[nodiscard]] inline Node* getRoot() const {return root;}
    void clearTree(); // ���������� �� ����� �����.
};
