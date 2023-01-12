#include <iostream>
#include <interval_tree.hpp>
#include <benchmark/benchmark.h>
#include "BTree.h"
#include "BPlusTree.h"
#include "RTree.h"
#ifndef _WIN32
#include <cmath>
#include <cstdlib>
#endif

// bitwise interlacing of x and y
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

// next power of 2
int next_power_of_two(int x)
{
    int y = 1;
    while (y < x)
        y *= 2;
    return y;
}

// previous power of 2
int prev_power_of_two(int x)
{
    int y = 1;
    while (y < x)
        y *= 2;
    return y / 2;
}

void print_bool(bool cond) {
    if (cond) {
        std::cout << "True\n";
    } else {
        std::cout << "False\n";
    }
}

void test1() {
    BTree<int> bpt(15);

    for(int i=1; i<136; i++){
        bpt.insert(i*13+87);
        std::cout<<i*13+87<<' ';
        bpt.insert(i*99-28);
        std::cout<<i*99-28<<' ';

    }

    std::cout<<std::endl;
    bpt.print();

    bpt.remove(152);
    bpt.remove(269);
    bpt.remove(256);


    std::cout<<"ㄴㄴㄴ"<<std::endl;
    bpt.remove(467);
    bpt.print();

    std::cout<<std::endl<<std::endl;
    bpt.remove(764);
    bpt.remove(863);

    std::cout<<std::endl;
//    bpt.getroot();
    bpt.print();

    bpt.remove(71);
    bpt.remove(100);
    bpt.remove(139);

    std::cout<<std::endl;
    bpt.print();

    bpt.remove(368);


    std::cout<<std::endl;
    bpt.print();
}

void test2() {
    RTree<float*, float, 3> bpt = RTree<float*, float, 3>();

    for(int i=1; i<136; i++){
        float min[3] = {0,0,0};
        float max[3] = {100,100,100};
        float value[3] = {(float) i*13+87, (float) i*37-28, (float) i*19+43};
        bpt.Insert(min,max,value);
        std::cout<<i*13+87<<' ';

    }
}

void testIntervalTree() {
    using namespace lib_interval_tree;

    // interval_tree <interval <int>>;
    interval_tree_t <int> tree;

    tree.insert(make_safe_interval<int>(21, 16)); // make_safe_interval swaps low and high if not in right order.
    tree.insert({8, 9});
    tree.insert({25, 30});
    tree.insert({5, 8});
    tree.insert({15, 23});
    tree.insert({17, 19});
    tree.insert({26, 26});
    tree.insert({0, 3});
    tree.insert({6, 10});
    tree.insert({19, 20});

    tree.deoverlap();

    for (auto const& i : tree)
    {
        std::cout << "[" << i.low() << ", " << i.high() << "]\n";
    }
}

int main() {
    // print z function for (1,1)
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            std::cout << "z(" << i << "," << j << ") = " << z_function(i, j) << std::endl;
        }
    }

    // print next power of 2
    for(int i = 0; i < 10; i++) {
        std::cout << "next_power_of_two(" << i << ") = " << next_power_of_two(i) <<
        " | prev_power_of_two(" << i << ") = " << prev_power_of_two(i) << std::endl;
    }
}

static int steps = 1000;

static BTree<int> BTree_Insert() {
    BTree<int> bpt(15);

    for(int i = 0; i < steps; i++){
        bpt.insert(i * 13 + 87);
    }

    return bpt;
}

static BPlusTree<int> BPlusTree_Insert() {
    BPlusTree<int> bpt(15);

    for(int i = 0; i < steps; i++){
        bpt.insert(i * 13 + 87);
    }

    return bpt;
}

static lib_interval_tree::interval_tree_t<int> IntervalTree_Insert() {
    lib_interval_tree::interval_tree_t<int> bpt;

    for(int i = 0; i < steps; i++){
        bpt.insert({i * 13 + 87, i * 14 + 88});
    }

    return bpt;
}

static RTree<int*, int, 2> RTree_Insert() {
    RTree<int*, int, 2> bpt;

    for(int i = 0; i < steps; i++){
        int min[2] = {i * 13 + 87,i * 13 + 87};
        int max[2] = {i * 14 + 88,i * 14 + 88};
        bpt.Insert(min,max,0);
    }

    return bpt;
}

static void BM_BTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        BTree_Insert();
    }
}

static void BM_BPlusTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        BPlusTree_Insert();
    }
}

static void BM_IntervalTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        IntervalTree_Insert();
    }
}

static void BM_RTree_Insert(benchmark::State& state) {
    for (auto _ : state) {
        RTree_Insert();
    }
}

//static BTree<int> btree = BTree_Insert();
static BPlusTree<int> bplustree = BPlusTree_Insert();
static lib_interval_tree::interval_tree_t<int> intervaltree = IntervalTree_Insert();
static RTree<int*, int, 2> rtree = RTree_Insert();

static void BM_BTree_Search(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            //btree.search(i * 13 + 87);
        }
    }
}

static void BM_BPlusTree_Search(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            bplustree.search(i * 13 + 87);
        }
    }
}

static void BM_IntervalTree_Search(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            intervaltree.find({i * 13 + 88, i * 13 + 88 + 13 * 3});
        }
    }
}

static void BM_RTree_Search(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            int min[2] = {i * 13 + 88,i * 13 + 88};
            int max[2] = {i * 13 + 88 + 13 * 3,i * 13 + 88 + 13 * 3};
            rtree.Search(min,max, {});
        }
    }
}

static void BM_BTree_SearchNF(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            //btree.search(i * 13 + 88);
        }
    }
}

static void BM_BPlusTree_SearchNF(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            bplustree.search(i * 13 + 88);
        }
    }
}

static void BM_IntervalTree_SearchNF(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        for(int i = 0; i < steps; i++) {
            if(i % 2 == 0) {
                intervaltree.find({0, 1});
            } else {
                intervaltree.find({steps * 14 + 300, steps * 14 + 301});
            }
        }
    }
}

// Benchmark insertions
//BENCHMARK(BM_BTree_Insert);
BENCHMARK(BM_BPlusTree_Insert);
BENCHMARK(BM_IntervalTree_Insert);
BENCHMARK(BM_RTree_Insert);

// Benchmark search
//BENCHMARK(BM_BTree_Search);
BENCHMARK(BM_BPlusTree_Search);
BENCHMARK(BM_IntervalTree_Search);
BENCHMARK(BM_RTree_Search);

//BENCHMARK(BM_BTree_SearchNF);
BENCHMARK(BM_BPlusTree_SearchNF);
BENCHMARK(BM_IntervalTree_SearchNF);

// Run the benchmark
//BENCHMARK_MAIN();