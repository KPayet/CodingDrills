<h3>Stack</h3>

Implementation of a simple Stack class.
Here, I provide two different implementations:

* The first implementation is linked list based, and I use the LinkedList class in the CodingDrills folder. It is pretty much the same as the Queue class, and the only thing to do is ensure that we addFirst instead of last, and change a few names...
* The second one is dynamic array based implementation. This last implementation has better amortized time complexities, but some slow operations from time to time (when we need to rebuffer). So, the choice between the two implementations depends on whether one needs only fast operations, or can accomodate some slow operations, if it ends up being faster in average.

<br/>
Note: 
The class has been tested with valgrind for memory leaks, and no problem was found.
