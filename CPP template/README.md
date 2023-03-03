## CP template
### Benchmarking and constants
Contains code Bench-Marking, Random Number Genegator and useful constants that we may need at compile-time.
   - To benchmark code we put `Timer` instance in the scope of the algorithm, timer begins when Construtor is called and stops when destructor. 
     We donot need to tweak or call `TIMER` attributes to calculate timings it happens automatically when object gets created inside the scope and destroyed when
     execution leaves the scope.
   - We use `std::random_device` to seed `std::mt19937` Mersenne Twister PRNG and use `uniform_int_distribution<>(a,b)` to map `unsigned int` from PRNG to range a to b.
   - At compile time we need `const` values to perform optimizations and having precalculated values for grid traversal also saves time and its less error prone during contest time.  

### Bi-Connectivity
We have 2 types of Bi-connectivity to condence graph into much simpler version called condensed graph (aka Tree), which makes analysis of graph easier since analyzing tree is much more convinient.

Bi-connectivity :  nodes u and v connected by path such that
- vertex Bi-connectivity : we have no common nodes with no common edges 
- edge Bi-connectivity   : we have common nodes with no common edges!
- Euler Cycle is special case, a cycle that starts and ends at the same graph vertex after visiting every edge exactly once.

### FFT-and-IFFT
Fast Fourier Transform and Inverse-FFT algorithms are used to handle large polynomials and matrices efficiently. It uses 2 important fact to make it work
- Using roots of unity as periodic function which gives n unique values when raised to thier powers, we can use infact any number in any number system which have this property
  ,for ex: generator function can be alternative.
- Uniquness of polynomial thats explained in [Lagrange interpolation](https://en.wikipedia.org/wiki/Lagrange_polynomial#Definition)

### Functional graph
Graph that have only one outgoing edges like a function f(x) gives unique y, It has inherant structure in which there exist only 1 loop and every node
we traverse will always led to that loop only.

### Kosaraju and 2SAT
Kosaraju algorithm for finding Strongly Connected Component in direct graphs and 2SAT problem can be easily converted into finding SCC problem where we need to check whether
there lies contradiction between the values of SCC and ~SCC pair nodes (aka primary & complimentary pair).

### Template MACROS 
It makes long line of codes better readable and easier to debug.


### NumberTheory
Contains most commonly used Number Theory algorithms
- Congruent modulo N (`% N`) number system mainly for counting problem that exceeds the numerical magnitude limis of computers.
- LinearSieve to find primes and composite numbers along with lowest prime multiple of a number.
- Finding `gcd()`, `lcd()`, factorials and inverse factorials are very common in combinatorics problems.

### Segment Tree
One of the most famous Data Structure well known to handle Point Updates, Point Queries, Range updates and Range queries very efficienlty in 
O(logn) time complexity. Its also easily scable onto higher dimensions without loosing significant amount of performance. Segment tree basically
works as long as there exist 
- a monoid identity, monoid element has property that it gives same element when monoid operation is applied.
- a monoid operation, associative binary operation that gives gives element of same kind after operation
- Non-Commutative operations are handled using Lazy propagation.

### Sparse Table 
One of the most usefull Static Data Structure to perform point query and range queries in O(1) time and O(logn) time for some operations. Its 
properties are also similar to Segment Tree

### Suffix Array
Usefull data-structure for string algorithms Pattern finding, data-compression algorithms, and the field of bibliometrics. 
Act of storing suffixes of strings itself inherently makes data quite easy to query either using Binary Search or using 2 pointers for above applications.

### XOR basis

Sometimes in XOR related problem realizing that Transforming xor operations is equivalent to doing bitwise addition modulo 2. 
And after finding basis-vector for given binary numbers we can make comment on entire vector space using only basis-vectors and its efficient 
because amount of basis vectors are very small compare to given input, for ex : 32bit number can have no more than 32 basis vectors even though
input data can be consist of millions of 32bit numbers.






