#include <iostream>
#include <vector>

int main(int argc, char **argv) {
    std::vector<int> testVector;

    testVector.push_back(1);
    testVector.push_back(2);
    std::cout << "testVector has " << testVector.size() << " elements." << std::endl;
    testVector.clear();
    std::cout << "testVector has " << testVector.size() << " elements." << std::endl;
}
