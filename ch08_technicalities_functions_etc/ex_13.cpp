/*
13. Write a function that takes a vector<string> argument 
    and returns a vector<int> containing the number of characters in each string.
    
    Also find the longest and the shortest string and the lexicographically first and last string.
    
    How many separate functions would you use for these tasks? Why?

    ---
    (simple) options exist along a continuum:

    All in one function, returned as a struct or by reference
        Pros: similar computations can be grouped / done together - slightly more computationally efficient
        Cons: messy interface!  more difficult to use, and to maintain.

    Each operation as a separate function (num char per str, longest str, shortest str, lexo first string, lexo last string)
        Pros: cleaner, easier to use/maintain
        Cons: no grouping = repeated work.

    I like the cleaner option.  Unless it's shown to be a bottleneck or is being used in a performance-critical application, simpler is better.        
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

vector<int> char_per_string(const vector<string>& strings) {
    vector<int> char_counts;
    for (string s : strings)
        char_counts.push_back(s.size());
    return char_counts;
}
int longest_string(const vector<string>& strings) {
    int longest = 0;
    for (int char_count : char_per_string(strings))
        if (char_count > longest)
            longest = char_count;
    return longest;
}
int shortest_string(const vector<string>& strings) {
    int shortest = numeric_limits<int>::max();
    for (int char_count : char_per_string(strings))
        if (char_count < shortest)
            shortest = char_count;
    return shortest;
}
string lexographically_first_str(const vector<string>& strings) {
    vector<string> s = strings;
    sort(s.begin(), s.end());
    return s[0];
}
string lexographically_last_str(const vector<string>& strings) {
    vector<string> s = strings;
    sort(s.begin(), s.end());
    return s[s.size()-1];
}

int main() {
    vector<string> s = {"short", "very very very very long", "zzzzzzzzzz", "aaaaaaaaaa"};

    vector<int> cps = char_per_string(s);
    for(int i=0; i<s.size(); i++)
        cout << s[i] << "    " << cps[i] << "\n";
    
    cout << longest_string(s) << "\n";
    cout << shortest_string(s) << "\n";
    cout << lexographically_first_str(s) << "\n";
    cout << lexographically_last_str(s) << "\n";

    return 0;
}