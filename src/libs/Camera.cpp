#include "Camera.hpp"
#include <cmath>
#include <algorithm>

Camera::Camera(sf::Vector2f viewSize)
    : m_targetPosition(0.0f, 0.0f)
    , m_currentPosition(0.0f, 0.0f)
    , m_deadzone(0.0f, 0.0f)
    , m_smoothness(DEFAULT_SMOOTHNESS)
    , m_useBounds(false)
    , m_bounds({0.0f, 0.0f}, {0.0f, 0.0f})
{
    m_view.setSize(viewSize);
    m_view.setCenter(m_currentPosition);
}

void Camera::setTarget(sf::Vector2f target)
{
    m_targetPosition = target;
}

void Camera::update(float deltaTime)
{
    // Calculate difference between current and target position
    sf::Vector2f diff = m_targetPosition - m_currentPosition;

    // Apply deadzone - only move if outside deadzone
    if (std::abs(diff.x) < m_deadzone.x) {
        diff.x = 0.0f;
    }
    if (std::abs(diff.y) < m_deadzone.y) {
        diff.y = 0.0f;
    }

    // Smooth interpolation (lerp) towards target
    float factor = 1.0f - std::exp(-m_smoothness * deltaTime);
    m_currentPosition.x += diff.x * factor;
    m_currentPosition.y += diff.y * factor;

    // Clamp to bounds if enabled
    if (m_useBounds) {
        sf::Vector2f halfSize = m_view.getSize() / 2.0f;

        float minX = m_bounds.position.x + halfSize.x;
        float maxX = m_bounds.position.x + m_bounds.size.x - halfSize.x;
        float minY = m_bounds.position.y + halfSize.y;
        float maxY = m_bounds.position.y + m_bounds.size.y - halfSize.y;

        if (minX < maxX) {
            m_currentPosition.x = std::clamp(m_currentPosition.x, minX, maxX);
        } else {
            m_currentPosition.x = (minX + maxX) / 2.0f;
        }

        if (minY < maxY) {
            m_currentPosition.y = std::clamp(m_currentPosition.y, minY, maxY);
        } else {
            m_currentPosition.y = (minY + maxY) / 2.0f;
        }
    }

    m_view.setCenter(m_currentPosition);
}

void Camera::apply(sf::RenderWindow& window) const
{
    window.setView(m_view);
}

sf::View Camera::getView() const
{
    return m_view;
}

void Camera::setSmoothness(float smoothness)
{
    m_smoothness = smoothness;
}

void Camera::setDeadzone(sf::Vector2f deadzone)
{
    m_deadzone = deadzone;
}

void Camera::setBounds(sf::FloatRect bounds)
{
    m_bounds = bounds;
}

void Camera::setUseBounds(bool useBounds)
{
    m_useBounds = useBounds;
}
