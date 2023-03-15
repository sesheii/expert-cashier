#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <iomanip>
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
    bool hasGovernmentPermission;
public:

    bool hasGovPerm(){
        return hasGovernmentPermission;
    }
    void createAccount() {
        if (registered) {
            std::cout << "This person is registered already.\n";
            return;
        }
        ID = randomNumber(10000000, 99999999);
        balance = 0;
        registered = true;
    }

    bool isRegistered() {
        return registered;
    }

    void accountWithdraw(uint64_t amount) {
        balance -= amount;
    }

    void accountDeposit(uint64_t amount) {
        balance += amount;
    }

    int getAccountID() {
        return ID;
    }

    uint64_t getBalance(){
        return balance;
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
            if (randomNumber(0, 9)) { /// 10% chance to get no bank account
                this->createAccount();
                this->accountDeposit(randomNumber(0, 5000));
            }
            gender = "male";
            age = randomNumber(0, 80);
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
            age = randomNumber(0, 80);
            name_surname = female_names[randomNumber(0,female_names.size()-1)] + ' '
                           + female_surnames[randomNumber(0,female_surnames.size()-1)];
        }
    }
    Woman(std::string _name_surname, int _age) : Human(_name_surname, _age){
        gender = "female";
    }
};

class Alien : public Entity, public BankClient {
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
};

void DisplayOptions(){
    std::cout <<
                 "\nChoose your next action by typing in a number:\n"
                 "| 1. fulfil the request\n"
                 "| 2. deny the request\n"
                 "| 3. check alien government permission\n"
                 "| 4. check balance\n"
                 "| 5. check whether account exists\n"
                 "| 6. register an account\n"
                 "| 7. remind about a request type\n"
                 "----------------------------------------------\n";
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
    if (person->getAge() < 16) {
        message += person->getNameSurname() + " You miscalculated. is too young to have a bank account.\n";
        count++;
    }

    if (!person->isRegistered() && person->getBalance() > 0) {
        message += person->getNameSurname() + "'something's wrong or the person has done same malicious manipulations. ";
//                                                 " Yet you still have fulfilled " + ( (person->getGender() == "male") ? "his" : "her")  + " request\n";
        count++;
    }
    if (!person->isRegistered()) {
        message += person->getNameSurname() + " Is not registered in the bank. ";
//                                                 " Yet you still have fulfilled " + ( (person->getGender() == "male") ? "his" : "her")  + " request\n";
        count++;
    }
    if (person->getSpecies() == "alien" && !person->hasGovPerm()){
        message += "This alien doesn't have government's permission. ";
    }
    if (count > 0) std::cout << message << '\n';
    return count;
}


class withdrawalRequest : public Request_ {
    bool handleRequest(Human* person) override {

        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout << "Client: Hello, my full name is " << person->getNameSurname() << ", my ID is "
        << person->getAccountID() << " and I would like to withdraw " <<
        randomNumber(0, 3000) << " UAH from my bank account balance.\n";

        while (!resolved) {
            DisplayOptions();

            int i;
            std::cin >> std::ws >> i;

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

            else if (i == 3) {
                if (person->getSpecies() == "human") {
                    std::cout << "This person is not an alien so doesn't need this permission.\n";
                }
                else {
                    std::cout << person->hasGovPerm();
                }
            }

            else if (i == 4){
                std::cout << person->getNameSurname() << " currently has " << person->getBalance() << " UAH on "
                << (person->getGender() == "male" ? "his" : "her") << " bank account.\n";
            }

            else if (i == 5) {
                std::cout << person->getNameSurname() << ' ' << (person->isRegistered() ? "Has a bank account.\n" : "Doesn't have a bank account.\n");
            }

            else if (i == 6) {
                person->createAccount();
            }

            else if (i == 7) {
                std::cout << person->getNameSurname() << " with ID " << person->getAccountID() << " wants to withdraw money.\n";
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
            std::cout << "Press Enter to Continue";
            std::cin.ignore();
            std::string myString = "";
            std::getline(std::cin, myString);
            if (myString.length() != 0) stop();
        }
    }

}

int main() {

    Game instance1;
    instance1.play();



//    for (int i = 0; i < 20; ++i){
//        Man MAN("random");
//        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
//        << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << "; balance: " << MAN.getBalance() <<
//        "; isReg: " << MAN.isRegistered() << '\n';
//    }
//    std::cout << "\n\n\n\n";
//    for (int i = 0; i < 20; ++i){
//        Woman MAN("random");
//        std::cout << "name_surname: " << MAN.getNameSurname() << "; age: "
//                  << MAN.getAge() << "; ID:" << MAN.getAccountID() << "; species:" << MAN.getGender() << "; balance: " << MAN.getBalance() <<
//                  "; isReg: " << MAN.isRegistered() << '\n';
//    }

//    Alien al;
}
