#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "cs225/point.h"

#include "kdtree.h"


int main() {
    Point<2> a(3, 2);
    Point<2> b(5, 8);
    Point<2> c(6, 1);
    Point<2> d(4, 4);
    Point<2> e(9, 0);
    Point<2> f(1, 1);
    Point<2> g(2, 2);
    Point<2> h(8, 7);

    vector<Point<2>> arr = {a, b, c, d, e, f, g, h};
    
    KDTree<2> t1(arr);
    t1.printTree();

    return 0;

}
