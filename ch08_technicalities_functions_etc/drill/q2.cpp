#include <iostream>

using namespace std;


void swap_v (int        a, int        b){ int temp; temp = a, a=b; b=temp; }
void swap_r (int&       a, int&       b){ int temp; temp = a, a=b; b=temp; }

//// won't compile with this function -- can't change const refs!
// void swap_cr(const int& a, const int& b){ int temp; temp = a, a=b; b=temp; }

int main() {

    /*
    Will it swap?

    swap_v: no, since it's pass-by-value (operates on copies) and doesn't return anything
    swap_r: yes
        however:
        - won't compile when literal values are passed as arguments
        - doesn't like the swap on the const int values
    swap_cr: no, since it's a const-reference
    */
    int x = 7;
    int y = 9;
    swap_r(x,y);
    cout << x << " " << y << "\n";
    // swap_r(7,9);

    const int cx = 7;
    const int cy = 9;
    // swap_r(cx,cy);
    cout << cx << " " << cy << "\n";
    // swap_r(7.7,9.9);
    
    double dx = 7.7;
    double dy = 9.9;
    //swap_r(dx, dy);
    cout << dx << " " << dy << "\n";
    // swap_r(7.7,9.9);

    return 0;
}