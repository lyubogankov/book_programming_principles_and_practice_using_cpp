#include <iostream>
#include <vector>

using namespace std;

/*
Each of the 25 fragments are meant to be inserted into the scaffolding below ("My code here!!").
Each has zero or more errors.  My task is to find/remove all errors.
*/

int main()
try {
    // My code here!!

    // 1.
    // Cout << "Success!\n";  // original
    // cout << "Success!\n";  // fixed Cout -> cout (lowercase)
    // ^

    // 2.
    // cout << "Success!\n ;  // original
    // cout << "Success!\n";  // fixed: added terminating quote
    //                    ^

    // 3.
    // cout << "Success" <<  !\n"   // original
    // cout << "Success" << "!\n";  // fixed: added opening quote to !\n, as well as semicolon to end line
    //                      ^

    // 4.
    // cout <<  success  << '\n';  // original
    // cout << "success" << '\n';  // fixed - enclosed it in quotes
    //         ^       ^

    // 5.
    // string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";  // original
    // int    res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";  // fixed: variable res should be of type int, since it holds a 7, and we are putting it into vector of ints
    // ^^^^^^

    // 6.
    // vector<int> v(10);  v(5) = 7;  if (v(5) != 7) cout << "Success!\n";  // original
    // vector<int> v(10);  v[5] = 7;  if (v[5] == 7) cout << "Success!\n";  // fixed: vector element access requires [] not ().  Conditional logic changed to allow message print.
    //                      ^ ^            ^ ^ ^

    // 7.
    //                   if (cond) cout << "Success!\n"; else cout << "Fail!\n";  // original
    // bool cond = true; if (cond) cout << "Success!\n"; else cout << "Fail!\n";  // fixed: instantiated boolean variable 'cond'
    // ^^^^^^^^^^^^^^^^^

    // 8.
    // bool c = false; if ( c) cout << "Success!\n"; else cout << "fail!\n";  // original  (1 logical error)
    // bool c = false; if (!c) cout << "Success!\n"; else cout << "fail!\n";  // fixed: changed conditional logic to print desired statement
    //                     ^

    // 9.
    // string s = "ape"; boo  c = "fool" < s; if (c) cout << "Success!\n";  // original
    // string s = "ape"; bool c = "fool" > s; if (c) cout << "Success!\n";  // fixed: corrected type to bool; logical error fixed to provide correct comparison to allow print
    //                      ^            ^

    // 10.
    // string s = "ape";  if (s == "fool") cout << "Success!\n";  // original
    // string s = "ape";  if (s != "fool") cout << "Success!\n";  // fixed: corrected logic error to allow print
    //                          ^

    // 11.
    // string s = "ape";  if (s == "fool") cout <  "Success!\n";  // original
    // string s = "ape";  if (s != "fool") cout << "Success!\n";  // fixed: corrected conditional logic to allow print;  cout operator needs two chevrons
    //                          ^                ^
 
    // 12.
    // string s = "ape";  if (s + "fool") cout <  "Success!\n";  // og
    // string s = "ape";  if (s < "fool") cout << "Success!\n";  // fixed: cout operator has two chevrons;  fixed conditional so it's actually a boolean expression
    //                          ^               ^

    // 13.
    // vector<char> v(5);  for (int i=0; i<v.size(); ++i) ; cout << "Success!\n";  // og - no errors.  compiles/runs fine

    // 14.
    // vector<char> v(5);  for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n";  // og - Potential logical error - if we access elements of v using i we'll get a seg fault.  

    // 15.
    // string s = "Success!\n";  for (int i=0; i<6       ; ++i) cout << s[i];  // og
    // string s = "Success!\n";  for (int i=0; i<s.size(); ++i) cout << s[i];  // fixed: now iterating over whole string size instead of just first 6 characters
    //                                           ^^^^^^^^

    // 16.
    // if (true) then cout << "Success!\n"; else cout << "Fail!\n";  // og
    // if (true)      cout << "Success!\n"; else cout << "Fail!\n";  // fixed: "then" is not keyword within if/else block
    //           ^^^^

    // 17.
    // int x = 2000;  char c = {x};  if (c == 2000) cout << "Success!\n";  // og -- narrowing conversion
    // int x = 20;    char c = {x};  if (c == 20  ) cout << "Success!\n";  // fixed: changed numbers.  First tried 200, but that was also too big, so settled on 20.
    //         ^^^^                           ^^^^

    // 18.
    // string s = "Success!\n";  for (int i=0; i<10;       ++i) cout << s[i];  // og
    // string s = "Success!\n";  for (int i=0; i<s.size(); ++i) cout << s[i];  // fixed -- not sure if there was an issue before.  Went over string bounds but no seg fault??
    //                                           ^^^^^^^^

    // 19.
    // vector      v(5);  for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n";  // og
    // vector<int> v(5);  for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n";  // fixed: no type given for vector
    //       ^^^^^

    // 20.
    // int i=0;  int j=9;  while (i<10) ++j;  if (j<i) cout << "Success!\n";  // og
    // int i=0;  int j=9;  while (i<10) ++i;  if (j<i) cout << "Success!\n";  // fixed - incrementing i so we can break out of loop, otherwise program gets stuck!
    //                                    ^

    // 21.
    // int x = 2;  double d = 5/(x-2);  if (d == 2*x + 0.5) cout << "Success!\n";  // og
    // double x = -1.0655218370325;  double d = 5/(x-2);  if (d == 2*x + 0.5) cout << "Success!\n";  // not sure how to do this one properly... I tried solving for the roots but the double isn't properly expressing it.

    // 22.
    // string<char> s = "Success!\n";  for (int i=0; i<=10; ++i) cout << s[i];  // og
    // string       s = "Success!\n";  for (int i=0; i<=10; ++i) cout << s[i];  // fixed: removed <char> type, this isn't a vector.  Aside: tried vector<char> but that didn't work (error, conversion from 'const char [10] to non-scalar type 'std::vector<char> requested)
    //       ^^^^^^

    // 23.
    // int i=0;       while (i<10) ++j;  if (j<i) cout << "Success!\n";  // og
    // int i=0, j=0;  while (i<10) ++i;  if (j<i) cout << "Success!\n";  // fixed: j not initialized, while loop was infinite (j -> i)
    //          ^^^                  ^

    // 24.
    // int x = 2;  double d = 5/(x-2);  if (d = 2*x + 0.5) cout << "Success!\n";  // og (floating point exception (core dumped))
    // int x = 3;  double d = 5/(x-2);  if (d < 2*x + 0.5) cout << "Success!\n";  // fixed: changed x to anything except 2 to avoid floating point exception, and changed conditional to get success.
    //         ^                              ^

    // 25.
    // cin  << "Success!\n";  // og
    // cout << "Success!\n";  // fixed, cout instead of cin
    // ^^^^

    return 0;
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
    return 1;
}
catch (...) {
    cerr << "oops: unknown exception!\n";
    return 2;
}