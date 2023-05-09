/*
5.  This exercise and the next few require you to design and implement a Book class, such as you can imagine as part of software for a library.
 
    - Class Book should have members for the ISBN, title, author, and copyright date.
    - Also store data on whether or not the book is checked out.
    - Create functions for returning those data values.
    - Create functions for checking a book in and out.
    - Do simple validation of data entered into a Book;
        for example, accept ISBNs only of the form n-n-n-x where n is an integer and x is a digit or a letter. Store an ISBN as a string.

6.  Add operators for the Book class.
    Have the == operator check whether the ISBN numbers are the same for two books.
    Have != also compare the ISBN numbers.
    Have a << print out the title, author, and ISBN on separate lines.

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

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
    public:
        // constructor(s)
        Book(string _isbn, string _title, string _author, int _copyright_year);
        // accessors
        string isbn() { return _isbn; }
        string title() { return _title; }
        string author() { return _author; }
        int copyright_year() { return _copyright_year; }
        bool is_checked_out() { return _is_checked_out; }
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
        bool _is_checked_out = false;
};

bool is_valid_isbn(string isbn) {
    return true;
}

Book::Book(string isbn, string title, string author, int copyright_year) 
    : _title {title}, _author {author}
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


int main() {

    Book b1 = Book(
        "isbn",
        "Programming Principles and Practice Using C++",
        "Bjarne Stroustrup",
        2014
    );
    cout << "Checked out? " << b1.is_checked_out() << "\n";
    cout << "Checking out...\n";
    b1.check_out();
    cout << "Checked out? " << b1.is_checked_out() << "\n";
    cout << "Checking in...\n";
    b1.check_in();
    cout << "Checked out? " << b1.is_checked_out() << "\n\n";
    
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

    try {
        Book badbook = Book("isbn", "title", "author", -15);
    } catch (Book::InvalidBook) {
        cout << "Error initializing `badbook`\n";
    }

    return 0;
}