1. Create three files: `my.h`, `my.cpp`, and `use.cpp`.

    The header file `my.h` contains:

    ``` C++
    extern int foo;
    void print_foo();
    void print(int);
    ```

    The source code file `my.cpp`:
    - `#include`s `my.h` and `std_lib_facilities.h`
    - defines `print_foo()` to print the value of `foo` using `cout`
    - defines `print(int i)` to print the value of `i` using `cout`

    The source code file `use.cpp`:
    - `#include`s my.h
    - defines `main()`
        - sets the value of foo to 7
        - prints it using `print_foo()`
        - prints the value of 99 using `print()`
        
    Note that `use.cpp` does not `#include std_lib_facilities.h` as it doesn’t directly use any of those facilities.

    Get these files compiled and run. On Windows, you need to have both use.cpp and my.cpp in a project and use { char cc; cin>>cc; } in use.cpp to be able to see your output. Hint: You need to #include <iostream> to use cin.

    ***Note:*** *This wasn't explained in the textbook, but it seems like each file has its own global scope?  Removing `extern inf foo` from `my.h` causes compiler to throw error (w/in `use.cpp`, that `foo` isn't declared in scope.  Using `extern` in the header file allows the two `.cpp` files to "share" the global variable defined in `my.cpp`.*


2. Write three functions `swap_v(int,int)`, `swap_r(int&,int&)`, and `swap_cr(const int&, const int&)`. 

    Each should have the body

    ``` C++
    { int temp; temp = a, a=b; b=temp; }
    ```

    where `a` and `b` are the names of the arguments.

    Try calling each swap like this:

    ``` C++ 
    int x = 7;
    int y =9;
    swap_?(x,y);                      // replace ? by v, r, or cr
    swap_?(7,9);
    const int cx = 7;
    const int cy = 9;
    swap_?(cx,cy);
    swap_?(7.7,9.9);
    double dx = 7.7;
    double dy = 9.9;
    swap_?(dx,dy);
    swap_?(7.7,9.9);
    ```

    Which functions and calls compiled, and why? After each swap that compiled, print the value of the arguments after the call to see if they were actually swapped. If you are surprised by a result, consult §8.6.


3. Write a program using a single file containing three namespaces X, Y, and Z so that the following main() works correctly:

    ``` C++
    int main()
    {
            X::var = 7;
            X::print();                  // print X’s var
            using namespace Y;
            var = 9;
            print();                       // print Y’s var
            {          using Z::var;
                        using Z::print;
                        var = 11;
                        print();           // print Z’s var
            }
            print();                      // print Y’s var
            X::print();                // print X’s var
    }
    ```

    Each namespace needs to define a variable called var and a function called print() that outputs the appropriate var using cout.