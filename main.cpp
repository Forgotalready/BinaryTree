#include "binaryTree.h"

int main()
{
    vector<int> t = {1,2,3,4,5};
    BinTree a(t, 5);
    cout << "Check print function:\n";
    a.printTree(0, a.getRoot());

    cout << "\nCheck BFS:\n";
    vector<int> bfs; int n;
    a.BFS(a.getRoot(), bfs, n);
    for(auto x : bfs) cout << x << " ";
    cout << "\nDelete function\n";
    a.delRoot();
    cout << "\n\n";
    a.printTree(0, a.getRoot());
    cout << "\n\n" << a.countVertex(a.getRoot()) << "\n";
    cout << "\n\n" << a.findHeight(a.getRoot()) << "\n";
    cout << "\n\n" << a.findMax(a.getRoot()) -> getKey()<< "\n";
    cout << "\n\n" << a.findMin(a.getRoot()) -> getKey() << "\n";

    a.delRoot();
    BinTree b = a;
    b.delRoot();
    cout << "\n\nB tree\n";
    b.printTree(0, b.getRoot());
    cout << "\n\na tree\n";
    a.printTree(0, a.getRoot());
    b = a;
    a.clearTree();
    cout << "\n\n";
    a.printTree(0, a.getRoot());

    cout << "\n\nb btree \n";
    b.printTree(0, b.getRoot());
}
