#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include "utility.h"

int randomNumber(int lower, int higher) {
    std::uniform_int_distribution distribution(lower, higher);
    std::mt19937_64 timeSeededGenerator {static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
    return distribution(timeSeededGenerator);
}

class Entity {
protected:
    std::string name_surname;
    int age;
    std::string species;

public:
    Entity(){}
    Entity(std::string _name_surname, int _age) : name_surname(_name_surname), age(_age) {}

    std::string getNameSurname() {
        return name_surname;
    }
    int getAge() {
        return age;
    }
    std::string getSpecies() {
        return species;
    }

    virtual void greet(){
        std::cout << "UNDEFINED. YOU SHOULDN'T SEE THIS MESSAGE\n";
    }
};

class BankClient {
    bool registered = false;
    int ID = 0;
    uint64_t balance;
public:
    void createAccount() {
        if (registered) {
            std::cout << "This person is registered already.\n";
            return;
        }
        ID = randomNumber(10000000, 99999999);
        balance = 0;
        registered = true;
    }

    void accountWithdraw(uint64_t amount) {
        if (amount > balance) {
            std::cout << "This person doesn't have enough money to perform the operation.\n";
            return;
        }
        balance -= amount;
    }

    void accountDeposit(uint64_t amount) {
        balance += amount;
    }

    int getAccountID() {
        return ID;
    }

};

class Human : public Entity, public BankClient {
protected:
    std::string gender;
public:
    Human(){
        species = "human";
    }
    Human(std::string _name_surname, int _age) : Entity(_name_surname, _age){
        species = "human";
    }

    std::string getGender() {
        return gender;
    }

    void greet() override {
        std::cout << "Hello, mr cashier!\n";
    }
};

class Man : public Human {
public:
    Man(std::string r = "") {
        if (r == "random") {
            if (randomNumber(0, 9)) /// 10% chance to get no bank account
                this->createAccount();
            gender = "male";
            age = randomNumber(16, 100);
            name_surname = male_names[randomNumber(0,male_names.size()-1)] + ' '
                    + male_surnames[randomNumber(0,male_surnames.size()-1)];
        }
    }
    Man(std::string _name_surname, int _age) : Human(_name_surname, _age){
        gender = "male";
    }
};

class Woman : public Human {
public:
    Woman(std::string r = "") {
        if (r == "random") {
            if (randomNumber(0, 9)) /// 10% chance to get no bank account
                this->createAccount();
            gender = "female";
            age = randomNumber(16, 100);
            name_surname = female_names[randomNumber(0,female_names.size()-1)] + ' '
                           + female_surnames[randomNumber(0,female_surnames.size()-1)];
        }
    }
    Woman(std::string _name_surname, int _age) : Human(_name_surname, _age){
        gender = "female";
    }
};

class Alien : public Entity, public BankClient {
    bool hasGovernmentPermission;
public:
    Alien() {
        species = "alien";
    }

    Alien(std::string _name_surname, int _age) : Entity(_name_surname, _age){
        species = "alien";
    }

    void greet() override {
        std::cout << "!&$:209#@;%  @#%2;:$!90&!  (Hello, mr cashier!)\n";
    }

    bool hasGovPerm(){
        return hasGovernmentPermission;
    }
};

class Game {
    int highScore = 0;
    int currentScore = 0;
    bool active = true;
public:

    void play(){
        active = true;
        while (active) {

        }

    }

    void stop() {
        active = false;
    }

    int getHighScore() {
        return highScore;
    }
};

int main() {


    for (int i = 0; i < 20; ++i){
        Man MAN("random");
        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
        << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << '\n';
    }
    std::cout << "\n\n\n\n";
    for (int i = 0; i < 20; ++i){
        Woman MAN("random");
        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
                  << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << '\n';
    }
    
    Alien al;
}
