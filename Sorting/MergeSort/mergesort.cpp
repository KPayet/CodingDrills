#include "mergesort.h"

namespace Merge{

void sort(std::vector<int> &a) {

    std::vector<int> aux;
    sort(a, aux, 0, a.size()-1);
}

static void sort(std::vector<int> &a, std::vector<int> &aux, int lo, int hi){

}
}
