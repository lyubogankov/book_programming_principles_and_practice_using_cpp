/*
Modify exercise 5 mini-calculator to only accept single-digit numbers,
either as digits or spelled out (similar to exercise 06).
*/


// Modifying mini-calculator from ex5 with code from ex6
// It'll only accept single-digit numbers that are either given as digits or spelled out.
// Note - this won't handle negative numbers, only digits [0, 9].
#include<iostream>
#include<string>
#include<vector>
using namespace std;

inline int convert_operand_to_int(string operand) {
    vector<string> digits = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int result;
    int scalar = 1;
    if (operand[0] == '-')
        scalar = -1;
        operand = operand.substr(1); // take everything from 1st char to the end

    // if the input is a digit  (testing via ascii code)
    if(operand[0] >= 48 && operand[0] <= 57)
        result = stoi(operand);
    // if (operand == "0" || operand == "1" || operand == "2" || operand == "3" || operand == "4" || operand == "5" || operand == "6" || operand == "7" || operand == "8" || operand == "9")
    //     result = stoi(operand);
    else {
        for(int i=0; i<digits.size(); ++i){
            if (operand == digits[i]){
                result = i;
                break;
            }
        }
    }
    return result*scalar;
}

int main() {

    string soperand1, soperand2;
    int    ioperand1, ioperand2;

    char calcoperator; // note: "operator" is a C++ keyword.

    string operation_result_name_and_preposition;
    double result;

    cout << "Please enter {operand1} {operand2} {operator} to receive the result.\n"
         << "\t";
    while(cin >> soperand1 >> soperand2 >> calcoperator) {

        ioperand1 = convert_operand_to_int(soperand1);
        ioperand2 = convert_operand_to_int(soperand2);

        // perform the computation, now that we have the operands converted to integers
        switch(calcoperator){
            case '+':
                operation_result_name_and_preposition = "sum of";
                result = ioperand1 +ioperand2;
                break;
            case '-':
                operation_result_name_and_preposition = "difference between";
                result = ioperand1 -ioperand2;
                break;
            case '*':
                operation_result_name_and_preposition = "product of";
                result = ioperand1 *ioperand2;
                break;
            case '/':
                operation_result_name_and_preposition = "quotient of";
                result = double(ioperand1) / ioperand2;  // casing first iop to double to get actual result
                break;
            default:
                cout << "Unrecognized operator.\n";
        }
        cout << "\tThe " << operation_result_name_and_preposition << " "
             << ioperand1 << " and " <<ioperand2 << " is " << result
             << "\n\n\t";
    }

    return 0;
}
