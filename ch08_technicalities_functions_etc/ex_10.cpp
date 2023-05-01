/* 10. Write a function maxv() that returns the largest element of a vector argument. */

#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int maxv(vector<int>& v) {
    int largest_seen = numeric_limits<int>::min();
    for (int x : v)
        if (x > largest_seen)
            largest_seen = x;
    return largest_seen;
}

int main() {

    vector<int> v = {1, 2, 3, 4, 5};
    cout << maxv(v) << "\n";

    return 0;
}