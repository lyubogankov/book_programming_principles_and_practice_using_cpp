/*

 5. Add the article the to the “English” grammar in §6.4.1, 
    so that it can describe sentences such as “The birds fly but the fish swim.”

     Grammar from §6.4.1
     -------------------
          Sentence:
               Noun Verb
               Article Noun Verb                # new!
               Sentence Conjunction Sentence
          Article:                              # new!
               "the"                            # <
               "a"                              # < (extra credit)
               "an"                             # < (extra credit)
          Conjunction:
               "and"
               "or"
               "but"
          Noun:
               "birds"
               "fish"
               "C++"
          Verb:
               "rules"
               "fly"
               "swim"


 6. Write a program that checks if a sentence is correct according to the “English” grammar in §6.4.1.
    Assume that every sentence is terminated by a full stop (.) surrounded by whitespace.
   
    For example, this is a sentence:
         birds fly but the fish swim . 
    These are not sentences:
         birds fly but the fish swim   # (terminating dot missing)
         birds fly but the fish swim.  # (no space before dot)

     For each sentence entered, the program should simply respond “OK” or “not OK.” 
     
     Hint: Don’t bother with tokens; just read into a string using >>.

*/
#include <iostream>
#include <vector>
using namespace std;

bool is_valid_sentence(vector<string> word_types) {
     for (string s : word_types)
          cout << s << " ";
     cout << "\n";
     return true;
}

bool string_in_strvector(vector<string> haystack, string needle) {
     for (string s : haystack) {
          if (s == needle)
               return true;
     }
     return false;
}
string classify_word(string word) {
     vector<string> articles = {"the", "a", "an"};
     vector<string> conjunctions = {"and", "or", "but"};
     vector<string> nouns = {"birds", "fish", "C++"};
     vector<string> verbs = {"rules", "fly", "swim"};

     if (string_in_strvector(articles,     word)) return "article";
     if (string_in_strvector(conjunctions, word)) return "conjunction";
     if (string_in_strvector(nouns,        word)) return "noun";
     if (string_in_strvector(verbs,        word)) return "verb";

     throw runtime_error("word not present in grammar");
}

int main() {

     string input = "";
     string word_class;
     vector<string> classified_inputs;
     while(input != "quit") {
          cin >> input;
          if (input != "." and input != "quit") 
               classified_inputs.push_back(classify_word(input));
          else {
               if (is_valid_sentence(classified_inputs))
                    cout << "OK\n\n";
               else
                    cout << "Not OK\n\n";
               // empty vector and start over!
               classified_inputs.clear();
          }
     }
}