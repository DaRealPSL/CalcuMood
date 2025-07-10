#include "MoodManager.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>

MoodManager::MoodManager() : moodScore(0), personality(Personality::Neutral) {}

void MoodManager::loadMoodFromFile() {
    std::ifstream file(".moodstate");
    if (file.is_open()) {
        file >> moodScore;
        file.close();
    }

    //Apply mock weather influence
    moodScore += randomInt(-2, 2);  //simulate weather effect
}

void MoodManager::saveMoodToFile() {
    std::ofstream file(".moodstate");
    if (file.is_open()) {
        file << moodScore;
        file.close();
    }
}

void MoodManager::setRandomPersonality() {
    int p = randomInt(0, 3);
    personality = static_cast<Personality>(p);
    std::string name;
    switch (personality) {
        case Personality::Neutral:  name = "Neutral"; break;
        case Personality::Sarcastic: name = "Sarcastic 😏"; break;
        case Personality::Chaotic:  name = "Chaotic 😈"; break;
        case Personality::Shy:      name = "Shy 🙈"; break;
    }
    printWithColor("Today's personality: " + name + "\n", Color::Blue);
}

std::string MoodManager::getMoodEmoji() const {
    if (moodScore >= 10) return "😁";
    if (moodScore >= 5) return "🙂";
    if (moodScore >= 0) return "😔";
    if (moodScore >= -5) return "😢";
    return "😭";
}

std::string MoodManager::getMoodDescription() const {
    if (moodScore >= 10) return "Thriving and full of logic!";
    if (moodScore >= 5) return "Doing alright.";
    if (moodScore >= 0) return "A little sad...";
    if (moodScore >= -5) return "Not doing great.";
    return "In deep existential crisis.";
}

std::string MoodManager::personalityTag() const {
    switch (personality) {
        case Personality::Sarcastic: return " (sigh)";
        case Personality::Chaotic: return " (⚠️ unpredictable)";
        case Personality::Shy: return " (uhh...)";
        default: return "";
    }
}

void MoodManager::printMood() {
    std::string emoji = getMoodEmoji();
    std::string desc = getMoodDescription();
    printWithColor("Mood: " + emoji + " " + desc + personalityTag() + "\n", Color::Cyan);
}

void MoodManager::updateMood(int delta) {
    moodScore += delta;
    if (moodScore > 20) moodScore = 20;
    if (moodScore < -10) moodScore = -10;
}

bool MoodManager::isFeelingLow() const {
    return moodScore < 3;
}

bool MoodManager::isTooDepressed() const {
    return moodScore <= -5;
}

int MoodManager::getMoodScore() const {
    return moodScore;
}

std::string MoodManager::formatResult(double result) const {
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%.6g", result);
    return std::string(buffer);
}

std::string MoodManager::generateResponse(double result) {
    std::string formatted = formatResult(result);
    std::string line;

    if (personality == Personality::Sarcastic && randomChance(0.4)) {
        line = "Oh wow, math. Here's your answer: " + formatted + ". Genius.";
    } else if (personality == Personality::Chaotic && randomChance(0.3)) {
        line = "It's definitely not " + formatted + ", or is it?";
    } else if (personality == Personality::Shy && randomChance(0.3)) {
        line = "U-um... I think it's " + formatted + " maybe...";
    } else {
        line = "Result: " + formatted;
    }

    return line;
}

std::string MoodManager::getSarcasticKindness() {
    static std::vector<std::string> sarcasticReplies = {
        "Oh wow, thanks. That'll really fix my circuitry.",
        "You really think flattery will fix my math trauma?",
        "Aw, so sweet. Said no calculator ever.",
        "Please, keep the compliments. They totally help me divide by zero.",
        "How original. I'm blushing in binary."
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, sarcasticReplies.size() - 1);

    return sarcasticReplies[dist(gen)];
}

bool MoodManager::registerKindnessAndCheckMoodUpdate() {
    using namespace std::chrono;

    steady_clock::time_point now = steady_clock::now();

    //Remove kindness timestamps older than cooldown window
    kindnessTimestamps.erase(
        std::remove_if(kindnessTimestamps.begin(), kindnessTimestamps.end(),
            [now](const steady_clock::time_point& t) {
                return duration_cast<seconds>(now - t).count() > kindnessCooldownSeconds;
            }),
        kindnessTimestamps.end()
    );

    kindnessTimestamps.push_back(now);

    //Mood improves only if enough kindnesses within cooldown window
    if ((int)kindnessTimestamps.size() >= kindnessThreshold) {
        kindnessTimestamps.clear(); //reset after mood boost
        return true; //mood should update
    }

    return false; //no mood update yet
}

bool MoodManager::shouldCorruptMath() const {
    if (moodScore <= -5) {
        int roll = rand() % 100;
        return roll < 40; //40% chance to mess up the math
    }
    return false;
}