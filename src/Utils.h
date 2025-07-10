#pragma once
#include <string>
#include <vector>

enum class Color {
    Default,
    Red,
    Green,
    Yellow,
    Blue,
    Cyan,
		Magenta
};

//Terminal colorized output
void printWithColor(const std::string& text, Color color);

//String utilities
std::string toLower(const std::string& s);
std::string trim(const std::string& s);
bool containsKindness(const std::string& input);
bool containsSadness(const std::string& input);

//Random utilities
bool randomChance(double probability);  //example: 0.3 = 30%
int randomInt(int min, int max);

//Misc
void fakeThinkingDelay();

//Log
void logInteraction(int moodScore, const std::string& input);