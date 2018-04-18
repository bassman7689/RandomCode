#include "Menu.h"

Menu::Menu(std::string description, std::vector<std::string> options) : m_description(description), m_options(options) {}

Menu::~Menu() {}

std::string Menu::choose() {
    int choice = 0;
    std::string selectedOption;
    bool selected = false;

    std::cout << m_description << std::endl;

    while(!selected) {
        int number = 1;
        for (auto &option : m_options) {
            std::cout << number << ". " << option << std::endl;
            number++;
        }

        std::cout << "choice: ";
        std::cin >> choice;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            rangeError();
            continue;
        }


        if(choice > 0 && choice <= m_options.size()) {
            selected = true;
            selectedOption = m_options.at(choice-1);
        } else {
            rangeError();
        }
    }

    return selectedOption;
}

void Menu::rangeError() {
            std::cout << "your choice must be a number between 1 and " << m_options.size() << std::endl;
}

