/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    return find(root, key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == NULL || subtree->key == key)
        return subtree;
    
    if (key < subtree->key)
        return find(subtree->left, key);

    else
        return find(subtree->right, key);
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{   
    if (root == NULL) {
        root = new Node(key, value);
        return;
    }
    else 
        insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key, value); // Create a new node
        return;
    }
    
    // Check if the key already exists
    if (key == subtree->key) 
        return; // Duplicate key, do not modify the tree
    
    // Decide to go left or right based on the key comparison
    if (key < subtree->key)
        insert(subtree->left, key, value); 

    else 
        insert(subtree->right, key, value);
     
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    if (first == NULL || second == NULL) return; // Unable to swap with NULL

    K tmpKey = first->key;
    V tmpVal = first->value;

    first->key = second->key;
    first->value = second->value;

    second->key = tmpKey;
    second->value = tmpVal;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == nullptr)
        return; // Node does not exist

    if (key < subtree->key)
        remove(subtree->left, key); // Traverse left

    else if (key > subtree->key)
        remove(subtree->right, key); // Traverse right

    else {
        
        // 1st case: no children
        if (subtree->left == nullptr && subtree->right == nullptr) {
            delete subtree;
            subtree = nullptr; 
        } 

        // 2nd case: one child
        else if (subtree->left == nullptr) {
            Node* temp = subtree; 
            subtree = subtree->right;
            delete temp;
        } 

        else if (subtree->right == nullptr) {
            Node* temp = subtree;
            subtree = subtree->left;
            delete temp;
        } 

        // 3rd case: two children
        else {
            // Find the in-order predecessor (rightmost in the left subtree)
            Node* IOP = subtree->left;
            while (IOP->right != nullptr) {
                IOP = IOP->right;
            }

            // Copy the in-order predecessor key and value
            subtree->key = IOP->key;
            subtree->value = IOP->value;

            // Remove the in-order predecessor
            remove(subtree->left, IOP->key);
        }
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> tree; // initialize an empty bst

    // range based for loop (read-only)
    for (const auto& it: inList) {
        tree.insert(it.first, it.second); // call our insert function (key, value)
    }

    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList) {
    std::vector<int> height(inList.size(), 0);
    std::sort(inList.begin(), inList.end());

    do {
        BST<K, V> bst = listBuild(inList);
        int currentHeight = bst.height();
        if (currentHeight >= 0 && currentHeight < (int)height.size()) {
            height[currentHeight]++;
        }
    }
    while (std::next_permutation(inList.begin(), inList.end()));

    return height;
}