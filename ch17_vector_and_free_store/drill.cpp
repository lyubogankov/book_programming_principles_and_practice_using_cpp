/*
 This drill has two parts. The first exercises/builds your understanding of free-store-allocated arrays and contrasts arrays with vectors:

1. Allocate an array of ten ints on the free store using new.
2. Print the values of the ten ints to cout.
3. Deallocate the array (using delete[]).
4. Write a function print_array10(ostream& os, int* a) that prints out the values of a (assumed to have ten elements) to os.
5. Allocate an array of ten ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.
6. Allocate an array of 11 ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.
7. Write a function print_array(ostream& os, int* a, int n) that prints out the values of a (assumed to have n elements) to os.
8. Allocate an array of 20 ints on the free store; initialize it with the values 100, 101, 102, etc.; and print out its values.
9. Did you remember to delete the arrays? (If not, do it.)
10. Do 5, 6, and 8 using a vector instead of an array and a print_vector() instead of print_array().

The second part focuses on pointers and their relation to arrays. Using print_array() from the last drill:

1. Allocate an int, initialize it to 7, and assign its address to a variable p1.
2. Print out the value of p1 and of the int it points to.
3. Allocate an array of seven ints; initialize it to 1, 2, 4, 8, etc.; and assign its address to a variable p2.

4. Print out the value of p2 and of the array it points to.

5. Declare an int* called p3 and initialize it with p2.

6. Assign p1 to p2.

7. Assign p3 to p2.

8. Print out the values of p1 and p2 and of what they point to.

9. Deallocate all the memory you allocated from the free store.

10. Allocate an array of ten ints; initialize it to 1, 2, 4, 8, etc.; and assign its address to a variable p1.

11. Allocate an array of ten ints, and assign its address to a variable p2.

12. Copy the values from the array pointed to by p1 into the array pointed to by p2.

13. Repeat 10–12 using a vector rather than an array.
*/

#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// ----------------------------------------------------------------------------
// PART ONE
//
// 4.
void print_array10(ostream& os, int* a) {
    for (int i=0; i<10; i++)
        os << a[i] << " ";
    os << '\n';
}

void one_thru_four() {
    // 1.
    int size = 10;
    int* myarr = new int[size];
    // initialization
    for(int i=0; i<size; i++)
        myarr[i] = size - i;

    // 2.
    for(int i=0; i<size; i++)
        cout << myarr[i] << " ";
    cout << "\n";
    print_array10(cout, myarr);

    // 3.
    delete[] myarr;
}

// ----------------------------------------------
// 7.
void print_array(ostream& os, int* a, int size) {
    for (int i=0; i<size; i++)
        os << a[i] << " ";
    os << '\n';
}

// parts 5-9
void allocate_and_print(int size) {
    int* myarr = new int[size];
    for (int i=0; i<size; i++)
        myarr[i] = 100 + i;
    print_array(cout, myarr, size);
    delete[] myarr; // 9. whoops, had forgotten to delete!
}

// ----------------------------------------------
// 10.
void print_vector(ostream& os, vector<int>& v) {
    for (int element : v)
        os << element << " ";
    os << '\n';
}
void allocate_and_print_vector(int size) {
    vector<int> v;
    for (int i=0; i<size; i++)
        v.push_back(100 + i);
    print_vector(cout, v);
}

// ----------------------------------------------------------------------------
// PART TWO
//

void part_two_array() {
    cout << "\n\n---- PART TWO\n";
    
    // 1.
    int i1 = 7;
    int* p1 = &i1;
    // 2.
    cout << "i1: " << i1 << "\np1: " << p1 << "\n";
    // 3.
    int p2_size = 7;
    int* p2 = new int[p2_size];
    for (int i=0; i<p2_size; i++)
        p2[i] = pow(2, i+1);
    cout << "p2: ";
    print_array(cout, p2, p2_size);
    cout << "p2 address: " << p2 << "\n";

    // cleanup
    delete[] p2;
}
// void part_two_vector() {
// }


int main() {

    // Part One
    one_thru_four();
    allocate_and_print(10); // 5.
    allocate_and_print(11); // 6.
    allocate_and_print(20); // 8.
    // 10.
    allocate_and_print_vector(10);
    allocate_and_print_vector(11);
    allocate_and_print_vector(20);
    
    // Part Two

    return 0;
}