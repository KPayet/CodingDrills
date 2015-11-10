#Quicksort

A pretty efficient implementation of quicksort. Can be used for any type that implements comparison operators.
The present implementation requires C++11.

This implementation of quicksort uses Bentley-McIlroy 3-way partitioning which gives pretty good results. You can see here: http://www.sorting-algorithms.com/static/QuicksortIsOptimal.pdf, pages 8 and 9 for the model used for this implementation. It is really worth it in terms of performance, compared to standard Dijsktra 3-way partitioning.
There is also a cutoff to insertion sort for arrays smaller than 7 elements.
Finally, the pivot element for partitioning is computed using Tukey's ninther (= median of 3 medianS of 3), or simple median of 3 for smaller arrays.
The biggest factor for the performance seems to be the partitioning algorithm used, which is what we would expect...


