#include "binaryTree.h"

Node* BinTree::tree(int n, Node *p){
    if(n == 0) return nullptr;
    Node* q = new Node(rand() % 50);
    int nL = (n - 1) / 2, nR = n - 1 - nL;
    q -> left = tree(nL, q); q -> right = tree(nR, q);
    q -> parent = p;
    return q;
}

BinTree::BinTree(int n){
    root = tree(n, nullptr);
}

BinTree::BinTree(vector<int> &a, int n) {
    for(const int& x : a) add(x, root);
}

void BinTree::copy(Node *q, Node *p, int k){
    if(q == nullptr) return;

    Node *copy_q = new Node(q -> key);
    copy_q -> parent = p;
    if(k == 0) p -> left = copy_q;
    else p -> right = copy_q;
    copy(q -> left, copy_q, 0); copy(q -> right, copy_q, 1);
}

BinTree::BinTree(const BinTree& second){
    if(second.root == nullptr) root = nullptr;
    else{
        root = new Node(second.root -> key);
        copy(second.root -> left, root, 0);
        copy(second.root -> right, root, 1);
    }
}
void BinTree::printTree(int k, Node* p) const{
    if(!p) return;
    printTree(k + 5, p -> right);
    for(int i = 0;i < k;i++) cout << " ";
    cout << p -> key << "\n";
    printTree(k + 5, p -> left);
}

/*
    Замечание: 1)В main долнжны быть следующие переменные HANDLE hstOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    2) вызов функции делается так:
    2.1) Получаем положение курсора GetConsoleScreenBufferInfo(hsout, &csbi);
    COORD cursor = csbi.dwCursorPosition;
    T1.printTreeVert(T1.getRoot(), 0, 60,cursor.Y + 2); puts(" ");
*/

void BinTree::printTreeVert(Node* p, int left_border, int right_border, int y) const{
    if(!p) return;
    int x = (left_border + right_border) / 2;
    HANDLE hstOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD curpos = {(SHORT) x, (SHORT) y};
    cout << p -> key;
    printTreeVert(p -> left, left_border, x, y + 2);
    printTreeVert(p -> right, x, right_border, y + 2);
}

void BinTree::add(int k, Node *p) {
    if(p == nullptr) {root = new Node(k);return;}

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1000);

    int t = dist(mt) % 2;
    if(t == 1){
        if(p -> right) add(k, p -> right);
        else {
            Node* q = new Node(k);
            p -> right = q;
            q -> parent = p;
        }
    }else{
        if(p -> left) add(k, p ->left);
        else {
            Node* q = new Node(k);
            p -> left = q;
            q -> parent = p;
        }
    }
}

 void BinTree::treeTraversalLCR(Node* p, vector<int> &a, int &n) const{
    if(p -> left != nullptr) treeTraversalLCR(p -> left, a, ++n);
    a.emplace_back(p -> getKey());
    if(p -> right != nullptr) treeTraversalLCR(p -> right, a, ++n);
 }

 void BinTree::treeTraversalCLR(Node* p, vector<int> &a, int &n) const{
    a.emplace_back(p -> getKey());
    if(p -> left != nullptr) treeTraversalCLR(p -> left, a, ++n);
    if(p -> right != nullptr) treeTraversalCLR(p -> right, a, ++n);
 }

 void BinTree::treeTraversalRCL(Node* p, vector<int> &a, int &n) const{
    if(p -> right != nullptr) treeTraversalRCL(p -> right, a, ++n);
    a.emplace_back(p -> getKey());
    if(p -> left != nullptr) treeTraversalRCL(p -> left, a, ++n);
 }

 void BinTree::BFS(Node* p, vector<int> &a, int &n) const{
    queue<Node*> q;
    q.push(p); ++n; // Добавляем вершину начала обхода
    while (!q.empty()){
        Node* temp = q.front(); q.pop();
        // Добавляем детей вершины, если они есть
        if(temp -> left != nullptr) {q.push(temp -> left); ++n;}
        if(temp -> right != nullptr) {q.push(temp -> right); ++n;}
        a.emplace_back(temp -> getKey());
    }
 }
