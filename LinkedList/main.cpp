#include <iostream>
#include "LinkedList.h"

int main(int argc, char *argv[]){

    std::vector<double> a = {1.5, 2.5, 3.0, 4.9, 5.55, 5.154};

    LinkedList<double> l(a);

    for(auto x: l) {
        std::cout<<x<<std::endl;
        x = 1.0;
    }
    l.print();
    //delete l;

    return 0;
}
