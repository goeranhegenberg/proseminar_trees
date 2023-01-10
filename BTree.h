// Header file for B-Tree

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
#include <list>
#include <map>

using namespace std;

// Node class
template <typename T>
struct Node
{
    T* keys;
    Node** children;
    int count;
    int order;

public:
    // Constructor
    Node(int order)
    {
        this->order = order;
        keys = new T[order - 1];
        children = new Node*[order];
        for (int i = 0; i < order; i++)
            children[i] = NULL;
        count = 0;
    }

    // Destructor
    ~Node()
    {
        delete[] keys;
        delete[] children;
    }

    // Insert key into node
    void insertKey(T key)
    {
        int i = count - 1;
        while (i >= 0 && keys[i] > key)
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        count++;
    }

    // Split node
    void splitChild(int i, Node* child)
    {
        Node* newNode = new Node(child->order);
        newNode->count = order / 2 - 1;
        for (int j = 0; j < order / 2 - 1; j++)
            newNode->keys[j] = child->keys[j + order / 2];
        if (!child->isLeaf())
        {
            for (int j = 0; j < order / 2; j++)
                newNode->children[j] = child->children[j + order / 2];
        }
        child->count = order / 2 - 1;
        for (int j = count; j >= i + 1; j--)
            children[j + 1] = children[j];
        children[i + 1] = newNode;
        for (int j = count - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = child->keys[order / 2 - 1];
        count++;
    }

    // Remove key from node
    void removeKey(int i)
    {
        for (int j = i + 1; j < count; j++)
            keys[j - 1] = keys[j];
        count--;
    }

    // Remove child from node
    void removeChild(int i)
    {
        for (int j = i + 1; j <= count; j++)
            children[j - 1] = children[j];
    }

    // Search key recursively
    int search(T key)
    {
        int i = 0;
        while (i < count && key > keys[i])
            i++;
        if (keys[i] == key)
            return i;
        if (isLeaf())
            return -1;
        return children[i]->search(key);
    }

    // Getters
    T getKey(int i) { return keys[i]; }
    Node* getChild(int i) { return children[i]; }
    int getCount() { return count; }
    bool isLeaf() { return children[0] == NULL; }

    // Setters
    void setKey(int i, T key) { keys[i] = key; }
    void setChild(int i, Node* child) { children[i] = child; }
    void setCount(int count) { this->count = count; }
};

// BTree class
template <class T>
class BTree
{
private:
    Node<T>* root;
    int order;

    void print(Node<T>* cursor) {
        // You must NOT edit this function.
        if (cursor != NULL) {
            for (int i = 0; i < cursor->count; ++i) {
                std::cout << cursor->keys[i] << " ";
            }
            std::cout << "\n";

            /*if (!cursor->is_leaf) {
                for (int i = 0; i < cursor->count + 1; ++i) {
                    print(cursor->children[i]);
                }
            }*/
        }
    }

public:
    // Constructor
    BTree(int order)
    {
        this->order = order;
        root = NULL;
    }

    // Destructor
    ~BTree()
    {
        delete root;
    }

    // Insert key into tree
    void insert(T key)
    {
        if (root == NULL)
        {
            root = new Node<T>(order);
            root->insertKey(key);
        }
        else
        {
            if (root->getCount() == order - 1)
            {
                Node<T>* newNode = new Node<T>(order);
                newNode->children[0] = root;
                newNode->splitChild(0, root);
                int i = 0;
                if (newNode->getKey(0) < key)
                    i++;
                newNode->getChild(i)->insertKey(key);
                root = newNode;
            }
            else
                root->insertKey(key);
        }
    }

    // Remove key from tree
    void remove(T key)
    {
        if (root == NULL)
            return;
        root->removeKey(key);
        if (root->getCount() == 0)
        {
            Node<T>* temp = root;
            if (root->isLeaf())
                root = NULL;
            else
                root = root->getChild(0);
            delete temp;
        }
    }

    // Search for key in tree
    bool search(T key)
    {
        if (root == NULL)
            return false;
        return root->search(key);
    }

    // Print tree
    void print(){
        if (root == NULL) {
            return;
        }
        print(root);
    }
};

#endif

// Path: BTree.cpp
// Implementation file for B-Tree
