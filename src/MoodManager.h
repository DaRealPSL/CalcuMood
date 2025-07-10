#pragma once
#include <string>
#include <vector>

enum class Personality {
    Neutral,
    Sarcastic,
    Chaotic,
    Shy
};

class MoodManager {
public:
    MoodManager();

    void loadMoodFromFile();
    void saveMoodToFile();
    void setRandomPersonality();
    void printMood();
    void updateMood(int delta);
    std::string generateResponse(double result);
    std::string getSarcasticKindness();

    bool isFeelingLow() const;
    bool isTooDepressed() const;
    bool registerKindnessAndCheckMoodUpdate();
    bool shouldCorruptMath() const;
    int getMoodScore() const;

private:
    int moodScore;
    Personality personality;

    std::string getMoodEmoji() const;
    std::string getMoodDescription() const;
    std::string personalityTag() const;
    std::string formatResult(double result) const;

    std::vector<std::chrono::steady_clock::time_point> kindnessTimestamps;
    static constexpr int kindnessCooldownSeconds = 10; //minimum seconds between kindnesses
    static constexpr int kindnessThreshold = 2;        //how many kindnesses needed to improve mood
};