#include <iostream>
#include <limits>
#include <string>
using namespace std;

// History storage
const int MAX_HISTORY = 50;
string history[MAX_HISTORY];
int historyCount = 0;

// Function declarations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
bool divide(double a, double b, double &result);
void addToHistory(const string &record);
void showHistory();

int main() {
    int choice;
    double num1, num2, result;

    while (true) {
        cout << "\n===== SIMPLE CALCULATOR =====\n";
        cout << "1. Addition\n";
        cout << "2. Subtraction\n";
        cout << "3. Multiplication\n";
        cout << "4. Division\n";
        cout << "5. Show Calculation History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        // Validate menu input
        if (!(cin >> choice)) {
            cout << "Error: Invalid input! Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 6) {
            cout << "Exiting calculator...\n";
            break;
        }

        if (choice == 5) {
            showHistory();
            continue;
        }

        if (choice < 1 || choice > 6) {
            cout << "Invalid option! Please choose between 1 and 6.\n";
            continue;
        }

        // Input first number
        cout << "Enter first number: ";
        if (!(cin >> num1)) {
            cout << "Error: Invalid number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Input second number
        cout << "Enter second number: ";
        if (!(cin >> num2)) {
            cout << "Error: Invalid number!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Perform calculation
        switch (choice) {
            case 1:
                result = add(num1, num2);
                cout << "Result = " << result << endl;
                addToHistory(to_string(num1) + " + " + to_string(num2) + " = " + to_string(result));
                break;

            case 2:
                result = subtract(num1, num2);
                cout << "Result = " << result << endl;
                addToHistory(to_string(num1) + " - " + to_string(num2) + " = " + to_string(result));
                break;

            case 3:
                result = multiply(num1, num2);
                cout << "Result = " << result << endl;
                addToHistory(to_string(num1) + " * " + to_string(num2) + " = " + to_string(result));
                break;

            case 4:
                if (divide(num1, num2, result)) {
                    cout << "Result = " << result << endl;
                    addToHistory(to_string(num1) + " / " + to_string(num2) + " = " + to_string(result));
                } else {
                    cout << "Error: Division by zero is not allowed!\n";
                }
                break;
        }
    }

    cout << "Calculator closed safely.\n";
    return 0;
}

// Function definitions
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

bool divide(double a, double b, double &result) {
    if (b == 0)
        return false;
    result = a / b;
    return true;
}

void addToHistory(const string &record) {
    if (historyCount < MAX_HISTORY) {
        history[historyCount++] = record;
    }
}

void showHistory() {
    if (historyCount == 0) {
        cout << "\nNo calculation history available.\n";
        return;
    }

    cout << "\n===== CALCULATION HISTORY =====\n";
    for (int i = 0; i < historyCount; i++) {
        cout << i + 1 << ". " << history[i] << endl;
    }
}

