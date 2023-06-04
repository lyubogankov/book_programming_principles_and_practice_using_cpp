/*
1. Start a program to work with points, discussed in §10.4. 
    Begin by defining the data type Point that has two coordinate members x and y.

2. Using the code and discussion in §10.4, prompt the user to input seven (x,y) pairs. 
    As the data is entered, store it in a vector of Points called original_points.

3. Print the data in original_points to see what it looks like.

4. Open an ofstream and output each point to a file named mydata.txt. 
    On Windows, we suggest the .txt suffix to make it easier to look at the data with an ordinary text editor (such as WordPad).

5. Close the ofstream and then open an ifstream for mydata.txt. 
    Read the data from mydata.txt and store it in a new vector called processed_points.

6. Print the data elements from both vectors.

7. Compare the two vectors and print "Something's wrong!"
    if the number of elements or the values of elements differ.
*/

#include <iostream>
#include <vector>
using namespace std;

class Point {
    public:
        Point(int x, int y) : _x {x}, _y{y} {}
        int x() const { return _x; }
        int y() const { return _y; }
    private:
        int _x;
        int _y;
};
ostream& operator<<(ostream& os, const Point& p) {
    return os << p.x() << " " << p.y();
}
// following example from 10.9 (pg 365)
istream& operator>>(istream& is, Point& p) {
    int x, y;
    is >> x >> y;
    if (!is) return is;
    p = Point(x, y);
    return is;
}
void test_point() {
    Point p1 {1, 2};
    cout << "this is my point: " << p1 << "!\n";

    Point p2 {0, 0};
    cout << "Please enter a point: ";
    cin >> p2;
    cout << "This is the point that you entered: " << p2 << "\n";
}


int main() {
    // test_point();  // testing #1
    return 0;
}