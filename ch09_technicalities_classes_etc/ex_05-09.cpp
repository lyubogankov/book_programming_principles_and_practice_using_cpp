/*
5.  This exercise and the next few require you to design and implement a Book class, such as you can imagine as part of software for a library.
 
    - Class Book should have members for the ISBN, title, author, and copyright date.
    - Also store data on whether or not the book is checked out.
    - Create functions for returning those data values.
    - Create functions for checking a book in and out.
    - Do simple validation of data entered into a Book;
        for example, accept ISBNs only of the form n-n-n-x where n is an integer and x is a digit or a letter. Store an ISBN as a string.

6.  Add operators for the Book class.
    - Have the == operator check whether the ISBN numbers are the same for two books.
    - Have != also compare the ISBN numbers.
    - Have a << print out the title, author, and ISBN on separate lines.

7.  Create an enumerated type for the Book class called Genre.
    - Have the types be fiction, nonfiction, periodical, biography, and children.
    - Give each book a Genre and make appropriate changes to the Book constructor and member functions.

8.  Create a Patron class for the library.
    - The class will have a user’s name, library card number, and library fees (if owed).
    - Have functions that access this data, as well as a function to set the fee of the user.
    - Have a helper function that returns a Boolean (bool) depending on whether or not the user owes a fee.

9.  Create a Library class.
    - Include vectors of Books and Patrons.
    - Include a struct called Transaction. Have it include a Book, a Patron, and a Date from the chapter.
    - Make a vector of Transactions.
    - Create functions to add books to the library, add patrons to the library, and check out books.
    - Whenever a user checks out a book, have the library make sure that both the user and the book are in the library.
        If they aren’t, report an error. Then check to make sure that the user owes no fees.
        If the user does, report an error. If not, create a Transaction, and place it in the vector of Transactions.
    - Also write a function that will return a vector that contains the names of all Patrons who owe fees.

    Issue with my current implementation!
    I'm defining the books/patrons outside of the Library, pass-by-ref-ing them to `<Library>.add*()` functions.
        Then, they get `push_back()`ed onto the relevant vector.  Issue: push_back *makes a copy*, and modifying 
        the original does not change the copy.


    Two options:
    - still make the books/patrons outside the library, and store them in a vector of book/patron pointers
    - make the books/patrons within the library, and add additional function to add fee to a patron based on library card number (unique identifier)

        I'll start with option 1, since (I think) it will allow me to keep my same test code.
*/

