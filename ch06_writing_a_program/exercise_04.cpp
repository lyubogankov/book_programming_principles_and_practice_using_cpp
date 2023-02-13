/*
4. Define a class Name_value that holds a string and a value.
   Rework exercise 19 in Chapter 4 to use a vector<Name_value> instead of two vectors.


   For reference:

   ch4, ex19
   Write a program where you first enter a set of name-and-value pairs, such as "Joe 17" and "Barbara 22".
   For each pair, add the name to a vector called names and the number to a vector called scores.
   Terminate input with "NoName 0".  Check that each name is unique and terminate with an error message
   if a name is entered twice.  Write out all the (name,score) pairs, one per line.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// (new)
class NameAndValue{
public:
   string name;
   int value;
   // constructor
   NameAndValue(string n, int v)
      :name(n), value(v) { }
};

int main() {

   vector<NameAndValue> pairs;  // (new)
   string name = "";
   int value = 0;
   char peek = ' ';

   // input loop
   cout << "Please enter a set of name-and-value pairs of the form {name} {value} (ex: Joe 17).\n"
        << "Note: names must be unique!\n"
        << "When you are done entering name-value pairs, please enter NoName 0 to terminate entry.\n\n";
   while(true) {
      // TODO make this more robust
      cin >> name >> value;
      // cin >> name;
      // cin >> peek;
      // if (peek - '0' > 9 || peek - '0' < 0) {
      //    cout << "\nInvalid entry -- must be {name} {value} pairs.\n";
      //    continue;
      // }
      // cin.putback(peek);
      // cin >> value;
      // if (!cin) {
      //    cout << "Putting back value as char?\n";
      //    cin.putback(value);
      //    continue;
      // }
      if (name == "NoName" && value == 0)
         break;
      // ensure name is not already present (new)
      for (NameAndValue pair : pairs) {
         if (name == pair.name) {
            cout << "Error - duplicate name entered.  Terminating program.\n";
            return 0;
         }
      }
      pairs.push_back(NameAndValue(name, value));
   }

   // once input loop is complete, print out all name/value pairs
   cout << "\n\n"
        << "Here are all the name, value pairs you entered:\n";
   // (new)
   for (NameAndValue pair : pairs)
      cout << pair.name << " " << pair.value << "\n";
}