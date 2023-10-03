/*
1. Define a class B1 with a virtual function vf() and a non-virtual function f().
    Define both of these functions within class B1.
    Implement each function to output its name (e.g., B1::vf()).
    Make the functions public.
    Make a B1 object and call each function.

2. Derive a class D1 from B1 and override vf().
    Make a D1 object and call vf() and f() for it.

3. Define a reference to B1 (a B1&) and initialize that to the D1 object you just defined.
    Call vf() and f() for that reference.

4. Now define a function called f() for D1 and repeat 1–3. Explain the results.

5. Add a pure virtual function called pvf() to B1 and try to repeat 1–4. Explain the result.

6. Define a class D2 derived from D1 and override pvf() in D2.
    Make an object of class D2 and invoke f(), vf(), and pvf() for it.

7. Define a class B2 with a pure virtual function pvf().
    Define a class D21 with a string data member and a member function that overrides pvf();
        D21::pvf() should output the value of the string.
    Define a class D22 that is just like D21 except that its data member is an int.
    Define a function f() that takes a B2& argument and calls pvf() for its argument.
        Call f() with a D21 and a D22.
*/

 

// #include <iostream>
// using std::cout;

// class B1 {
// public:
//     virtual void vf() const { cout << "B1::vf()\n"; }
//     void f() const { cout << "B1::f()\n"; }
//     virtual void pvf() =0;
// };

// class D1 : public B1 {
// public:
//     void vf() const { cout << "D1::vf()\n"; }
//     void f() const { cout << "D1::f()\n"; }
// };

// int main(int argc, char** argv)
// {
//     // 1.
//     B1 b1;
//     b1.vf(); // prints B1::vf()
//     b1.f();  // prints B1::f()
//     // 2.
//     // D1.f() prints "B1::f()", but ONLY if:
//     // 1. B1 is a public base class of D1
//     // 2. Both D1 / B1 are structs
//     D1 d1;
//     d1.vf(); // prints D1::vf()
//     d1.f();  // prints B1::f()
//     // 3.
//     B1& b1ref = d1;
//     b1ref.vf(); // prints D1::vf()
//     b1ref.f();  // prints B1::vf()
//     // 4. When I define D1::f(), only 2 has a different printout because now D1 has an f that overrides B1's.
//     // 5. Adding a pure virtual function to B1 turns B1 and D1 into abstract classes and 1-3 don't work, as instantiating an abstract class is an error.
//     return 0;
// }

#include <iostream>
#include <string>

using std::cout;
using std::string;

class B1 {
public:
    virtual void vf() const { cout << "B1::vf()\n"; }
    void f() const { cout << "B1::f()\n"; }
    virtual void pvf() const =0;
};

class D1 : public B1 {
public:
    void vf() const { cout << "D1::vf()\n"; }
    void f() const { cout << "D1::f()\n"; }
};

class D2 : public D1 {
public:
    void pvf() const { cout << "D2::pvf()\n"; }
};

class B2 {
public:
    virtual void pvf() const =0;
};

class D21 : public B2 {
private:
    string value = "woah";
public:
    void pvf() const { cout << "D21::pvf(): " << value << '\n'; }
};

class D22 : public B2 {
private:
    int value = 20;
public:
    void pvf() const { cout << "D22::pvf(): " << value << '\n'; }
};

void f(B2& b2ref) { b2ref.pvf(); }

int main(int argc, char** argv)
{
    // 6.
    D2 d2;
    d2.vf();  // prints D1::vf()
    d2.f();   // prints D1::f()
    d2.pvf(); // prints D2::pvf()

    // 7.
    D21 d21;
    D22 d22;
    f(d21); // prints D21::pvf(): <str>
    f(d22); // prints D22::pvf(): <int>

    return 0;
}