/*
1. What is the output format of pointer values on your implementation? Hint: Don’t read the documentation.

Based on the drill, it's in hexadecimal - 12 hex digits
    0x7ffc8bed1b84

2. How many bytes are there in an int? In a double? In a bool? Do not use sizeof except to verify your answer.

    Preliminary answers, based on looking at addresses:
        int:    4 bytes
        double: 8 bytes
        bool:   1 byte

    Using `sizeof()` operator confirms the findings above!!
*/

#include <iostream>
using namespace std;

int main() {

    /* Investigating int (this is the printout)
        Address of 1st element of p (printing p):     0x5562d1a54e70
        Address of 1st element of p (printing &p[0]): 0x5562d1a54e70
        Address of 2nd element of p (         &p[1]): 0x5562d1a54e74
        Difference between 1st/2nd elements:          1
    */
    int size = 2;
    int* p = new int[size];
    for (int i=0; i<size; i++)
        p[i] = 0;

    cout << "Address of 1st element of p (printing p):     " << p     << '\n'
         << "Address of 1st element of p (printing &p[0]): " << &p[0] << '\n'
         << "Address of 2nd element of p (         &p[1]): " << &p[1] << '\n'
         << "Difference between 1st/2nd elements:          " << &p[1] - &p[0] << '\n';

    /* Investigating double
        Address of 1st element of pd (printing pd):     0x555dfbd302a0
        Address of 1st element of pd (printing &pd[0]): 0x555dfbd302a0
        Address of 2nd element of pd (         &pd[1]): 0x555dfbd302a8
        Difference between 1st/2nd elements:            1
    */
    double* pd = new double[size];
    for (int i=0; i<size; i++)
        pd[i] = 0;
    cout << "Address of 1st element of pd (printing pd):     " << pd     << '\n'
         << "Address of 1st element of pd (printing &pd[0]): " << &pd[0] << '\n'
         << "Address of 2nd element of pd (         &pd[1]): " << &pd[1] << '\n'
         << "Difference between 1st/2nd elements:            " << &pd[1] - &pd[0] << '\n';

    /* Investigating bool
        Address of 1st element of pb (printing pb):     0x555dfbd302c0
        Address of 1st element of pb (printing &pb[0]): 0x555dfbd302c0
        Address of 2nd element of pb (         &pb[1]): 0x555dfbd302c1
        Difference between 1st/2nd elements:            1
    */
    bool* pb = new bool[size];
    for (int i=0; i<size; i++)
        pb[i] = 0;
    cout << "Address of 1st element of pb (printing pb):     " << pb     << '\n'
         << "Address of 1st element of pb (printing &pb[0]): " << &pb[0] << '\n'
         << "Address of 2nd element of pb (         &pb[1]): " << &pb[1] << '\n'
         << "Difference between 1st/2nd elements:            " << &pb[1] - &pb[0] << '\n';

    cout << "\n\nChecking our work:\n"
         << "int:    " << sizeof(int) << '\n'
         << "double: " << sizeof(double) << '\n'
         << "bool:   " << sizeof(bool) << '\n';

    return 0;
}