#include <cctype>   // for isalnum / isdigit
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// #include "date_ch09.h" // for ex09
//// DATE
enum class Month { jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
class InvalidDate {};
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
Date::Date(int yy, Month mm, int dd) {
    if (1 <= int(mm) && int(mm) <= 12 && 1 <= dd && dd <= 31) {
        y = yy;
        m = mm;
        d = dd;
    } else {
        throw InvalidDate();
    }
}
void Date::add_day(int n) {
    if (d + n <= 31) {
        d += n;
    } else {
        m = Month(int(m) + (d + n) / 31);
        d = (d + n) % 31; 
    }
}
ostream& operator<<(ostream& os, const Month& m) { return os << int(m); }
ostream& operator<<(ostream& os, const Date& d) {
    return os << "Date(y=" << d.year() << ", m=" << d.month() << ", d=" << d.day() << ")";
}



// I'd prefer this was a dictionary / map, so that I could use the number to look up the label.
// This is fine for internal representation, but would not be meaningful to a user if printed to them,
//   as they'd see an integer code without any lookup table.
enum class Genre { unassigned, fiction, nonfiction, periodical, biography, childrens };
ostream& operator<<(ostream& os, const Genre& g) { return os << int(g); }

class Book {
    public:
        // constructor(s)
        Book(string isbn, string title, string author, int copyright_year); // for ex05/06
        Book(string isbn, string title, string author, int copyright_year, Genre genre); // new for ex07
        // accessors
        string isbn() const { return _isbn; }
        string title() const { return _title; }
        string author() const { return _author; }
        int copyright_year() const { return _copyright_year; }
        Genre genre() const { return _genre; }
        bool is_checked_out() const { return _is_checked_out; }
        // helper functions
        void check_out();
        void check_in();
        // for error reporting
        class InvalidBook {};
        class InvalidOperation {};
    private:
        string _isbn;
        string _title;
        string _author;
        int _copyright_year;
        Genre _genre;
        bool _is_checked_out = false;
};
bool is_valid_isbn(string isbn) {
    int hyphen_count = 0;
    for (int i=0; i<isbn.size(); i++){
        if (isbn[i] == '-') {
            hyphen_count++;
            continue;
        }
        // first three clauses: must only be digits
        //                                          // last clause: either digit or letter (alphanumeric)
        if ((hyphen_count < 3 && !isdigit(isbn[i])) || (hyphen_count == 3 && !isalnum(isbn[i])))
            return false;
    }
    return true;
}
// Q: Is there an idiomatic way to reuse constructor code between calls?
//    Constructor w/ genre's body is same as constructor w/o genre.
Book::Book(string isbn, string title, string author, int copyright_year) 
    : _title {title}, _author {author}, _genre{Genre::unassigned} // default
{
    // validate copyright year
    if (copyright_year < 0 || copyright_year > 2023) {
        cout << "Book is invalid due to copyright year.\n";
        throw InvalidBook();
    }
    _copyright_year = copyright_year;

    // validate isbn
    if (!is_valid_isbn(isbn)) {
        cout << "Book is invalid due to isbn.\n";
        throw InvalidBook();
    }
    _isbn = isbn;
}
Book::Book(string isbn, string title, string author, int copyright_year, Genre genre) 
    : _title {title}, _author {author}, _genre {genre}
{
    // validate copyright year
    if (copyright_year < 0 || copyright_year > 2023) {
        cout << "Book is invalid due to copyright year.\n";
        throw InvalidBook();
    }
    _copyright_year = copyright_year;

    // validate isbn
    if (!is_valid_isbn(isbn)) {
        cout << "Book is invalid due to isbn.\n";
        throw InvalidBook();
    }
    _isbn = isbn;
}
void Book::check_out() {
    if (_is_checked_out == true) throw InvalidOperation();
    _is_checked_out = true;
}
void Book::check_in() {
    if (_is_checked_out == false) throw InvalidOperation();
    _is_checked_out = false;
}
bool operator==(const Book& b1, const Book& b2) { return b1.isbn() == b2.isbn(); }
bool operator!=(const Book& b1, const Book& b2) { return !(b1 == b2); }
ostream& operator<<(ostream& os, const Book& b) {
    return os << b.title() << "   " << b.author() << "   " << b.isbn();
}

class Patron {
    public:
        // Constructor(s)
        Patron(string name, string librarycardnum);
        // Accessors
        string name() const { return _name; }
        string librarycardnum() const { return _librarycardnum; }
        double fee_balance() const { return _fees_owed; }
        // Helper
        bool owes_fees() const { return (_fees_owed > 0.0); }
        void change_fee_balance(double delta) { _fees_owed += delta; } // fee = +, payment = -
        class InvalidLibraryCardNum {};
    private:
        string _name;
        string _librarycardnum;
        double _fees_owed = 0.0; // all patrons start out with no fees
};
// storing library card as string to capture leading zeros!
bool is_valid_librarycardnum(string librarycardnum) {
    for (int i=0; i< librarycardnum.size(); i++) {
        if (!isdigit(librarycardnum[i]))
            return false;
    }
    return true;
}
Patron::Patron(string name, string librarycardnum)
    : _name {name}
{
    if (!is_valid_librarycardnum(librarycardnum))
        throw Patron::InvalidLibraryCardNum();
    _librarycardnum = librarycardnum;
}
bool operator==(const Patron& p1, const Patron& p2) {
    return (p1.librarycardnum() == p2.librarycardnum());
}

class Library {
    public:
        Library() {}; // all vectors start empty by default, so no need for constructor.
        void add_new_book(Book& b) { books.push_back(&b); }
        void add_new_patron(Patron& p) { patrons.push_back(&p); }
        void check_out_book(Book& b, Patron& p, Date& d);
        void check_in_book(Book& b, Patron& p, Date& d);
        bool book_in_library(Book& b);
        bool patron_in_library(Patron& p);
        vector<string> query_fee_owing_patrons();
        // for throwing errors
        class InvalidTransaction {};
    private:
        // for internal record-keeping (I wonder whether I can have a private struct defined?? let's try!)
        struct Transaction { Book& b; Patron& p; Date& d; };
        vector<Book*> books;
        vector<Patron*> patrons;
        vector<Transaction> transactions;
};
bool Library::book_in_library(Book& b) {
    for ( Book* bp : books )
        if (*bp == b)
            return true;
    return false;
}
bool Library::patron_in_library(Patron& p) {
    for ( Patron* pp : patrons )
        if (*pp == p)
            return true;
    return false;
}
void Library::check_out_book(Book& b, Patron& p, Date& d) {
    if (!book_in_library(b) || !patron_in_library(p) || b.is_checked_out() || p.owes_fees())
        throw InvalidTransaction();
    b.check_out();
    Transaction t {b, p, d};
    transactions.push_back(t);
    cout << "    patron (" << p.name() << ") checked out book (" << b << ") [" << d << "]\n";
}
void Library::check_in_book(Book& b, Patron& p, Date& d) {
    if (!book_in_library(b) || !patron_in_library(p) || !b.is_checked_out())
        throw InvalidTransaction();
    // could additionally validate that this date >= check-out date (for same book/patron)
    b.check_in();
    Transaction t {b, p, d};
    transactions.push_back(t);
    cout << "    patron (" << p.name() << ") checked in book (" << b << ") [" << d << "]\n";
}
vector<string> Library::query_fee_owing_patrons() {
    vector<string> debtornames;
    for ( Patron* pp : patrons) {
        if ((*pp).owes_fees()) {
            debtornames.push_back((*pp).name());
        }
    }
    return debtornames;
}


void test_ex05() {
    cout << "\n"
         << "---------------- EX 05 ----"
         << "\n\n";
    // create a valid Book
    Book b1 = Book(
        "0-0-0-0",
        "Programming Principles and Practice Using C++",
        "Bjarne Stroustrup",
        2014
    );

    // validate checking in/out
    cout << "Checked out? " << b1.is_checked_out() << "\n";
    cout << "Checking out...\n";
    b1.check_out();
    cout << "Checked out? " << b1.is_checked_out() << "\n";
    cout << "Checking in...\n";
    b1.check_in();
    cout << "Checked out? " << b1.is_checked_out() << "\n\n";
    
    // validate checking in/out errors
    try {
        b1.check_in();
    } catch (Book::InvalidOperation) {
        cout << "Error - can't check in a book that isn't checked out.\n";
    }
    cout << "Checking out...\n";
    b1.check_out();
    try {
        b1.check_out();
    } catch (Book::InvalidOperation) {
        cout << "Error - can't check out a book that isn't checked in.\n\n";
    }

    // validate invalid copyright year book
    try {
        Book badbook = Book("0-0-A-A", "title", "author", -15);
    } catch (Book::InvalidBook) {
        cout << "Error initializing `badbook`\n";
    }
    // validate invalid isbn book
    try {
        Book badbook = Book("0-0-A-A", "title", "author", 2003);
    } catch (Book::InvalidBook) {
        cout << "Error initializing `badbook`\n";
    }
}
void test_ex06() {
    cout << "\n"
         << "---------------- EX 06 ----"
         << "\n\n";
    Book b1 = {"0-0-0-0", "Programming Principles and Practice Using C++", "Bjarne Stroustrup", 2014};
    Book b2 {"1-1-1-B", "Fluent Python (2nd ed)", "Luciano Ramahlo", 2021};
    Book b3 ("1-1-1-B", "Copycat Chronicles", "Copy Cat", 1998);
    cout << b1 << "\n" << b2 << "\n" << b3 << "\n"
         << "\n"
         << "b1 == b2: " << (b1 == b2) << "\n"
         << "b1 != b2: " << (b1 != b2) << "\n"
         << "b2 == b3: " << (b2 == b3) << "\n"
         << "b2 != b3: " << (b2 != b3) << "\n";
}
void test_ex07() {
    cout << "\n"
         << "---------------- EX 07 ----"
         << "\n\n";
    Book b1 = {"0-0-0-0", "Programming Principles and Practice Using C++", "Bjarne Stroustrup", 2014};
    Book b2 {"1-1-1-B", "Fluent Python (2nd ed)", "Luciano Ramahlo", 2021, Genre::nonfiction};
    Book b3 ("1-1-1-B", "Copycat Chronicles", "Copy Cat", 1998, Genre::childrens);

    cout << "b1 genre: " << b1.genre() << "\n"
         << "b2 genre: " << b2.genre() << "\n"
         << "b3 genre: " << b3.genre() << "\n\n";
}
void test_ex08() {
    cout << "\n"
         << "---------------- EX 08 ----"
         << "\n\n";
    Patron p {"Lyubo", "123456789"};
    cout << p.name() << "\n" << p.librarycardnum() << "\n"
         << "Owes fees? " << p.owes_fees() << " (fee balance: $" << p.fee_balance() << ")\n\n";

    cout << p.name() << " has an overdue book... charging $1.00 fee.\n";
    p.change_fee_balance(1.00);
    cout << "Owes fees? " << p.owes_fees() << " (fee balance: $" << p.fee_balance() << ")\n\n";

    cout << p.name() << " has paid the fee.\n";
    p.change_fee_balance(-1.00);
    cout << "Owes fees? " << p.owes_fees() << " (fee balance: $" << p.fee_balance() << ")\n\n";
}
void test_ex09() {
    cout << "\n"
         << "---------------- EX 09 ----"
         << "\n\n";

    // create a library
    Library mylibrary {};

    // create 3 books,   add 2 to library
    Book b1 {"0-0-0-0", "Programming Principles and Practice Using C++", "Bjarne Stroustrup", 2014};
    Book b2 {"1-1-1-B", "Fluent Python (2nd ed)", "Luciano Ramahlo", 2021, Genre::nonfiction};
    Book b3 ("1-1-1-C", "Copycat Chronicles", "Copy Cat", 1998, Genre::childrens);
    mylibrary.add_new_book(b1);
    mylibrary.add_new_book(b2);

    // create 3 patrons, add 2 to library
    Patron p1 {"Lyubo", "123456789"};
    Patron p2 {"AlsoLyubo", "987654321"};
    Patron p3 {"NotLyubo", "192837465"};
    mylibrary.add_new_patron(p1);
    mylibrary.add_new_patron(p2);

    // p1 checkout b1 (should succeed)
    Date d1 {2023, Month::may, 12};
    mylibrary.check_out_book(b1, p1, d1);
    // p2 checkout b1 (should fail - b1 already checked out to p1)
    try {
        mylibrary.check_out_book(b1, p2, d1);
    } catch (Library::InvalidTransaction) {
        cout << "    couldn't checkout b1 to p2, it's already checked out!\n";
    }
    // p3 checkout b2 (should fail - p3 not in library)
    try {
        mylibrary.check_out_book(b2, p3, d1);
    } catch (Library::InvalidTransaction) {
        cout << "    couldn't checkout b2 to p3, p3 isn't a library member!\n";
    }
    // p2 checkout b3 (should fail - b3 not in library)
    try {
        mylibrary.check_out_book(b3, p2, d1);
    } catch (Library::InvalidTransaction) {
        cout << "    couldn't checkout b3 to p2, b3 isn't a library book!\n";
    }

    // query patrons with fee - should be empty
    vector<string> f = mylibrary.query_fee_owing_patrons();
    cout << "Number of patrons that owe fees: " << f.size() << "\n";
    // p1 gets a fee (let's say they keep b1 for too long)
    cout << "p1 balance: " << p1.fee_balance() << "\n";
    p1.change_fee_balance(1.0);
    cout << "p1 now owes library $1\n";
    cout << "p1 balance: " << p1.fee_balance() << "\n";
    // query patrons with fee - should have p1 inside
    vector<string> f2 = mylibrary.query_fee_owing_patrons();
    cout << "Number of patrons that owe fees: " << f2.size() << "\n";
    for (string n : f2)
        cout << "    debtor: " << n << "\n";
    
    // p1 checkout b2 (should fail - p1 owes fees)
    try {
        mylibrary.check_out_book(b2, p1, d1);
    } catch (Library::InvalidTransaction) {
        cout << "    couldn't checkout b2 to p1, p1 owes fees\n";
    }
    // p1 checkin b1  (should succeed)
    Date d2 {2023, Month::may, 15};
    mylibrary.check_in_book(b1, p1, d2);
    cout << "    p1 checked in b1!\n";
    // p1 checkin b1  (should fail - already checked in)
    try {
        mylibrary.check_in_book(b1, p1, d2);
    } catch (Library::InvalidTransaction) {
        cout << "    p1 could not check b1 back in, it's no longer checked out to them!\n";
    }
}

int main() {

    test_ex05();
    test_ex06();
    test_ex07();
    test_ex08();
    test_ex09();

    return 0;
}