void BinTree::del(Node* p){
    if(p -> left == nullptr && p -> right == nullptr){
        Node* par = p -> parent;
        bool isLeft = false;
        if(par -> left == p) isLeft = true;
        if(isLeft) par -> left = nullptr;
        else par -> right = nullptr;
        delete p;
        p = nullptr;
        return;
    }
    Node* temp = p;
    while(temp -> left != nullptr || temp -> right != nullptr){
        if(temp -> left != nullptr) temp = temp -> left;
        else if(temp -> right != nullptr) temp = temp -> right;
    }
    p -> key = temp -> key;
    //Говорим родителю, что его ребенок nullptr
    Node* par = temp -> parent;
    if(par -> left == temp) par -> left = nullptr;
    else par -> right = nullptr;
    delete temp;
    temp = nullptr;
}

void BinTree::delRoot(){
    if(root -> left == nullptr && root -> right == nullptr){
        root = nullptr;
        return;
    }
    Node* temp = root;
    while(temp -> left != nullptr || temp -> right != nullptr){
        if(temp -> left != nullptr) temp = temp -> left;
        else if(temp -> right != nullptr) temp = temp -> right;
    }
    root -> key = temp -> key;
    //Говорим родителю, что его ребенок nullptr
    Node* par = temp -> parent;
    if(par -> left == temp) par -> left = nullptr;
    else par -> right = nullptr;
    delete temp;
    temp = nullptr;
}

void BinTree::clearTree() {
    while (root -> left !=  nullptr || root -> right != nullptr){
        if(root -> left != nullptr) del(root -> left);
        if(root -> right != nullptr) del(root -> right);
    }
}

BinTree::~BinTree() {
    this -> clearTree();
    this -> delRoot();
}

Node *BinTree::findKey(Node *p, int k) const {
    if(p -> key == k) return p;
    else{
        Node* ans = nullptr;
        if(p -> right != nullptr){
            ans = findKey(p -> right, k);
        }
        if(p -> left != nullptr){
            ans = findKey(p -> left, k);
        }
        return ans;
    }
}

Node *BinTree::findMax(Node *p) const {
    Node* maxi = p;

   auto cmp = [](Node* a, Node* b){
        return a -> key < b -> key;
    };

    if(p -> left != nullptr) maxi = std::max(maxi, findMax(p -> left), cmp);
    if(p -> right != nullptr) maxi = std::max(maxi, findMax(p -> right), cmp);

    return maxi;
}

Node *BinTree::findMin(Node *p) const {
    Node* mini = p;

    auto cmp = [](Node* a, Node* b){
        return a -> key < b -> key;
    };

    if(p -> left != nullptr) mini = std::min(mini, findMin(p -> left), cmp);
    if(p -> right != nullptr) mini = std::min(mini, findMin(p -> right), cmp);

    return mini;
}

int BinTree::findHeight(Node *p) const {
    int height = 1;
    int subTreeHeight = 0;
    if(p -> left != nullptr) subTreeHeight = findHeight(p -> left);
    if(p -> right != nullptr) subTreeHeight = std::max(subTreeHeight, findHeight(p -> right));

    return height + subTreeHeight;
}

int BinTree::countVertex(Node *p) const {
    int counter = 1;
    if(p -> left != nullptr) counter += countVertex(p -> left);
    if(p -> right != nullptr) counter += countVertex(p -> right);
    return counter;
}

BinTree &BinTree::operator=(const BinTree &second){
    if(this -> root == second.root) return *this;

    this -> clearTree();
    this -> delRoot();

    if(second.root == nullptr) root = nullptr;
    else{
        root = new Node(second.root -> key);
        copy(second.root -> left, root, 0);
        copy(second.root -> right, root, 1);
    }
    return *this;
}


