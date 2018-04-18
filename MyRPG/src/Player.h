#ifndef __PLAYER__
#define __PLAYER__

#include <iostream>

class Player {
public:
    Player(std::string name, std::string race, std::string klass);
    ~Player();

    std::string name() const;
    std::string race() const;
    std::string klass() const;
    int attack() const;
    int defense() const;

private:
    std::string m_name;
    int m_attack;
    int m_defense;

    std::string m_race;
    std::string m_klass;

};


std::ostream& operator<<(std::ostream& os, Player const& player);

#endif
