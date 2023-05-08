/*
2. Design and implement a Name_pairs class holding (name,age) pairs where name is a string and age is a double. 
   Represent that as a vector<string> (called name) and a vector<double> (called age) member.
   
   Provide an input operation read_names() that reads a series of names.
   Provide a read_ages() operation that prompts the user for an age for each name.
   Provide a print() operation that prints out the (name[i],age[i]) pairs (one per line) in the order determined by the name vector.
   Provide a sort() operation that sorts the name vector in alphabetical order and reorganizes the age vector to match.
   
   Implement all “operations” as member functions. Test the class (of course: test early and often).


3. Replace Name_pair::print() with a (global) operator << and define == and != for Name_pairs.


NOTE -- this is an object-oriented version of Ch8, ex07-08.  Re-using my code here :)
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const bool TEST_PRINT = false;

ostream& operator<<(ostream&os, vector<double> vd) {
   for (double element : vd)
      os << element << "  ";
   return os;
}

class NamePairs {
   public:
      void read_names();
      void read_ages();
      void print();
      void sort();

      struct Pair;
      int size() const;
      Pair get_pair(int index) const;
   private:
      vector<string> names;
      vector<double> members;
};
// ex 02
void NamePairs::read_names() {
   string name_input = "";
   cout << "Please input names (type 'quit' once done):\n";
   while(true) {
      cout << "> ";
      cin >> name_input;
      if(name_input == "quit") break;
      names.push_back(name_input);
   }
}
void NamePairs::read_ages() {
   int age_input = 0;
   cout << "\n";
   for (string name : names) {
      cout << "How old is " << name << "? ";
      cin >> age_input;
      members.push_back(age_input);
   }
   cout << "\n";
}
void NamePairs::sort() {
   vector<string> original_name_order = names;
   // sort the names into alphabetical order
   std::sort(names.begin(), names.end());
   // use original order to now sort the ages (`members`) in-place!
   int num_pairs = names.size();
   for (int i=0; i<num_pairs; i++) {
      if (TEST_PRINT)
         cout << "\t[" << i << "] " << names[i] << "\n";
      for (int j=0; j<num_pairs; j++) {
         if (TEST_PRINT)
            cout << "\t\t[" << j << "] " << original_name_order[j] << "\n";
         if (names[i] == original_name_order[j]) {
            if (TEST_PRINT)
               cout << "Before swap: " << members << "\n";
            std::swap(members[i], members[j]);
            std::swap(original_name_order[i], original_name_order[j]);
            if (TEST_PRINT)
               cout << " After swap: " << members << "\n";
            break;
         }
      }
   }
}
void NamePairs::print() {
   cout << "\n--- contents ---\n";
   for (int i=0; i<names.size(); i++) {
        cout << "  (" << names[i] << ", " << members[i] << ")\n";
   }
}
// ex 03
int NamePairs::size() const { return names.size(); }
struct NamePairs::Pair {
   string name;
   double member;
};
NamePairs::Pair NamePairs::get_pair (int index) const {
   return Pair { names[index], members[index] };
}

ostream& operator<<(ostream& os, NamePairs np) {
   for (int i=0; i<np.size(); i++ ) {
      NamePairs::Pair p = np.get_pair(i);
      os << p.name << "  " << p.member << "\n"; 
   }
   return os;
}

bool operator==(const NamePairs::Pair& p1, const NamePairs::Pair& p2) {
   return ((p1.name == p2.name) && (p1.member == p2.member));
}
bool operator!=(const NamePairs::Pair& p1, const NamePairs::Pair& p2) {
   return !(p1 == p2);
}

bool operator==(const NamePairs& np1, const NamePairs& np2) {
   if (np1.size() != np2.size())
      return false;
   for (int i=0; i<np1.size(); i++) {
      if (np1.get_pair(i) != np2.get_pair(i))
         return false;
   }
   return true;
}
bool operator!=(const NamePairs& np1, const NamePairs& np2) {
   return !(np1 == np2);
}

int main() {

   NamePairs np;
   np.read_names();
   np.read_ages();
   // np.print();
   cout << "--- before\n" << np;
   np.sort();
   // np.print();
   cout << "---  after\n" << np;

   cout << "\n\n\ncomparison operators:\n\n";
   NamePairs np2;
   np2.read_names();
   np2.read_ages();

   cout << "equal? " << (np == np2) << "\n";
   cout << "  neq? " << (np != np2) << "\n\n";

   return 0;
}