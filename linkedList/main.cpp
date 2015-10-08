#include <iostream>
#include "linkedList.h"

int main(int argc, char *argv[]){

    std::vector<int> a = {1, 2, 3, 4, 5};
    for(auto x: a) {
        std::cout<<x<<std::endl;
    }
    linkedList *l = new linkedList(a);
    std::cout<<l<<std::endl;
    delete l;

    return 0;
}
