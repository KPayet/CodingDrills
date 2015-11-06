#include "mergesort.h"

namespace Merge{

static void sort(std::vector<int> &a, std::vector<int> &aux, int lo, int hi){

}

void sort(std::vector<int> &a) {
    std::vector<int> aux;   // mergesort is not in place and requires an auxiliary array
    sort(a, aux, 0, a.size()-1);    // does all the work, but stays in the shadows...
}
}
