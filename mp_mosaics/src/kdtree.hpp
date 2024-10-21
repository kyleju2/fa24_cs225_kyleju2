/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
  // bounds check
  if (curDim < 0 || (curDim > Dim - 1)) 
    return false;

  // conditional logic chain:
  if (first[curDim] < second[curDim])
    return true;
  
  else if (first[curDim] > second[curDim])
    return false;

  else 
    return first < second;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
  double best = 0; // var to store dist from best
  double pot = 0; // var to store dist to potential

  // Loop through points possible due to templated <int Dim> and calculate euclidian distance
  for (int i = 0; i < Dim; i++) {
    best += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
    pot +=  (target[i] - potential[i])*(target[i] - potential[i]);
  }

  if (best == pot)
    return potential < currentBest;

  return best > pot ? true : false; 
}


template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
  size = newPoints.size();
  // empty tree condition
  if (size == 0) {
    root = NULL;
    return;
  }

  vector<Point<Dim>> copy = newPoints; // make a non const copy

  root = builder(copy, 0, size-1, 0);

}


template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::builder(vector<Point<Dim>>& list, int start, int end, int dimension) {
  if (start > end)
    return NULL;
  // median calculations
  int median = (start + end) / 2;
  // create cmp lambda to call smallerDimVal between 2 pts to pass as cmp in select
  auto cmp = [dimension](const Point<Dim>& p1, const Point<Dim>& p2) {return smallerDimVal(p1, p2, dimension);};
  KDTreeNode* root = new KDTreeNode(list[median]); // create new node to be the root of our tree
  // call select to get the median value and partition our list
  select(list.begin() + start, list.end(), list.begin() + median, cmp);
  // recursively call down right and left subtrees
  // (d + 1) mod k -> from MP writeup
  root->left = builder(list, start, median - 1, (dimension + 1) % Dim); 
  root->right = builder(list, median + 1, end, (dimension + 1) % Dim);

  return root; // return root (pointer to tree root node)
}


template <typename RandIter, typename Comparator>
RandIter partition(RandIter left, RandIter right, RandIter pivotIndex, Comparator cmp) {
  auto pivot = *pivotIndex;
  std::iter_swap(pivotIndex, right-1); // move pivotIndex to the end (right)
  
  RandIter storeIndex = left;
  
  for (RandIter it = left; it != right-1; ++it) {
    if (cmp(*it, pivot)) {
      std::iter_swap(storeIndex, it);
      ++storeIndex;
    }
  }

  std::iter_swap(storeIndex, right-1);
  return storeIndex;
}


template <typename RandIter, typename Comparator>
void select(RandIter begin, RandIter end, RandIter k, Comparator cmp) {
  // base case:
  if (begin == end)
    return;
  
  RandIter pivotIndex = begin + (end - begin) / 2;
  pivotIndex = partition(begin, end, pivotIndex, cmp);
  if (k == pivotIndex)
    return;

  else if (k < pivotIndex)
    return select(begin, pivotIndex, k, cmp);

  else 
    return select(pivotIndex+1, end, k, cmp);

}

// Helper function to traverse and copy one tree and make a copy of it
template <int Dim>
void copy(KDTree<Dim>* sub_tree_1, KDTree<Dim>* sub_tree_2) {
  // sub_tree_1 is the original; sub_tree_2 is the copy;
  if (sub_tree_1 == NULL) {
    sub_tree_2 = NULL; // if original tree node is NULL, make copy's tree node also NULL 
  }
  else {
    sub_tree_2->point = sub_tree_1->point; // shallow copy of point values to sub_tree_2
    copy(sub_tree_1->left, sub_tree_2->left); // recursive call on left subtree
    copy(sub_tree_1->right, sub_tree_2->right); // recursive call on right subtree
  }
}


// helper function to swap Points<Dim> in a std::vector
// template <int Dim>
// void swap(Point<Dim>& p1, Point<Dim>& p2) {
//   Point<Dim> tmp = p1; // temp variable to store p1 during re-assignment
//   p1 = p2;
//   p2 = tmp;
// }

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  size = other.size; // update size member variable
  /* 
    call recursive copy helper to create a deep copy of the KDTtree structure in the 
    newly created class object.
  */
 this->root = new KDTreeNode();
 copy(other.root, this->root);
}



template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  // self assignment check
  if (&rhs == this)
    return *this;

  clear(this); // delete any currently stored dynamic memory before re-assignment to avoid memory leaks
  size = rhs.size; // update size member variable
  this->root = new KDTreeNode(); // create root node
  copy(rhs.root, this->root); // once again call the handy copy helper function to make a deep copy of the tree
  return *this;
}

// defining a recursive helper function to erase a k-d tree
template <int Dim>
void clear(KDTree<Dim>* node) {
  // check to make sure we dont call delete on nullptr
  if (!node)
    return;
  // recurse down subtrees, deleting current node after calling clear
  // on each sub tree so that its reference is stored on the call stack
  clear(node->left); // recursive call on left sub-tree
  clear(node->right); // recursive call on right-subtree
  delete node; // delete node
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  // clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

