#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <stdlib.h>
using std::string;

const std::vector<string> allowed_names {"Andriy", "Oleksiy", "Mykhailo", "Ivan", "Volodymyr", "Dmytro", "Serhiy", "Petro", "Yaroslav", "Bohdan",
                                          "Taras", "Yevhen", "Orest", "Anatoliy", "Viktor", "Maksym", "Denys", "Kyrylo", "Oleh", "Vitaliy",
                                          "Roman", "Borys", "Vasyl", "Hryhorii", "Fedir", "Hryhoriy", "Nazar", "Oleksandr", "Anatolii", "Olexandr",
                                          "Sergiy", "Mykola", "Ihor", "Anton", "Yuriy", "Olexiy", "Yosyp", "Kostyantyn", "Ruslan", "Maksymilian",
                                          "Olexander", "Dmytrov", "Zakhar", "Lev", "Rostyslav", "Leonid", "Ostap", "Vasyl'", "Bohdan", "Heorhii",
                                          "Hryts'", "Oksana", "Andrii", "Mstyslav", "Nazar", "Yaroslav", "Vasylyna", "Volodymyr", "Dmytro", "Roman",
                                          "Mykhailo", "Ivan", "Petro", "Serhiy", "Viktor", "Oleh", "Taras", "Maksym", "Yevhen", "Kyrylo",
                                          "Orest", "Borys", "Vitaliy", "Hryhorii", "Sergiy", "Fedir", "Vasyl", "Anatoliy", "Hryhoriy", "Ihor",
                                          "Mykola", "Anton", "Oleksandr", "Yuriy", "Zakhar", "Ruslan", "Kostyantyn", "Olexander", "Lev", "Dmytrov",
                                          "Olexiy", "Rostyslav", "Leonid", "Ostap", "Vasyl'", "Bohdan", "Heorhii", "Hryts","Anna", "Maria", "Oksana",
                                          "Iryna", "Olha", "Tetiana", "Svitlana", "Natalia", "Kateryna", "Yuliya",
                                          "Mariya", "Daryna", "Veronika", "Yana", "Valentyna", "Liliya", "Halyna", "Zoryana", "Yaroslava", "Ivanna",
                                          "Olena", "Viktoriya", "Marianna", "Ludmyla", "Nadiya", "Bohdana", "Anastasiya", "Vira", "Solomiya", "Karina",
                                          "Marta", "Yelyzaveta", "Viktoriia", "Alina", "Oleksandra", "Ivanka", "Inna", "Lyudmyla", "Irina", "Lyubov",
                                          "Nina", "Zlata", "Olesya", "Anhelina", "Margarita", "Marina", "Valeria", "Iryna", "Nataliya", "Yuliia","Yaroslavna"};



static uint64_t GetRandomNumber(uint64_t lower, uint64_t higher){
    /// random number gen seeded with time. Outputs numbers between lower and higher
    std::mt19937 randomGen { static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()) };

    std::uniform_int_distribution range(lower,higher);
    return range(randomGen);
}





/// a game where you are a bank worker and people come to your bank cash desk and give you randomised phrases

class Game {
public:
    void start_game() {
        system("CLS");
        std::cout << "Dear cashier, your work begins NOW. Survive as long as possible.\n\n";
        while (playerAlive) {

        }
    }

    void end_game() {

    }

    void display_best_score() {
        std::cout << best_score;
    }

private:
    bool playerAlive = true;
    static uint64_t best_score;

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

class Person {
    short age;
    string name;
    string surname;
    string occupation;
};

class BankAccount {
    
};


int main() {
    std::cout << allowed_names[GetRandomNumber(0,148)];


}

