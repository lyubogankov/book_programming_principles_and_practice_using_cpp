/*
11. Write a function that, given a vector argument:
    - finds the smallest and the largest element
    - computes the mean and the median.
    Do not use global variables.
    
    Either return a struct containing the results or pass them back through reference arguments.
    Which of the two ways of returning several result values do you prefer and why?
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct stats { int smallest; int largest; double median; double mean; };

stats compute_stats(const vector<int>& v) {
    int largest_seen = numeric_limits<int>::min();
    int smallest_seen = numeric_limits<int>::max();
    int sum = 0;

    double median = 0;
    vector<int> sorted = v;
    sort(sorted.begin(), sorted.end());
    int mid = v.size() / 2;
    if (v.size() % 2 == 0) {
        median = double(sorted[mid] + sorted[mid - 1]) / 2;
    } else {
        median = sorted[mid];
    }

    for (int x : v) {
        if (x > largest_seen)
            largest_seen = x;
        if (x < smallest_seen)
            smallest_seen = x;
        sum += x;
    }
    double mean = double(sum) / v.size();

    struct stats ret = {smallest_seen, largest_seen, median, mean};
    return ret;
}

int main() {

    vector<int> data = {5, 1, 2, 3};
    struct stats s = compute_stats(data);

    cout << s.smallest << " " << s.largest << " " << s.median << " " << s.mean << "\n";

    return 0;
}