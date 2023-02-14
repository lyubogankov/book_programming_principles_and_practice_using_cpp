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
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

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

     throw runtime_error("word not present in grammar: " + word);
}

// function signature declaration
bool is_valid_sentence(vector<string> words, bool alread_converted);

bool sentence_rule_template(vector<string> words, function<bool(vector<string>)> starts_with_sentence_fn, int conjunction_idx) {
     if (starts_with_sentence_fn(words)) {
          if (words.size() == conjunction_idx)
               return true;
          else if (words[conjunction_idx] == "conjunction" && words.size() > conjunction_idx + 1) {
               vector<string> remainder;
               for (int i = conjunction_idx + 1; i < words.size(); i++)
                    remainder.push_back(words[i]);
               return is_valid_sentence(remainder, true);
          }
     }
     return false;
}
bool sentence_rule_one(vector<string> words) {
     return sentence_rule_template(
          words,
          [](vector<string> w) -> bool { return w[0] == "article" && w[1] == "noun" && w[2] == "verb"; },
          3
     );
}
bool sentence_rule_two(vector<string> words) {
     return sentence_rule_template(
          words,
          [](vector<string> w) -> bool { return w[0] == "noun" && w[1] == "verb"; },
          2
     );
}

bool is_valid_sentence(vector<string> words, bool alread_converted) {     
     // convert words -> parts of speech  (in place)
     if (!alread_converted) {
          for (int i=0; i<words.size(); i++)
               words[i] = classify_word(words[i]);
     }
     
     // assess whether our string is a sentence, or not.
     // Sentence:
     //     Noun Verb          (rule one)
     //     Article Noun Verb  (rule two)
     //     Sentence Conjunction Sentence
     return sentence_rule_one(words) || sentence_rule_two(words);
}

int main() {

     cout << "Please input sentences using our limited vocabulary.\n"
          << "Please terminate each sentence with a standalone period: '{sentence} .'\n"
          << "The program will tell you whether or not the sentence is 'grammatically' correct.\n"
          << "Type 'quit' to quit.\n\n";

     string input = "";
     vector<string> words;
     while(input != "quit") {
          cin >> input;
          if (input == "quit")
               return 0;
          if (input != ".") 
               words.push_back(input);
          else {
               try {
                    if (is_valid_sentence(words, false))
                         cout << "OK\n\n";
                    else
                         cout << "Not OK\n\n";
               } catch (exception &e) {
                    cerr << "error: " << e.what() << "\n\n";
               }
               // empty vector and start over!
               words.clear();
          }
     }
}

// TODO -- remove the classification from MAIN.  Just take user input there, and classify in the is_sentence_valid() function.