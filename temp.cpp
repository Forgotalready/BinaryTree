BinTree::printTreeVert(Node* p, int left_border, int right_border, int y){
    if(!p) return;
    int x = (left_border + right_border) / 2;
    HANDLE hstOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD curpos = {x, y};
    SetConsoleCursorPosition(hstOut, curpos);
    cout << p -> key;
    printTreeVert(p -> left, left_border, x, y + 2);
    printTreeVert(p -> right, x, right_border, y + 2);
}
/*
    Замечание: 1)В main долнжны быть следующие переменные HANDLE hstOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    2) вызов функции делается так:
    2.1) Получаем положение курсора GetConsoleScreenBufferInfo(hsout, &csbi);
    COORD cursor = csbi.dwCursorPosition;
    T1.printTreeVert(T1.getRoot(), 0, 60,cursor.Y + 2); puts(" ");
*/

void BinTree::add(int k, Node* p){
    if(p == nullptr) return;

    if(p -> left == nullptr){
        Node* q = new Node(k);
        p -> left = q;
        q -> parent = p;
        return;
    }
    if(p -> right == nullptr){
        Node* q = new Node(k);
        p -> right = q;
        q -> parent = p;
        return;
    }
    if(rand() % 2 == 0){
        add(k, p -> left);
    }else{
        add(k, p -> right);
    }
}
void BinTree::del(Node* p){
    if(p == nullptr) return;
    if(p == root) {
        delRoot();
        return;
    }
    Node* q = p -> parent;
    // Лист
    if(p -> left == nullptr && p -> right == nullptr){
        if(q -> left == p) q -> left = nullptr;
        else q -> right = nullptr;
        delete p;
        return;
    }
    // Нет левого сына
    if(p -> left == nullptr){
        if(q -> left == p) q -> left = p -> right;
        else q -> right = p -> right;
        p -> right -> parent = q;
        delete p;
        return;
    }
    // Нет правого сына
    if(p -> right == nullptr){
        if(q -> left == p) q -> left = p -> left;
        else q -> right = p -> left;
        p -> left -> parent = q;
        delete p;
        return;
    }

    // Есть оба ребёнка
    Node* t = p;
    while(t -> left != nullptr) t = t -> left;

    t -> parent -> left = t -> right;
    if(t -> right != nullptr){
        t -> right -> parent = t -> parent;
    }
    // 1 вариант (инф. поле хранит мало данных)
    p -> key = t -> key;
    delete t;
    /* 2 вариант (сложнее, установка 6 связей)
    if(q -> left == p) q -> left = t;
    else q -> right == p;
    t -> parent = q;
    t -> left = p -> left; t -> right = p -> right;
    p -> right -> parent = t;
    if(p -> left != nullptr) p -> left -> parent = t;
    delete p;
    */
}
