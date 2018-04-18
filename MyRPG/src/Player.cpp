#include "Player.h"

Player::Player(std::string name, std::string race, std::string klass) : m_name(name), m_race(race), m_klass(klass) {
    m_attack = 10;
    m_defense = 10;
}
Player::~Player() {}

std::string Player::name() const {
    return m_name;
}

std::string Player::race() const {
    return m_race;
}

std::string Player::klass() const {
    return m_klass;
}

int Player::attack() const {
    return m_attack;
}

int Player::defense() const {
    return m_defense;
}

std::ostream& operator<<(std::ostream& os, Player const& player) {
    os << "Name:    " << player.name() << std::endl;
    os << "Race:    " << player.race() << std::endl;
    os << "Class:   " << player.klass() << std::endl;
    os << "Attack:  " << player.attack() << std::endl;
    os << "Defense: " << player.defense() << std::endl;
    return os;
}

