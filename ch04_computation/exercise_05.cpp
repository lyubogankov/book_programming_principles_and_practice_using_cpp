#include<iostream>
#include<string>
using namespace std;

int main() {

    double operand1, operand2;
    char calcoperator; // note: "operator" is a C++ keyword.
    string operation_result_name_and_preposition;
    double result;

    cout << "Please enter {operand1} {operand2} {operator} to receive the result.\n"
         << "\t";
    while(cin >> operand1 >> operand2 >> calcoperator) {
        switch(calcoperator){
            case '+':
                operation_result_name_and_preposition = "sum of";
                result = operand1 + operand2;
                break;
            case '-':
                operation_result_name_and_preposition = "difference between";
                result = operand1 - operand2;
                break;
            case '*':
                operation_result_name_and_preposition = "product of";
                result = operand1 * operand2;
                break;
            case '/':
                operation_result_name_and_preposition = "quotient of";
                result = operand1 / operand2;
                break;
            default:
                cout << "Unrecognized operator.\n";
        }
        cout << "\tThe " << operation_result_name_and_preposition << " "
             << operand1 << " and " << operand2 << " is " << result
             << "\n\n\t";
    }

    return 0;
}
