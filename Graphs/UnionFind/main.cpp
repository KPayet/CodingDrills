#include "UF.h"

#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    std::ifstream input("testInput_1e6.txt");

    int N = 1000000;

    UF *uf = new UF(N);

    std::string line;

    while(std::getline(input, line)) {
        cout<<line<<endl;
    }

    delete uf;
    return 0;
}
