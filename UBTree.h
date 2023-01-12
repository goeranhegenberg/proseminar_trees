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
#include "BPlusTree.h"

using namespace std;

template <typename T, int NUMDIMS>
class UBTree {
    BPlusTree<T>* bpt;

    int z_function(int x, int y)
    {
        int z = 0;
        for (int i = 0; i < 32; i++)
        {
            z |= (x & 1) << (2 * i);
            z |= (y & 1) << (2 * i + 1);
            x >>= 1;
            y >>= 1;
        }
        return z;
    }

    T get_z(T* data) {
        if(NUMDIMS == 1) {
            return data[0];
        } else {
            T z = z_function(data[0], data[1]);
            for(int i=2; i<NUMDIMS; i++) {
                z = z_function(z, data[i]);
            }
            return z;
        }
    }
public:
    UBTree(std::size_t _degree) {
        this->bpt = new BPlusTree<T>(_degree);
    }

    ~UBTree() {
        delete this->bpt;
    }

    void insert(T* data) {
        bpt->insert(get_z(data));
    }

    void remove(T* data) {
        bpt->remove(get_z(data));
    }

    bool search(T* data) {
        return bpt->search(get_z(data));
    }

    bool rangeSearch(T* data1, T* data2) {
        return bpt->rangeSearch(get_z(data1), get_z(data2));
    }
};

#endif