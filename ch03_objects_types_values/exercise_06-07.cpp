#include<iostream>
#include<string>
using namespace std;

template <class T> const T& print_sorted(T& one, T& two, T&  three);
template <class T> const T& print_sorted(T& one, T& two, T&  three) {
    // input: three values come in unknown order
    // want:  printed order pos_one <= pos_two <= pos_three
    if(one > two)
        swap(one, two);
    if(two > three)
        swap(two, three);
        if(one > two)
            swap(one, two);
    cout << one << ", " << two << ", " << three << "\n\n";
}

int main() {

    // had both the int and string vars named "one, two, three" but got a compiler error.
    // it seems that I can't re-make a variable of a different type.
    // not sure what would happen if I tried to make one of same type.
    cout << "Please enter three integers: ";
    int ione, itwo, ithree;
    cin >> ione >> itwo >> ithree;
    print_sorted(ione, itwo, ithree);

    cout << "Please enter three strings: ";
    string one, two, three;
    cin >> one >> two >> three;
    print_sorted(one, two, three);

    return 0;
}
