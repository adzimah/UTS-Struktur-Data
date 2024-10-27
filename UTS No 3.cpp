#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

class Stack {
private:
    stack<double> s;
public:
    void push(double value) {
        s.push(value);
    }

    double pop() {
        if (!s.empty()) {
            double value = s.top();
            s.pop();
            return value;
        }
        return 0;
    }

    bool isEmpty() {
        return s.empty();
    }
};

double evaluasiPostfix(const string& ekspresi) {
    Stack stack;
    cout << "Langkah-langkah evaluasi ekspresi postfix:\n";

    for (size_t i = 0; i < ekspresi.size(); ++i) {
        char token = ekspresi[i];

        if (isdigit(token)) {
            double operand = token - '0';
            stack.push(operand);
            cout << "Push " << operand << " ke stack\n";
        } else if (token == ' ') {
            // Abaikan spasi
            continue;
        } else {
            double right = stack.pop();
            double left = stack.pop();
            double result;

            switch (token) {
                case '+':
                    result = left + right;
                    cout << "Pop " << left << " dan " << right << ", lakukan " << left << " + " << right << " = " << result << "\n";
                    break;
                case '-':
                    result = left - right;
                    cout << "Pop " << left << " dan " << right << ", lakukan " << left << " - " << right << " = " << result << "\n";
                    break;
                case '*':
                    result = left * right;
                    cout << "Pop " << left << " dan " << right << ", lakukan " << left << " * " << right << " = " << result << "\n";
                    break;
                case '/':
                    result = left / right;
                    cout << "Pop " << left << " dan " << right << ", lakukan " << left << " / " << right << " = " << result << "\n";
                    break;
                case '^':
                    result = pow(left, right);
                    cout << "Pop " << left << " dan " << right << ", lakukan " << left << " ^ " << right << " = " << result << "\n";
                    break;
                default:
                    cout << "Operator tidak dikenal: " << token << "\n";
                    return 0;
            }
            stack.push(result);
            cout << "Push " << result << " ke stack\n";
        }
    }

    double hasil = stack.pop();
    cout << "Hasil akhir: " << hasil << endl;
    return hasil;
}

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix: ";
    getline(cin, ekspresi);

    evaluasiPostfix(ekspresi);

    return 0;
}
