#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Menu.h"
#include "Player.h"
#include "Scene.h"

int main(int argc, char **argv) {
    std::string name;
    std::cout << "Hello adventurer, please enter your name: ";
    std::cin >> name;

    std::vector<std::string> races;
    races.push_back("Human");
    races.push_back("Dwarf");
    races.push_back("Elf");
    races.push_back("Half Elf");

    std::stringstream ss;
    ss << "Than you " << name << ", please select a race:";

    Menu raceMenu = Menu(ss.str(), races);
    std::string selectedRace = raceMenu.choose();
    
    std::vector<std::string> classes;
    classes.push_back("Wizard");
    classes.push_back("Fighter");
    classes.push_back("Rogue");
    classes.push_back("Hunter");

    ss.clear();
    ss.str(std::string());
    ss << "Thank you " << name << ", please select a class:";

    Menu classMenu = Menu(ss.str(), classes);
    std::string selectedClass = classMenu.choose();

    Player player = Player(name, selectedRace, selectedClass);

    std::cout << player; 

    std::cout << "You wake up in a field and wonder how you got there." << std::endl;
    std::cout << "You look around and see that you are in a field in the middle of a forest." << std::endl;

    ss.clear();
    ss.str(std::string());
    ss << "What would you like to do?";

    std::vector<std::string> actions;
    actions.push_back("Inspect Ground");
    actions.push_back("Investigate");

    Menu actionMenu = Menu(ss.str(), actions);
    Scene openingScene = Scene(actionMenu);
    openingScene.run();
}
