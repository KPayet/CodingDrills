#include <iostream>
#include "linkedList.h"

int main(int argc, char *argv[]){

    linkedList *l = new linkedList();
    std::cout<<l<<std::endl;
    l->addFirst(6);
    std::cout<<l<<std::endl;
    l->addLast(12);
    std::cout<<l<<std::endl;
    l->addFirst(6);
    std::cout<<l<<std::endl;
    l->addFirst(6);
    std::cout<<l<<std::endl;
    l->addLast(18);
    std::cout<<l<<std::endl;
    l->removeLast();
    std::cout<<l<<std::endl;
    l->removeLast();
    std::cout<<l<<std::endl;
    l->removeFirst();

    delete l;

    return 0;
}
