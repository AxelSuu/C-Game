#pragma once

#include <functional>

class ScoreManager {
public:
    using Callback = std::function<void(int newScore)>;

    static ScoreManager& getInstance();

    // Score manipulation
    void addScore(int points);
    void subtractScore(int points);
    void setScore(int score);
    void reset();

    // Getters
    int getScore() const { return m_score; }
    int getHighScore() const { return m_highScore; }

    // Multiplier system
    void setMultiplier(float multiplier) { m_multiplier = multiplier; }
    float getMultiplier() const { return m_multiplier; }
    void resetMultiplier() { m_multiplier = 1.0f; }

    // Combo system
    void incrementCombo();
    void resetCombo();
    int getCombo() const { return m_combo; }

    // Callbacks
    void setOnScoreChanged(Callback callback) { m_onScoreChanged = std::move(callback); }

    // Delete copy/move for singleton
    ScoreManager(const ScoreManager&) = delete;
    ScoreManager& operator=(const ScoreManager&) = delete;

private:
    ScoreManager();

    int m_score;
    int m_highScore;
    float m_multiplier;
    int m_combo;

    Callback m_onScoreChanged;
};
