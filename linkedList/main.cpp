#include <iostream>
#include "linkedList.h"

int main(int argc, char *argv[]){

    std::vector<double> a = {1.5, 2.5, 3.0, 4.9, 5.55};

    linkedList<double> *l = new linkedList<double>(a);

    for(auto x: l) {
        std::cout<<x<<std::endl;
        x = 1.0;
    }
    l->print();
    delete l;

    return 0;
}
