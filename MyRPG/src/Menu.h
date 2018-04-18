#ifndef __MENU__
#define __MENU__

#include <string>
#include <vector>
#include <iostream>

class Menu {
public:
    Menu(std::string description, std::vector<std::string> options);
    ~Menu();

    std::string choose();

private:
    void rangeError();

    std::string m_description;
    std::vector<std::string> m_options;
};

#endif
