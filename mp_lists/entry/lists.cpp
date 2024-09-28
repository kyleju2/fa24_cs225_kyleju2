#include "List.h"
#include <iostream>
using namespace std;

int main() {
    List<int> l1;
    l1.insertFront(8);
    l1.insertFront(7);
    l1.insertFront(6);
    l1.insertFront(5);
    l1.insertFront(4);
    l1.insertFront(3);
    l1.insertFront(2);
    l1.insertFront(1);


    l1.print();
    cout << endl;
    //l1.waterfall();

    // for (int x : l1) {
    //     cout << x << endl;
    // }
    //l1.reverse();
    l1.reverseNth(6);
    l1.print();
    cout << endl;

    //cout << "< 1 3 5 7 2 6 4 8 >" << endl;


    return 0;
}
