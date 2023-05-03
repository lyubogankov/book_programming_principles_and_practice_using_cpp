/*
This drill simply involves getting the sequence of versions of `Date` to work.
For each version define a `Date` called `today` initialized to June 25, 1978.
Then, define a `Date` called `tomorrow` and give it a value by copying `today` into it and increasing its day by one using `add_day()`.
Finally, output `today` and `tomorrow` using a `<<` defined as in §9.8.

Your check for a valid date may be very simple. Feel free to ignore leap years.
However, don’t accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
Test each version with at least one invalid date (e.g., 2004, 13, –5).

*/
#include <iostream>
using namespace std;

// shared
enum class Month { jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
ostream& operator<<(ostream& os, const Month& m) { return os << int(m); }
class InvalidDate {};

// 1. The version from §9.4.1
// --------------------------
struct Date_1 {
    int y;
    int m;
    int d;
};
void init_date_1(Date_1& dd, int y, int m, int d) {
    // check that (y, m, d) is a valid date.  If so, use it to initialize dd.
    if (1 <= m && m <= 12 && 1 <= d && d <= 31) {
        dd.y = y;
        dd.m = m;
        dd.d = d;
    } else {
        throw InvalidDate();
    }
}
void add_day_1(Date_1& dd, int n) {
    // increase dd by n days
    if (dd.d + n <= 31) {
        dd.d += n;
    } else {
        dd.m += (dd.d + n) / 31;
        dd.d  = (dd.d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, const Date_1& d) {
    return os << "Date_1(y=" << d.y << ", m=" << d.m << ", d=" << d.d << ")";
}


// 2. The version from §9.4.2
// --------------------------
struct Date_2 {
    int y, m, d;
    Date_2(int yy, int mm, int dd);
    void add_day(int n);
};
Date_2::Date_2(int yy, int mm, int dd) {
    // check that (y, m, d) is a valid date.  If so, use it to initialize dd.
    if (1 <= mm && mm <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date_2::add_day(int n) {
    // add n days to current date -- since this is being called on an object, we have access to its state
    if (d + n <= 31) {
        d += n;
    } else {
        m += (d + n) / 31;
        d  = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, const Date_2& d) {
    return os << "Date_2(y=" << d.y << ", m=" << d.m << ", d=" << d.d << ")";
}


// 3. The version from §9.4.3
// --------------------------
class Date_3 {
    int y, m, d;
public:
    Date_3(int yy, int mm, int dd);
    void add_day(int n);
    int year() { return y; }
    int month() { return m; }
    int day() { return d; }
};
Date_3::Date_3(int yy, int mm, int dd) {
    // check that (y, m, d) is a valid date.  If so, use it to initialize dd.
    if (1 <= mm && mm <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date_3::add_day(int n) {
    // add n days to current date -- since this is being called on an object, we have access to its state
    if (d + n <= 31) {
        d += n;
    } else {
        m += (d + n) / 31;
        d  = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, Date_3& d) {
    return os << "Date_3(y=" << d.year() << ", m=" << d.month() << ", d=" << d.day() << ")";
}


// 4. The version from §9.7.1
// --------------------------
class Date_4 {
public:
    Date_4(int y, Month m, int d);
    void add_day(int n);
    int year() { return y; }
    Month month() { return m; }
    int day() { return d; }
private:
    int y;
    Month m;
    int d;
};
Date_4::Date_4(int yy, Month mm, int dd) {
    // check that (y, m, d) is a valid date.  If so, use it to initialize dd.
    if (1 <= int(mm) && int(mm) <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date_4::add_day(int n) {
    // add n days to current date -- since this is being called on an object, we have access to its state
    if (d + n <= 31) {
        d += n;
    } else {
        m = Month(int(m) + (d + n) / 31);
        d = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, Date_4& d) {
    return os << "Date_4(y=" << d.year() << ", m=" << d.month() << ", d=" << d.day() << ")";
}


// 5. The version from §9.7.4
// --------------------------
class Date_5 {
public:
    Date_5(int yy, Month mm, int dd);

    int year() const { return y; }
    Month month() const { return m; }
    int day() const { return d; }
    
    void add_day(int n);
private:
    int y;
    Month m;
    int d;
};
Date_5::Date_5(int yy, Month mm, int dd) {
    if (1 <= int(mm) && int(mm) <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date_5::add_day(int n) {
    if (d + n <= 31) {
        d += n;
    } else {
        m = Month(int(m) + (d + n) / 31);
        d = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, const Date_5& d) {
    return os << "Date_5(y=" << d.year() << ", m=" << d.month() << ", d=" << d.day() << ")";
}


int main() {

    // 1
    cout << "\n\n--- Date_1 ----------\n\n";
    Date_1 today_1;
    init_date_1(today_1, 1978, 6, 25);
    Date_1 tomorrow_1 = today_1;
    add_day_1(tomorrow_1, 1);
    cout << "   today: " << today_1 << "\n"
         << "tomorrow: " << tomorrow_1 << "\n";
    // testing the add_day rollover logic
    Date_1 d2;
    init_date_1(d2, 1978, 7, 30);
    cout << "d2:          " << d2 << "\n";
    add_day_1(d2, 5);
    cout << "d2 + 5 days: " << d2 << "\n";
    // testing exception
    try {
        Date_1 e1;
        init_date_1(e1, 2004, 13, -5);
    } catch (InvalidDate) {
        cout << "Initializing e1 failed.\n";
    }

    // 2
    cout << "\n\n--- Date_2 ----------\n\n";
    Date_2 today_2 { 1978, 6, 25};
    Date_2 tomorrow_2 = today_2;
    tomorrow_2.add_day(1);
    cout << "   today: " << today_2 << "\n"
         << "tomorrow: " << tomorrow_2 << "\n";
    try {
        Date_2 e2 {2004, 13, -5};
    } catch (InvalidDate) {
        cout << "Initializing e2 failed.\n";
    }

    // 3
    cout << "\n\n--- Date_3 ----------\n\n";
    Date_3 today_3 { 1978, 6, 25};
    Date_3 tomorrow_3 = today_3;
    tomorrow_3.add_day(1);
    cout << "   today: " << today_3 << "\n"
         << "tomorrow: " << tomorrow_3 << "\n";
    try {
        Date_3 e3 {2004, 13, -5};
    } catch (InvalidDate) {
        cout << "Initializing e3 failed.\n";
    }

    // 4
    cout << "\n\n--- Date_4 ----------\n\n";
    Date_4 today_4 { 1978, Month::jun, 25};
    Date_4 tomorrow_4 = today_4;
    tomorrow_4.add_day(1);
    cout << "   today: " << today_4 << "\n"
         << "tomorrow: " << tomorrow_4 << "\n";
    try {
        Date_4 e4 {2004, Month(13), 1};
    } catch (InvalidDate) {
        cout << "Initializing e4 failed.\n";
    }

    // 5
    cout << "\n\n--- Date_5 ----------\n\n";
    Date_5 today_5 { 1978, Month::jun, 25};
    Date_5 tomorrow_5 = today_5;
    tomorrow_5.add_day(1);
    cout << "   today: " << today_5 << "\n"
         << "tomorrow: " << tomorrow_5 << "\n";
    try {
        Date_5 e5 {2004, Month(13), 1};
    } catch (InvalidDate) {
        cout << "Initializing e5 failed.\n";
    }
    cout << "\n\n";

    return 0;
}