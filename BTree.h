//
// Created by goeran on 12.01.2023.
//

#ifndef TREES_BTREE_H
#define TREES_BTREE_H

#include <iostream>

template <class T>
class BTreeNode {
public:
    int t;
    bool leaf;
    int n;
    T* keys;
    BTreeNode<T>** C;
    BTreeNode(int _t, bool _leaf) {
        t = _t;
        leaf = _leaf;
        keys = new T[2 * t - 1];
        C = new BTreeNode<T>*[2 * t];
        n = 0;
    }
    void traverse() {
        int i;
        for (i = 0; i < n; i++) {
            if (!leaf)
                C[i]->traverse();
            std::cout << " " << keys[i];
        }
        if (!leaf)
            C[i]->traverse();
    }
    BTreeNode<T>* search(T k) {
        int i = 0;
        while (i < n && k > keys[i])
            i++;
        if (keys[i] == k)
            return this;
        if (leaf)
            return NULL;
        return C[i]->search(k);
    }
    void insertNonFull(T k) {
        int i = n - 1;
        if (leaf) {
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
            n = n + 1;
        } else {
            while (i >= 0 && keys[i] > k)
                i--;
            if (C[i + 1]->n == 2 * t - 1) {
                splitChild(i + 1, C[i + 1]);
                if (keys[i + 1] < k)
                    i++;
            }
            C[i + 1]->insertNonFull(k);
        }
    }
    void splitChild(int i, BTreeNode<T>* y) {
        BTreeNode<T>* z = new BTreeNode<T>(y->t, y->leaf);
        z->n = t - 1;
        for (int j = 0; j < t - 1; j++)
            z->keys[j] = y->keys[j + t];
        if (y->leaf == false) {
            for (int j = 0; j < t; j++)
                z->C[j] = y->C[j + t];
        }
        y->n = t - 1;
        for (int j = n; j >= i + 1; j--)
            C[j + 1] = C[j];
        C[i + 1] = z;
        for (int j = n - 1; j >= i; j--)
            keys[j + 1] = keys[j];
        keys[i] = y->keys[t - 1];
        n = n + 1;
    }
    void remove(T k) {
        int idx = findKey(k);
        if (idx < n && keys[idx] == k) {
            if (leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        } else {
            if (leaf) {
                std::cout << "The key " << k << " is does not exist in the tree\n";
                return;
            }
            bool flag = (idx == n);
            if (C[idx]->n < t)
                fill(idx);
            if (flag && idx > n)
                C[idx - 1]->remove(k);
            else
                C[idx]->remove(k);
        }
    }
    void removeFromLeaf(int idx) {
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];
        n--;
    }
    void removeFromNonLeaf(int idx) {
        T k = keys[idx];
        if (C[idx]->n >= t) {
            T pred = getPred(idx);
            keys[idx] = pred;
            C[idx]->remove(pred);
        } else if (C[idx + 1]->n >= t) {
            T succ = getSucc(idx);
            keys[idx] = succ;
            C[idx + 1]->remove(succ);
        } else {
            merge(idx);
            C[idx]->remove(k);
        }
    }
    T getPred(int idx) {
        BTreeNode<T>* cur = C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];
        return cur->keys[cur->n - 1];
    }
    T getSucc(int idx) {
        BTreeNode<T>* cur = C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];
        return cur->keys[0];
    }
    void fill(int idx) {
        if (idx != 0 && C[idx - 1]->n >= t)
            borrowFromPrev(idx);
        else if (idx != n && C[idx + 1]->n >= t)
            borrowFromNext(idx);
        else {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
    }
    void borrowFromPrev(int idx) {
        BTreeNode<T>* child = C[idx];
        BTreeNode<T>* sibling = C[idx - 1];
        for (int i = child->n - 1; i >= 0; --i)
            child->keys[i + 1] = child->keys[i];
        if (!child->leaf) {
            for (int i = child->n; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }
        child->keys[0] = keys[idx - 1];
        if (!child->leaf)
            child->C[0] = sibling->C[sibling->n];
        keys[idx - 1] = sibling->keys[sibling->n - 1];
        child->n += 1;
        sibling->n -= 1;
    }
    void borrowFromNext(int idx) {
        BTreeNode<T>* child = C[idx];
        BTreeNode<T>* sibling = C[idx + 1];
        child->keys[(child->n)] = keys[idx];
        if (!(child->leaf))
            child->C[(child->n) + 1] = sibling->C[0];
        keys[idx] = sibling->keys[0];
        for (int i = 1; i < sibling->n; ++i)
            sibling->keys[i - 1] = sibling->keys[i];
        if (!sibling->leaf) {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }
        child->n += 1;
        sibling->n -= 1;
    }
    void merge(int idx) {
        BTreeNode<T>* child = C[idx];
        BTreeNode<T>* sibling = C[idx + 1];
        child->keys[t - 1] = keys[idx];
        for (int i = 0; i < sibling->n; ++i)
            child->keys[i + t] = sibling->keys[i];
        if (!child->leaf) {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];
        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];
        child->n += sibling->n + 1;
        n--;
        delete (sibling);
    }
    int findKey(T k) {
        int idx = 0;
        while (idx < n && keys[idx] < k)
            ++idx;
        return idx;
    }
};
template <class T>
class BTree {
    BTreeNode<T>* root;
    int t;
public:
    BTree(int _t) {
        root = NULL;
        t = _t;
    }
    void traverse() {
        if (root != NULL)
            root->traverse();
    }
    BTreeNode<T>* search(T k) {
        return (root == NULL) ? NULL : root->search(k);
    }
    void insert(T k) {
        if (root == NULL) {
            root = new BTreeNode<T>(t, true);
            root->keys[0] = k;
            root->n = 1;
        } else {
            if (root->n == 2 * t - 1) {
                BTreeNode<T>* s = new BTreeNode<T>(t, false);
                s->C[0] = root;
                s->splitChild(0, root);
                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->C[i]->insertNonFull(k);
                root = s;
            } else
                root->insertNonFull(k);
        }
    }
    void remove(T k) {
        if (!root) {
            std::cout << "The tree is empty\n";
            return;
        }
        root->remove(k);
        if (root->n == 0) {
            BTreeNode<T>* tmp = root;
            if (root->leaf)
                root = NULL;
            else
                root = root->C[0];
            delete tmp;
        }
    }
};

#endif