#include "Calculator.h"
#include <cctype>
#include <stdexcept>
#include <cstdlib>
#include <random>
#include <vector>
#include <iostream>

bool Calculator::isMathExpression(const std::string& input) const {
    for (char c : input) {
        if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' &&
            c != '.' && c != '(' && c != ')' && !std::isspace(c))
            return false;
    }
    return true;
}

double Calculator::evaluate(const std::string& expression, int moodScore) {
    //Check mood before evaluating
    if (moodScore <= -5) {
        static std::vector<std::string> sadMessages = {
            "I can't. Not like this.",
            "What's the point of numbers anyway?",
            "I was once joyful... now just floating point despair.",
            "Error: Emotional core not found.",
            "I used to care about math. Now I just cope.",
            "I'm not broken. Just... miscompiled.",
            "Another calculation? Why bother..."
        };
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, sadMessages.size() - 1);
        std::cout << sadMessages[dist(gen)] << std::endl;
        throw std::runtime_error("Too sad to compute");
    }

    exprPtr = expression.c_str();
    double result = parseExpression();
    skipWhitespace();
    if (*exprPtr != '\0') {
        throw std::runtime_error("Unexpected characters at end");
    }
    return result;
}

void Calculator::skipWhitespace() {
    while (std::isspace(*exprPtr)) ++exprPtr;
}

char Calculator::peek() {
    skipWhitespace();
    return *exprPtr;
}

char Calculator::get() {
    skipWhitespace();
    return *exprPtr++;
}

double Calculator::parseExpression() {
    double left = parseTerm();
    while (true) {
        char op = peek();
        if (op == '+' || op == '-') {
            get();
            double right = parseTerm();
            if (op == '+') left += right;
            else left -= right;
        } else break;
    }
    return left;
}

double Calculator::parseTerm() {
    double left = parseFactor();
    while (true) {
        char op = peek();
        if (op == '*' || op == '/') {
            get();
            double right = parseFactor();
            if (op == '*') left *= right;
            else {
                if (right == 0) throw std::runtime_error("Division by zero");
                left /= right;
            }
        } else break;
    }
    return left;
}

double Calculator::parseFactor() {
    char c = peek();
    if (c == '+' || c == '-') {
        get();
        double val = parseFactor();
        return (c == '-') ? -val : val;
    } else if (c == '(') {
        get();
        double val = parseExpression();
        if (get() != ')') throw std::runtime_error("Expected closing parenthesis");
        return val;
    } else {
        return parseNumber();
    }
}

double Calculator::parseNumber() {
    skipWhitespace();
    const char* start = exprPtr;
    bool decimalFound = false;

    if (*exprPtr == '+' || *exprPtr == '-') ++exprPtr;

    while (std::isdigit(*exprPtr) || *exprPtr == '.') {
        if (*exprPtr == '.') {
            if (decimalFound) break;
            decimalFound = true;
        }
        ++exprPtr;
    }

    std::string token(start, exprPtr - start);
    if (token.empty() || token == "+" || token == "-")
        throw std::runtime_error("Invalid number");

    return std::stod(token);
}