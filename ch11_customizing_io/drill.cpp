/*  
# Working with stream manipulators

1. Start a program called Test_output.cpp. Declare an integer birth_year and assign it the year you were born.

2. Output your birth_year in decimal, hexadecimal, and octal form.

3. Label each value with the name of the base used.

4. Did you line up your output in columns using the tab character? If not, do it.

5. Now output your age.

6. Was there a problem? What happened? Fix your output to decimal.

7. Go back to 2 and cause your output to show the base for each output.

8. Try reading as octal, hexadecimal, etc.:

    cin >> a >>oct >> b >> hex >> c >> d;
    cout << a << '\t'<< b << '\t'<< c << '\t'<< d << '\n' ;

    Run this code with the input

    1234 1234 1234 1234

    Explain the results.
    - First input interpreted as decimal, second as octal, last two as hex
        (since we didn't specify a new base between c/d).
    - They're all printed without bases though?
        YES - the INPUTS are interpreted as hex/octal, and are OUTPUT as decimal equivalents.

9. Write some code to print the number 1234567.89 three times, 
    first using defaultfloat, then fixed, then scientific forms.
    Which output form presents the user with the most accurate representation? Explain why.

        Output:
        defaultfloat: 1.23457e+06
        fixed:        1234567.890000
        scientific:   1.234568e+06

        - Fixed, bc it shows the greatest amount of precision (number of decimal points).

10. Make a simple table including last name, first name, telephone number, and email address 
    for yourself and at least five of your friends. 
    Experiment with different field widths until you are satisfied that the table is well presented.
*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Person {
    string firstname;
    string lastname;
    string phonenumber;
};

int main() {

    // 1
    int birth_year = 1891;
    // 7
    cout << showbase;
    // 2, 3, 4
    cout << "Birth year (int):\t" << birth_year << '\n'
         << "           (hex):\t" << hex << birth_year << '\n'
         << "           (oct):\t" << oct << birth_year << '\n'; 
    // 5, 6
    int age = 132;
    cout << "My age: " << age << '\n'; // this will print out age in octal!
    cout << "My age (dec): " << dec << age << '\n';

    // // 8
    // int a, b, c, d;
    // cin >> a >> oct >> b >> hex >> c >> d;
    // cout << a << '\t' << b << '\t' << c << '\t' << d << '\n' ;

    // 9
    double n = 1234567.89;
    cout << "defaultfloat: " << defaultfloat << n << '\n'
         << "fixed:        " << fixed << n << '\n'
         << "scientific:   " << scientific << n << '\n';

    // 10
    vector<Person> folks {
        Person {"Kokoro", "Heru",  "+1 202-918-2132"},
        Person {"Winona", "Oliva", "+1 505-768-6692"},
        Person {"Dafne", "Rorie", "+1 505-646-5486"},
        Person {"Ea", "Behiye", "+359 999 977 960"},
        Person {"Leni", "Nita", "+1 205-933-6884"}
    };
    int longest_firstname_size=0, longest_lastname_size=0, longest_phonenum_size=0;
    for (Person& p : folks) {
        longest_firstname_size = max(longest_firstname_size, int(p.firstname.length()));
        longest_lastname_size = max(longest_lastname_size, int(p.lastname.length()));
        longest_phonenum_size = max(longest_phonenum_size, int(p.phonenumber.length()));
    }

    // header:
    // print '------...'
    for (int i=0; i<(longest_firstname_size + longest_lastname_size + longest_phonenum_size + 4 + 6); ++i) cout << '-';
    cout << '\n';
    // print out column names
    cout << "| " << setw(longest_firstname_size) << "first" 
        << " | " << setw(longest_lastname_size) << "last"
        << " | " << setw(longest_phonenum_size) << "phone"
        << " |\n";
    // print '------...'
    for (int i=0; i<(longest_firstname_size + longest_lastname_size + longest_phonenum_size + 4 + 6); ++i) cout << '-';
    cout << '\n';
    // body
    for (Person& p : folks) {
        cout << "| " << setw(longest_firstname_size) << p.firstname
            << " | " << setw(longest_lastname_size) << p.lastname
            << " | " << setw(longest_phonenum_size) << p.phonenumber
            << " |\n";
    }
    // footer
    for (int i=0; i<(longest_firstname_size + longest_lastname_size + longest_phonenum_size + 4 + 6); ++i) cout << '-';
    cout << '\n';

    return 0;
}