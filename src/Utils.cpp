#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include <cctype>
#include <fstream>
#include <ctime>

void printWithColor(const std::string& text, Color color) {
    std::string code;
    switch (color) {
        case Color::Red: code = "\033[1;31m"; break;
        case Color::Green: code = "\033[1;32m"; break;
        case Color::Yellow: code = "\033[1;33m"; break;
        case Color::Blue: code = "\033[1;34m"; break;
        case Color::Cyan: code = "\033[1;36m"; break;
				case Color::Magenta: code = "\033[1;35m"; break;
        default: code = "\033[0m"; break;
    }

    std::cout << code << text << "\033[0m";
}

std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";

    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

bool containsKindness(const std::string& input) {
    std::string lowered = toLower(input);
    std::vector<std::string> sweetWords = {
        "thank", "please", "love", "smart", "awesome", "great", "good", "appreciate", "sweet", "amazing"
    };

    for (const auto& word : sweetWords) {
        if (lowered.find(word) != std::string::npos)
            return true;
    }
    return false;
}

bool containsSadness(const std::string& input) {
    std::string lowered = toLower(input);
    std::vector<std::string> sadWords = {
        "hate", "stupid", "dumb", "kill", "die", "idiot", "ugly", "sucks"
    };

    for (const auto& word : sadWords) {
        if (lowered.find(word) != std::string::npos)
            return true;
    }
    return false;
}

bool randomChance(double probability) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);
    return dis(gen) < probability;
}

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void fakeThinkingDelay() {
    if (randomChance(0.3)) {
        std::string delays[] = {
            "Hmm...", "Uhhh...", "Wait a sec...", "Math is hard today...", "Thinking..."
        };
        printWithColor(delays[randomInt(0, 4)] + "\n", Color::Yellow);
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + randomInt(300, 700)));
    }
}

void logInteraction(int moodScore, const std::string& input) {
    std::ofstream log("calcuMood.log", std::ios::app);
    if (!log) return;

    std::time_t now = std::time(nullptr);
    char* timestr = std::ctime(&now);
    if (timestr) {
        timestr[strlen(timestr) - 1] = '\0'; //remove newline
    }

    log << "[" << (timestr ? timestr : "unknown time") << "] Mood: " 
        << moodScore << " | Input: " << input << "\n";
}