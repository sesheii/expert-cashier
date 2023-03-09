#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <stdlib.h>
using std::string;


/// a game where you are a bank worker and people come to your bank cash desk and give you randomised phrases

class Events {
public:
    static uint64_t GetRandomNumber(uint64_t lower, uint64_t higher){
        std::mt19937 randomGen { static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

        std::uniform_int_distribution range(lower,higher);
        return range(randomGen);
    }

    void start_game() {

    }
};

class Commands {

};

/// hi i want to withdraw money
/// i want to borrow some money
/// i want to rob you
/// i want to create a bank account
/// i want to delete my bank account and withdraw all money
/// i want to withdraw X money
/// i want to deposit X money


int main() {
    /// random number gen seeded with time

    std::cout << Events::GetRandomNumber(1,100);
//    std::mt19937 random_number { static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };
//    std::uniform_int_distribution die6{ 1, 6 };
//    bool isPlaying = true;
//    int rounds_count = 0;
//
//
//    while (isPlaying) {
//        system("CLS");
//        if (rounds_count >= 1) {
//            std::cout << "Do you want to play again? (Y/N): ";
//            char YN;
//            do {
//                std::cin >> YN;
//            }
//            while (YN != 'Y' && YN != 'N');
//
//            if (YN == 'Y'){
//                continue;
//            }
//            else {
//                isPlaying = false;
//                continue;
//            }
//        }
//    }

}

