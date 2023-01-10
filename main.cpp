#include <iostream>
//#include <interval-tree/interval_tree.hpp>
#include <benchmark/benchmark.h>
#include "BTree.h"
#include "BPlusTree.h"
#include "RTree.h"
#ifndef _WIN32
#include <cmath>
#include <cstdlib>
#endif

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

/*void testIntervalTree() {
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
}*/

/*int main() {
    //testIntervalTree();
}*/

static void BM_BTree(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        BTree<int> bpt(15);

        for(int i = 0; i < 100; i++){
            bpt.insert(i * 13 + 87);
        }
    }
}

static void BM_SomeFunction2(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        BPlusTree<int> bpt(15);

        for(int i = 0; i < 100; i++){
            bpt.insert(i * 13 + 87);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_BTree);
BENCHMARK(BM_SomeFunction2);

// Run the benchmark
BENCHMARK_MAIN();