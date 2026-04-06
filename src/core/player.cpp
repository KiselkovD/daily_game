/**
 * @file player.cpp
 * @brief реализация класса игрока
 */
#include "player.hpp"

Player::Player(const std::string &name) : m_name(name), m_generalScore(0) {}

std::string Player::getName() const { return m_name; }

int Player::getGeneralScore() const { return m_generalScore; }

void Player::addToGeneralScore(int points) { m_generalScore += points; }

void Player::setGeneralScore(int score) { m_generalScore = score; }

void Player::setName(const std::string &name) { m_name = name; }