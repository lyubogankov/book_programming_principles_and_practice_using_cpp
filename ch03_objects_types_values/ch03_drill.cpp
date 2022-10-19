// instead of including std_lib_facilities.h
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
inline void keep_window_open() { char ch; cin >> ch; } // only CTRL-D stops this? [linux]
inline void simple_error(string s)  // write ``error: s`` and exit program
{
    cerr << "error: " << s << '\n';
    keep_window_open();     // for some Windows environments
    exit(1);
}

// my code
int main() {
    cout << "Enter the name of the person to whom you want to write (followed by ENTER): ";
    string recipient_name = "???";
    cin >> recipient_name;
    cout << "\n\n~~~~~~~~~~\n"
         << "Dear " << recipient_name << ",\n"
         << "How are you?  I am fine, I miss you.\n"
         << "\n";

    cout << "Enter the name of a mutual friend (followed by ENTER): ";
    string friend_name = "???";
    cin >> friend_name;
    cout << "\n\n~~~~~~~~~~\n"
         << "Have you seen " << friend_name << " lately?\n"
         << "\n";

    cout << "Please enter the sex of the mutual friend (followed by ENTER): ";
    char friend_sex = 0;
    cin >> friend_sex;
    cout << "\n\n~~~~~~~~~~\n"
         << "If you see " << friend_name << " please ask ";
    if(friend_sex == 'm')
        cout << "him";
    else if(friend_sex == 'f')
        cout << "her";
    cout << " to call me.\n"
         << "\n";

    cout << "Please enter the age of " << recipient_name << " (followed by ENTER): ";
    int age = -1;
    cin >> age;
    cout << "\n\n~~~~~~~~~~\n"
         << "I hear you just had a birthday and you are " << age << " years old.\n";
    if(age <= 0 || age > 110)
        simple_error("you're kidding!");
    else if(age < 12)
        cout << "Next year you will be " << age + 1 << "\n";
    else if(age == 17)
        cout << "Next year you will be able to vote.\n";
    else if(age > 70)
        cout << "I hope you are enjoying retirement.\n";
    cout << "\n"
         << "Yours sincerely,"
         << "\n\n"
         << "lyubo"
         << "\n";
}
