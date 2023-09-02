#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <csignal>
#include <Windows.h>

using namespace std;

bool exitFlag = false;

// Signal handler for ending the program
void signalHandler(int signal) {
    if (signal == SIGINT) {
        exitFlag = true;
    }
}

// A function that checks whether a symbol is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function that determines the priority of the operator
int getPriority(char op) {
    if (op == '^')
        return 3;
    else if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return 0;
}

// A function that calculates the result of an expression using the inverse Polish notation
double evaluateExpression(string expression) {
    stack<double> values;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        if (expression[i] == '(') {
            operators.push('(');
        }
        else if (isdigit(expression[i]) || expression[i] == '.' || (expression[i] == '-' && (i + 1) < expression.length() && (isdigit(expression[i + 1]) || expression[i + 1] == '.'))) {
            string numStr;
            if (expression[i] == '-') {
                if (i == 0 || expression[i - 1] == '(' || isOperator(expression[i - 1])) {
                    numStr += '-';
                    i++;
                }
                else {
                    operators.push('-');
                    continue;
                }
            }
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                numStr += expression[i];
                i++;
            }
            i--;

            double num = stod(numStr);
            values.push(num);

            if (i + 1 < expression.length() && expression[i + 1] == '-') {
                operators.push('-');
            }
        }


        else if (isOperator(expression[i])) {
            while (!operators.empty() && operators.top() != '(' && getPriority(operators.top()) >= getPriority(expression[i])) {
                double val2 = 0.0;
                double val1 = 0.0;

                if (!values.empty()) {
                    val2 = values.top();
                    values.pop();
                }

                if (!values.empty()) {
                    val1 = values.top();
                    values.pop();
                }

                char op = operators.top();
                operators.pop();

                double result;
                if (op == '+')
                    result = val1 + val2;
                else if (op == '-')
                    result = val1 - val2;
                else if (op == '*')
                    result = val1 * val2;
                else if (op == '/')
                {
                    if (val2 != 0.0)
                        result = val1 / val2;
                    else
                    {
                        cout << "Error: division by zero" << endl;
                        return 0.0;
                    }
                }
                else if (op == '^')
                    result = pow(val1, val2);

                values.push(result);
            }

            operators.push(expression[i]);
        }
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double val2 = 0.0;
                double val1 = 0.0;

                if (!values.empty()) {
                    val2 = values.top();
                    values.pop();
                }

                if (!values.empty()) {
                    val1 = values.top();
                    values.pop();
                }

                char op = operators.top();
                operators.pop();

                double result;
                if (op == '+')
                    result = val1 + val2;
                else if (op == '-')
                    result = val1 - val2;
                else if (op == '*')
                    result = val1 * val2;
                else if (op == '/')
                    result = val1 / val2;
                else if (op == '/')
                {
                    if (val2 != 0.0)
                        result = val1 / val2;
                    else
                    {
                        cout << "Error: division by zero" << endl;
                        return 0.0;
                    }
                }

                values.push(result);
            }

            if (!operators.empty())
                operators.pop();
        }
        else if (expression[i] == 's' || expression[i] == 'c' || expression[i] == 't' || expression[i] == 'a' || expression[i] == 'l' || expression[i] == 'e') {
            string funcStr;
            while (i < expression.length() && isalpha(expression[i])) {
                funcStr += expression[i];
                i++;
            }
            i--;

            if (funcStr == "sin") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    values.push(sin(arg));
                }
            }
            else if (funcStr == "cos") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    values.push(cos(arg));
                }
            }
            else if (funcStr == "tan") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    values.push(tan(arg));
                }
            }
            else if (funcStr == "asin") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    if (arg >= -1 && arg <= 1)
                        values.push(asin(arg));
                    else {
                        cout << "Error: asin argument must be in the range from -1 to 1" << endl;
                        return 0.0;
                    }
                }
            }
            else if (funcStr == "acos") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    if (arg >= -1 && arg <= 1)
                        values.push(acos(arg));
                    else {
                        cout << "Error: acos argument must be in the range from -1 to 1" << endl;
                        return 0.0;
                    }
                }
            }
            else if (funcStr == "atan") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    values.push(atan(arg));
                }
            }
            else if (funcStr == "log") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    if (arg > 0)
                        values.push(log(arg) / log(10));
                    else {
                        cout << "Error: log argument must be greater than 0" << endl;
                        return 0.0;
                    }
                }
            }
            else if (funcStr == "sqrt") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    if (arg >= 0)
                        values.push(sqrt(arg));
                    else {
                        cout << "Error: sqrt argument must be at least 0" << endl;
                        return 0.0;
                    }
                }
            }
            else if (funcStr == "exp") {
                if (expression[i + 1] == '(') {
                    string argStr;
                    int count = 1;
                    i += 2;
                    while (i < expression.length() && count > 0) {
                        if (expression[i] == '(')
                            count++;
                        else if (expression[i] == ')')
                            count--;
                        if (count > 0)
                            argStr += expression[i];
                        i++;
                    }
                    i--;

                    double arg = evaluateExpression(argStr);
                    values.push(exp(arg));
                }
            }
            else {
                cout << "Error: unknown function \"" << funcStr << "\"" << endl;
                return 0.0;
            }
        }
        else {
            cout << "Error: unknown symbol \"" << expression[i] << "\"" << endl;
            return 0.0;
        }

        if (exitFlag)
            break;
    }

    while (!operators.empty() && values.size() >= 2) {
        double val2 = 0.0;
        double val1 = 0.0;
        char op = '\0';

        if (!values.empty()) {
            val2 = values.top();
            values.pop();
        }

        if (!values.empty()) {
            val1 = values.top();
            values.pop();
        }

        if (!operators.empty()) {
            op = operators.top();
            operators.pop();
        }

        double result;
        if (op == '+')
            result = val1 + val2;
        else if (op == '-')
            result = val1 - val2;
        else if (op == '*')
            result = val1 * val2;
        else if (op == '/')
        {
            if (val2 != 0.0)
                result = val1 / val2;
            else
            {
                cout << "Error: division by zero" << endl;
                return 0.0;
            }
        }
        else if (op == '^')
            result = pow(val1, val2);

        values.push(result);
    }

    if (values.size() == 1)
        return values.top();
    else {
        cout << "Error: invalid phrase format" << endl;
        return 0.0;
    }
}

int main() { 
    // Setting the signal generator for program termination by pressing Ctrl+C
    // setlocale(LC_ALL, "any lang");
    signal(SIGINT, signalHandler);

    while (!exitFlag) {
        cout << "Enter arithmetic phrase (or press Ctrl+C to exit): ";
        string expression;
        getline(cin, expression);

        double result = evaluateExpression(expression);
        cout << "Result: " << result << endl;
    }

    return 0;
}