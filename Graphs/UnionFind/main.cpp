#include "UF.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    using std::cout;
    using std::endl;

    std::ifstream input("testInput_1e6.txt");

    int N = 1000000;

    UF *uf = new UF(N);

    std::string line;

    int counter = 0;

    while(std::getline(input, line) && counter<1000) {
        int p = std::stoi(line.substr(0, line.find(" ")));
        int q = std::stoi(line.substr(line.find(" ") + 1, line.length() - line.find(" ")));
        
	uf->Union(p, q);
        ++counter;
    }

    delete uf;
    return 0;
}
