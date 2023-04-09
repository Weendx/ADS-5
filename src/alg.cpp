// Copyright 2021 NNTU-CS
#include <string>
#include <stdexcept>
#include <iostream>
#include "../include/tstack.h"

int getPriority(const char& symbol) {
    switch (symbol) {
        case '(':
            return 0;
        case ')':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
        case ' ':
            return -2;
        default:
            return -1;
    }
}

std::string infx2pstfx(std::string inf) {
    std::string output = "";

    TStack<char, 10> operators;

    std::size_t pointer = 0;
    while (inf[pointer]) {
        int priority = getPriority(inf[pointer]);
        if (priority == -1) {
            output += inf[pointer];
            output += ' ';
        } else if (priority == 0 || operators.isEmpty()) {
            operators.push(inf[pointer]);
        } else if (!operators.isEmpty() &&
                priority > getPriority(operators.get())) {
            operators.push(inf[pointer]);
        } else if (inf[pointer] == ')') {
            while (!operators.isEmpty()) {
                char operation = operators.pop();
                if (operation == '(')
                    break;
                if (operation != ')') {
                    output += operation;
                    output += ' ';
                }
            }
        } else {
            while (!operators.isEmpty() &&
                    priority <= getPriority(operators.get())) {
                output += operators.pop();
                output += ' ';
            }
            operators.push(inf[pointer]);
        }

        ++pointer;
    }

    while (!operators.isEmpty()) {
        char operation = operators.pop();
        if (operation != '(' || operation != ')') {
            output += operation;
            output += ' ';
        }
    }
    output.pop_back();
    return output;
}

int eval(std::string pref) {
    TStack<int, 10> operands;

    std::string buf = "";

    std::size_t pointer = 0;
    while (pref[pointer]) {
        int priority = getPriority(pref[pointer]);
        if (priority == -1) {
            buf += pref[pointer];
        } else if (priority == -2 && !buf.empty()) {
            operands.push(std::stoi(buf));
            buf = "";
        } else if (!operands.isEmpty() && (priority == 2 || priority == 3)) {
            int op1 = operands.pop();
            int op2 = operands.pop();
            switch (pref[pointer]) {
                case '+':
                    operands.push(op2 + op1);
                    break;
                case '-':
                    operands.push(op2 - op1);
                    break;
                case '*':
                    operands.push(op2 * op1);
                    break;
                case '/':
                    operands.push(op2 / op1);
                    break;
            }
        }
        ++pointer;
    }

    if (!operands.isEmpty())
        return operands.pop();
    return -999;
    throw std::logic_error("Empty prefession");
}
