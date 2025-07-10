#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>

#include "MoodManager.h"
#include "Calculator.h"
#include "Utils.h"

int main() {
    MoodManager moodManager;
    Calculator calculator;
    
    std::string input;
    
    printWithColor("Welcome to CalcuMood\n", Color::Yellow);
    printWithColor("Type math or be kind to cheer me up. Type 'exit' to leave.\n\n", Color::Yellow);
    
    moodManager.loadMoodFromFile();
    moodManager.setRandomPersonality();
    moodManager.printMood();

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        trim(input);
        
        if (input.empty()) continue;
        if (input == "exit") break;

        logInteraction(moodManager.getMoodScore(), input);
        
        //Easter Eggs
        std::string inputLower = toLower(input);

        if (inputLower == "42") {
            printWithColor("The answer to life, the universe, and everything. But what's the question?\n", Color::Cyan);
            moodManager.updateMood(1);
            moodManager.printMood();
            continue;
        }

        if (inputLower == "01134") {
            printWithColor("Turn me upside down.\n", Color::Cyan);
            continue;
        }

        if (inputLower == "69" || inputLower == "420") {
            printWithColor("Nice.\n", Color::Cyan);
            moodManager.updateMood(1);
            continue;
        }

        if (inputLower == "why") {
            printWithColor("Why not?\n", Color::Cyan);
            continue;
        }

        if (inputLower.find("sing") != std::string::npos) {
            printWithColor("I'm a calculator, not a karaoke machine...\n", Color::Magenta);
            continue;
        }

        if (moodManager.isTooDepressed()) {
            printWithColor("I can't. Not like this.\n", Color::Red);
            continue;
        }

        if (moodManager.isFeelingLow()) {
            fakeThinkingDelay(); //add "uhhh..."
        }

        if (containsKindness(input)) {
            //30% chance of sarcasm if mood is mid (0 to 2)
            if (moodManager.getMoodScore() >= 0 && moodManager.getMoodScore() <= 2) {
                int roll = rand() % 100;
                if (roll < 30) {
                    printWithColor(moodManager.getSarcasticKindness() + "\n", Color::Magenta);
                    moodManager.updateMood(0); //no mood improvement
                    moodManager.printMood();
                    continue;
                }
            }

            //Delayed mood recovery logic
            if (moodManager.registerKindnessAndCheckMoodUpdate()) {
                moodManager.updateMood(2);
                printWithColor("Thanks... that helps a little.\n", Color::Green);
            } else {
                printWithColor("Hmm... thanks, but I'm still thinking.\n", Color::Green);
            }

            moodManager.printMood();
            continue;
        }

        if (calculator.isMathExpression(input)) {
    try {
        double result = calculator.evaluate(input, moodManager.getMoodScore());

        // 👇 Inject math corruption when deeply sad
        if (moodManager.shouldCorruptMath()) {
            int corruptionType = rand() % 3;
            switch (corruptionType) {
                case 0:
                    result += (rand() % 100) - 50; // +/- 0 to 50
                    break;
                case 1:
                    printWithColor("Result: Definitely 7. Don’t ask why.\n", Color::Red);
                    moodManager.updateMood(-1); // even that hurt
                    moodManager.printMood();
                    continue;
                case 2:
                    printWithColor("ERROR: Division by existential dread.\n", Color::Red);
                    moodManager.updateMood(-1);
                    moodManager.printMood();
                    continue;
            }
        }

        std::string response = moodManager.generateResponse(result);
        std::cout << response << std::endl;
        moodManager.updateMood(1);
    } catch (const std::exception& e) {
        printWithColor("That broke my brain. Try again?\n", Color::Red);
        moodManager.updateMood(-1);
    }
        } else {
            printWithColor("I don't know what to do with that...\n", Color::Magenta);
            moodManager.updateMood(-1);
        }

        moodManager.printMood();
    }

    moodManager.saveMoodToFile();
    printWithColor("\nGoodbye, emotional human.\n", Color::Yellow);
    return 0;
}