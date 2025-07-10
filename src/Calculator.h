#pragma once
#include <string>

class Calculator {
public:
    Calculator() = default;

    //Checks if input looks like a math expression
    bool isMathExpression(const std::string& input) const;

    //Evaluates expression, throws std::runtime_error on failure
    double evaluate(const std::string& expression, int moodScore);

private:
    const char* exprPtr;

    double parseExpression();
    double parseTerm();
    double parseFactor();

    void skipWhitespace();
    char peek();
    char get();

    double parseNumber();
};