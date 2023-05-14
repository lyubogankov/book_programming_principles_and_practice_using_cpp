#include <iostream>
using namespace std;

enum class Month { jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
class Date {
    public:
        Date(int yy, Month mm, int dd);
        int year() const { return y; }
        Month month() const { return m; }
        int day() const { return d; }
        void add_day(int n);
    private:
        int y;
        Month m;
        int d;
};
class InvalidDate {};

ostream& operator<<(ostream& os, const Date& d);