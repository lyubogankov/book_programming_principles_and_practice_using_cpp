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
    Have the types be fiction, nonfiction, periodical, biography, and children.
    Give each book a Genre and make appropriate changes to the Book constructor and member functions.

8.  Create a Patron class for the library.
    The class will have a user’s name, library card number, and library fees (if owed).
    Have functions that access this data, as well as a function to set the fee of the user.
    Have a helper function that returns a Boolean (bool) depending on whether or not the user owes a fee.

9.  Create a Library class.
    Include vectors of Books and Patrons.
    Include a struct called Transaction. Have it include a Book, a Patron, and a Date from the chapter.
    Make a vector of Transactions. Create functions to add books to the library, add patrons to the library, and check out books.
    Whenever a user checks out a book, have the library make sure that both the user and the book are in the library.
    If they aren’t, report an error. Then check to make sure that the user owes no fees.
    If the user does, report an error. If not, create a Transaction, and place it in the vector of Transactions.
    Also write a function that will return a vector that contains the names of all Patrons who owe fees.
*/

#include <cctype>   // for isalnum / isdigit
#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

// ex06 - operators
bool operator==(const Book& b1, const Book& b2) { return b1.isbn() == b2.isbn(); }
bool operator!=(const Book& b1, const Book& b2) { return !(b1 == b2); }
ostream& operator<<(ostream& os, const Book& b) {
    return os << b.title() << "\n" << b.author() << "\n" << b.isbn() << "\n";
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

}
void test_ex09() {

}

int main() {

    test_ex05();
    test_ex06();
    test_ex07();
    test_ex08();
    test_ex09();

    return 0;
}