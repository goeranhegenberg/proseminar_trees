// Header file for Universal B-Tree

#ifndef UBTree_H
#define UBTree_H

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

using namespace std;

template <class DATATYPE, class ELEMTYPE, int NUMDIMS>
class UBTree {
public:
    UBTree();
    ~UBTree();

    void insert(DATATYPE data, ELEMTYPE* min, ELEMTYPE* max) {
        if (root == NULL) {
            root = new Node(0, true);
            root->keys[0] = new ELEMTYPE[NUMDIMS * 2];
            for (int i = 0; i < NUMDIMS * 2; i++) {
                root->keys[0][i] = min[i];
            }
            root->children[0] = new Node(1, false);
            root->children[0]->keys[0] = new ELEMTYPE[NUMDIMS * 2];
            for (int i = 0; i < NUMDIMS * 2; i++) {
                root->children[0]->keys[0][i] = min[i];
            }
            root->children[0]->children[0] = data;
            root->children[0]->children[1] = new ELEMTYPE[NUMDIMS * 2];
            for (int i = 0; i < NUMDIMS * 2; i++) {
                root->children[0]->children[1][i] = max[i];
            }
            root->count = 1;
        } else {
            if (root->count == (order - 1)) {
                Node* s = new Node(0, false);
                s->children[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0][0] < min[0]) {
                    i++;
                }
                s->children[i]->insertNonFull(data, min, max);
                root = s;
            } else {
                root->insertNonFull(data, min, max);
            }
        }
    }

    void remove(ELEMTYPE* min, ELEMTYPE* max) {
        if (root != NULL) {
            root->remove(min, max);
            if (root->count == 0) {
                Node* tmp = root;
                if (root->leaf) {
                    root = NULL;
                } else {
                    root = root->children[0];
                }
                delete tmp;
            }
        }
    }

    void search(ELEMTYPE* min, ELEMTYPE* max, vector<DATATYPE>& result) {
        if (root != NULL) {
            root->search(min, max, result);
        }
    }

    void print() {
        if (root != NULL) {
            root->print();
        }
    }

private:
    struct Node {
        ELEMTYPE** keys;
        Node** children;
        int count;
        bool leaf;

        Node(int count, bool leaf) {
            this->count = count;
            this->leaf = leaf;
            keys = new ELEMTYPE*[order - 1];
            children = new Node*[order];
        }

        ~Node() {
            delete[] keys;
            delete[] children;
        }

        void insertNonFull(DATATYPE data, ELEMTYPE* min, ELEMTYPE* max) {
            int i = count - 1;
            if (leaf) {
                while (i >= 0 && keys[i][0] > min[0]) {
                    keys[i + 1] = keys[i];
                    i--;
                }
                keys[i + 1] = new ELEMTYPE[NUMDIMS * 2];
                for (int j = 0; j < NUMDIMS * 2; j++) {
                    keys[i + 1][j] = min[j];
                }
                children[i + 2] = new Node(1, false);
                children[i + 2]->keys[0] = new ELEMTYPE[NUMDIMS * 2];
                for (int j = 0; j < NUMDIMS * 2; j++) {
                    children[i + 2]->keys[0][j] = min[j];
                }
                children[i + 2]->children[0] = data;
                children[i + 2]->children[1] = new ELEMTYPE[NUMDIMS * 2];
                for (int j = 0; j < NUMDIMS * 2; j++) {
                    children[i + 2]->children[1][j] = max[j];
                }
                count++;
            } else {
                while (i >= 0 && keys[i][0] > min[0]) {
                    i--;
                }
                if (children[i + 1]->count == (order - 1)) {
                    splitChild(i + 1, children[i + 1]);
                    if (keys[i + 1][0] < min[0]) {
                        i++;
                    }
                }
                children[i + 1]->insertNonFull(data, min, max);
            }
        }

        void splitChild(int i, Node* y) {
            Node* z = new Node(order / 2 - 1, y->leaf);
            z->count = order / 2 - 1;
            
