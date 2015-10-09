#include <iostream>
#include "linkedList.h"

int main(int argc, char *argv[]){

    std::vector<double> a = {1.5, 2.5, 3.0, 4.9, 5.55};

    linkedList<double> *l = new linkedList<double>(a);
    std::cout<<l<<std::endl;

    l->removeFirst();
    std::cout<<l<<std::endl;
    l->removeLast();
    std::cout<<l<<std::endl;
    l->addLast(18.26);
    std::cout<<l<<std::endl;
    l->addFirst(6.26);
    std::cout<<l<<std::endl;
    l->addLast(18.26);
    std::cout<<l<<std::endl;
    l->clear();
    std::cout<<l<<" "<<l->size()<<std::endl;

    delete l;

    return 0;
}
