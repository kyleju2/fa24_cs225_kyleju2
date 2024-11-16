#include "dsets.h"

void DisjointSets::addelements(int num)
{
    for (int i = 0; i < num; i++) {
        data.push_back(-1); // -1 is the default value, denoting a 'root'
    }
}


int DisjointSets::find(int elem)
{
    // this is taken from the code on the cs225 lecture slides
    // I think that this is allowed?
    if (data[elem] < 0) {return elem;} // root node (-1)
    
    else {
        int root = find(data[elem]);
        data[elem] = root;
        return root;
    } 
}


void DisjointSets::setunion(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    if (rootA != rootB) {
        if (data[rootA] <= data[rootB]) {
            data[rootA] += data[rootB]; // change size of data[rootA] to hold new size
            data[rootB] = rootA;
        }
        else {
            data[rootB] += data[rootA]; // change size of data[rootA] to hold new size
            data[rootA] = rootB;
        }
    }

}


int DisjointSets::size(int elem)
{
    int root = find(elem);
    return -data[root];
}


int DisjointSets::getValue(int elem) const
{
    return data[elem];
}

