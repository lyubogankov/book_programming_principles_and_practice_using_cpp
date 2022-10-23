#include<iostream>
using namespace std;

int main() {

    double operand1, operand2;
    char calcoperator;

    cout << "Please enter {operand1} {operand2} {operator} to receive the result.\n"
         << "\t";
    while(cin >> operand1 >> operand2 >> calcoperator) {
        switch(calcoperator){
            case '+':
                cout << "\tThe sum of " << operand1 << " and " << operand2 << " is "
                     << operand1 + operand2;
                break;
            case '-':
                cout << "\tThe difference between " << operand1 << " and " << operand2 << " is "
                     << operand1 - operand2;
                break;
            case '*':
                cout << "\tThe product of " << operand1 << " and " << operand2 << " is "
                     << operand1 * operand2;
                break;
            case '/':
                cout << "\tThe quotient of " << operand1 << " and " << operand2 << " is "
                     << operand1 / operand2;
                break;
            default:
                cout << "Unrecognized operator.\n";
        }
        cout << "\n\n\t";
    }

    return 0;
}
