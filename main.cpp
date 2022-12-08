#include <iostream>
#include <celero/Celero.h>
#include "BTree.h"
#include "RTree.h"

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
        float value[3] = {i*13+87, i*37-28, i*19+43};
        bpt.Insert(min,max,value);
        std::cout<<i*13+87<<' ';

    }
}

int main() {
    test1();
}

BASELINE(DemoSimple, Baseline, 10, 1000000)
{
    celero::DoNotOptimizeAway(static_cast<float>(sin(UniformDistribution(RandomDevice))));
}