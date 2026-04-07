#include <iostream>
#include <cstdlib>
#include <ctime>
#include "HandGenerator.h"

Hand HandGenerator::generateHand(){

    std::cout << "Generating cards for player...\n";

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Hand hand;
    hand.value = std::rand() % 13; // random value 0-12
    std::cout << "Random hand value: " << hand.value << std::endl;

    char choice;
    std::cout << "Do you want to input a custom hand value for checking? (y/n): ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        std::cout << "Enter hand value (0-12): ";
        std::cin >> hand.value;
        std::cout << "Using custom hand value: " << hand.value << std::endl;
    }
    return hand;

}
