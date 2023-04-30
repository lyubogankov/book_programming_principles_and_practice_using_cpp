/*
2. Write a function print() that prints a vector of ints to cout.
   Give it two arguments: a string for “labeling” the output and a vector.


3. Create a vector of Fibonacci numbers and print them using the function from exercise 2.
   To create the vector, write a function, fibonacci(x,y,v,n), where integers x and y are ints,
   v is an empty vector<int>, and n is the number of elements to put into v; 
   v[0] will be x and v[1] will be y.
   
   A Fibonacci number is one that is part of a sequence where each element is the sum of the two previous ones.
   For example, starting with 1 and 2, we get 1, 2, 3, 5, 8, 13, 21, . . . .
   
   Your fibonacci() function should make such a sequence starting with its x and y arguments.


4. An int can hold integers only up to a maximum number.
   Find an approximation of that maximum number by using fibonacci().

   Printout below, but the largest fib # was 45 (1-indexed) = 1,836,311,903
   This lines up with 32-bit signed integers.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ex 02
void print(const string& label, const vector<int>& values) {
    cout << label << "\n";
    for(int i=0; i < values.size(); i++)
        cout << "    [" << i << "] " << values[i] << "\n";
}

// ex 03
void fibonacci(int x, int y, vector<int>& v, int n) {
    v.push_back(x);
    v.push_back(y);
    for (int i=2; i<n; i++)
        v.push_back( v[i-2] + v[i-1] );
}

int main() {

    // testing ex 02
    vector<int> v;
    for(int i=1; i<=10; i++) v.push_back(i*i);

    print("My vector:", v);

    // testing ex 03
    vector<int> fib;
    fibonacci(1, 2, fib, 100);
    print("fibonnaci", fib);

    return 0;
}

// ex04

/*

fibonnaci
    [0] 1
    [1] 2
    [2] 3
    [3] 5
    [4] 8
    [5] 13
    [6] 21
    [7] 34
    [8] 55
    [9] 89
    [10] 144
    [11] 233
    [12] 377
    [13] 610
    [14] 987
    [15] 1597
    [16] 2584
    [17] 4181
    [18] 6765
    [19] 10946
    [20] 17711
    [21] 28657
    [22] 46368
    [23] 75025
    [24] 121393
    [25] 196418
    [26] 317811
    [27] 514229
    [28] 832040
    [29] 1346269
    [30] 2178309
    [31] 3524578
    [32] 5702887
    [33] 9227465
    [34] 14930352
    [35] 24157817
    [36] 39088169
    [37] 63245986
    [38] 102334155
    [39] 165580141
    [40] 267914296
    [41] 433494437
    [42] 701408733
    [43] 1134903170
    [44] 1836311903
    [45] -1323752223
*/