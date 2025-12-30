#include "ScoreManager.hpp"
#include <algorithm>

ScoreManager& ScoreManager::getInstance()
{
    static ScoreManager instance;
    return instance;
}

ScoreManager::ScoreManager()
    : m_score(0)
    , m_highScore(0)
    , m_multiplier(1.0f)
    , m_combo(0)
{
}

void ScoreManager::addScore(int points)
{
    if (points <= 0) return;

    int actualPoints = static_cast<int>(points * m_multiplier);
    m_score += actualPoints;

    if (m_score > m_highScore) {
        m_highScore = m_score;
    }

    if (m_onScoreChanged) {
        m_onScoreChanged(m_score);
    }
}

void ScoreManager::subtractScore(int points)
{
    if (points <= 0) return;

    m_score = std::max(0, m_score - points);

    if (m_onScoreChanged) {
        m_onScoreChanged(m_score);
    }
}

void ScoreManager::setScore(int score)
{
    m_score = std::max(0, score);

    if (m_score > m_highScore) {
        m_highScore = m_score;
    }

    if (m_onScoreChanged) {
        m_onScoreChanged(m_score);
    }
}

void ScoreManager::reset()
{
    m_score = 0;
    m_multiplier = 1.0f;
    m_combo = 0;

    if (m_onScoreChanged) {
        m_onScoreChanged(m_score);
    }
}

void ScoreManager::incrementCombo()
{
    m_combo++;
    // Increase multiplier based on combo
    m_multiplier = 1.0f + (m_combo * 0.1f);
}

void ScoreManager::resetCombo()
{
    m_combo = 0;
    m_multiplier = 1.0f;
}
