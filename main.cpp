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

    bool getRegistered() {
        return registered;
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
            this->accountDeposit(randomNumber(0,5000));
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
            this->accountDeposit(randomNumber(0,4999));
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

int DisplayAndChooseAction(){
    std::cout << "----------------------------------------------\n"
                 "Choose your next action by typing in a number:\n"
                 "| 1. fulfil the request\n"
                 "| 2. deny the request\n"
                 "| 3. check alien government permission\n"
                 "| 4. check balance\n"
                 "| 5. check whether account exists\n"
                 "| 6. register an account\n"
                 "----------------------------------------------\n";
    int t;
    std::cin >> t;
    return t;
}

/// Need some event thingy





class Request_ {
public:
    bool resolved = false;

    virtual bool handleRequest(Human* person) = 0;
    virtual void denyRequest(Human* person) = 0;
    virtual void acceptRequest(Human* person) = 0;
};

int faultCount(Human* person) {
    int count = 0;
    std::string message;
    if (person->getAccountID() < 10000000) {
        message += person->getNameSurname() + "'s ID is fake, because it's value is less than 10e+7.";
//                                                 " Yet you still have fulfilled " + ( (person->getGender() == "male") ? "his" : "her")  + " request\n";
        count++;
    }
    if (!person->getRegistered()) {
        message += person->getNameSurname() + " Is not registered in the bank.";
//                                                 " Yet you still have fulfilled " + ( (person->getGender() == "male") ? "his" : "her")  + " request\n";
        count++;
    }
    if (count > 0) std::cout << message << '\n';
    return count;
}


class withdrawalRequest : public Request_ {
    bool handleRequest(Human* person) override {

        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout << "Client: Hello, my full name is " << person->getNameSurname() << ", my ID is "
        << person->getAccountID() << " and I would like to withdraw " <<
        randomNumber(0, 3000) << " UAH from my bank account balance\n";

        while (!resolved) {
            std::cin.ignore();
            int i = DisplayAndChooseAction();

            if (i == 1)
            {
                resolved = true;
                if (faultCount(person) == 0) {
                    acceptRequest(person);
                    return true;
                }
                else {
                    return false;
                }
            }

            else if (i == 2) {
                resolved = true;
                if (faultCount(person) != 0) {
                    denyRequest(person);
                    return true;
                }
                else {
                    std::cout << "You denied a person without a reason. Game over.\n";
                    return false;
                }
            }

        }
    }

    void denyRequest(Human* person) override {
        std::cout << "Sorry, " << (person->getGender() == "male" ? "sir" : "miss") << ", but I have to deny your request. Please head out.\n";
    }

    void acceptRequest(Human* person) override {
        std::cout << "Here goes your money, " << (person->getGender() == "male" ? "sir" : "miss") << ". Have a great day.\n";
    }
};
class depositRequest : public Request_ {
    bool handleRequest(Human* person) override {

    }

    void denyRequest(Human* person) override {

    }

    void acceptRequest(Human* person) override {

    }
};
class createAccountRequest : public Request_ {
    bool handleRequest(Human* person) override {

    }

    void denyRequest(Human* person) override {

    }

    void acceptRequest(Human* person) override {

    }
};


enum REQUESTS {
    WITHDRAWAL, DEPOSIT, CREATE_ACCOUNT
};

Request_* selectRequest(REQUESTS TYPE) {
    if (TYPE == WITHDRAWAL) {
        Request_* req = new withdrawalRequest;
        return req;
    }
    if (TYPE == DEPOSIT) {

    }
    if (TYPE == CREATE_ACCOUNT) {

    }
}

class Game {
    int highScore = 0;
    int currentScore = 0;
    bool active = true;

public:
    void play();
    void stop() {
        active = false;
    }

    int getHighScore() {
        return highScore;
    }
};

void Game::play(){

    active = true;
    while (active) {

        Human* person = nullptr;

        if (randomNumber(0,1))
            person = new Woman("random");
        else
            person = new Man("random");

        Request_* req = selectRequest(WITHDRAWAL);

        active = req->handleRequest(person);

        if (active) {
//            std::cout << "\nType in Y to continue. Type N to stop the game.";
            std::cout << "Press Enter to Continue";
            std::cin.ignore();
            std::string myString = "";
            std::getline(std::cin, myString);
            if (myString.length() != 0) stop();
        }
//        std::cout << "Hello, my full name is " << person->getNameSurname() << " and I would like to withdraw " << randomNumber(0,1000)
//        << " UAH from my account.\n";
//        DisplayAndChooseAction();

    }

}

int main() {

    Game instance1;
    instance1.play();



//    for (int i = 0; i < 20; ++i){
//        Man MAN("random");
//        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
//        << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << '\n';
//    }
//    std::cout << "\n\n\n\n";
//    for (int i = 0; i < 20; ++i){
//        Woman MAN("random");
//        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
//                  << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << '\n';
//    }
//
//    Alien al;
}
