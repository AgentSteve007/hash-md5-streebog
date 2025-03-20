#include <iostream>
#include <stack>
#include <cctype> 

using namespace std;

// Функция для выполнения арифметической операции
int performOperation(int operand1, int operand2, char operation) {
    if (operation == '+') {
        return operand1 + operand2;
    }
    else if (operation == '-') {
        return operand1 - operand2;
    }
    return 0; // Защита на случай неверной операции
}

// Функция для вычисления выражения
int evaluateExpression(const string& expression) {
    stack<int> operands;    // Стек операндов (чисел)
    stack<char> operators;  // Стек операторов (+ или -)

    int i = 0;

    // Проверка на случай, если первый элемент — это знак минуса
    if (expression[0] == '-') {
        // Если выражение начинается с '-', считаем первое число отрицательным
        i++;  // Переходим к следующему символу
        operands.push(-(expression[i] - '0'));  // Запоминаем отрицательный первый операнд
        i++;  // Переходим дальше
    }

    // Основной цикл для обработки выражения
    for (; i < expression.length(); ++i) {
        char ch = expression[i];

        // Если символ - цифра, кладем его в стек операндов
        if (isdigit(ch)) {
            operands.push(ch - '0');
        }
        // Если символ - оператор (+ или -), кладем его в стек операторов
        else if (ch == '+' || ch == '-') {
            operators.push(ch);
        }
        // Если символ '=', выполняем все оставшиеся операции
        else if (ch == '=') {
            while (!operators.empty()) {
                int operand2 = operands.top(); operands.pop();
                int operand1 = operands.top(); operands.pop();
                char op = operators.top(); operators.pop();

                // Выполняем операцию и кладем результат обратно в стек операндов
                int result = performOperation(operand1, operand2, op);
                operands.push(result);
            }
        }
    }

    // Результат будет в вершине стека операндов
    return operands.top();
}

int main4() {
    setlocale(LC_ALL, "Russian");

    string expression;

    cout << "Введите выражение: ";
    cin >> expression;

    int result = evaluateExpression(expression);

    cout << "Результат: " << result << endl;

    return 0;
}
