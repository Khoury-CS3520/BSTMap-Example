#include "BSTMap.h"
#include <iostream>

int main () {
    BSTMap<int, std::string> myMap;
    myMap.insert(50, "hi");
    myMap.insert(25, "whats up?");
    myMap.insert(75, "hello");
    myMap.traverse();
    std::cout << std::endl;

    auto& temp = myMap.search(75);
    temp = "goodbye";
    myMap.traverse();

    auto anotherMap = myMap;
    std::cout << "\nAnother Map's Content" << std::endl;
    anotherMap.traverse();

    BSTMap<int, int> thirdMap;
    thirdMap.traverse();
}
