#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <locale>

#include "cs225/point.h"

#include "kdtree.h"


// int main() {
//     Point<2> a(3, 2);
//     Point<2> b(5, 8);
//     Point<2> c(6, 1);
//     Point<2> d(4, 4);
//     Point<2> e(9, 0);
//     Point<2> f(1, 1);
//     Point<2> g(2, 2);
//     Point<2> h(8, 7);


//     // Point<1> a(1);
//     // Point<1> b(2);
//     // Point<1> c(5);
//     // Point<1> d(4);
//     // Point<1> e(9);

   
//     // Create a vector of points
//     std::vector<Point<2>> points = {a, b, c, d, e, f, g, h};
//     KDTree<2> t1(points);

//     // std::vector<Point<1>> points = {a, b, c, d, e};
//     // KDTree<1> t1(points);

    

//     t1.printTree();
//     return 0;

// }
