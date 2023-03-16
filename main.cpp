#include <iostream>
#include <vector>
#include "utility.h"

class BankUser {
private:
    std::string ID;
    std::string accountType;
    uint64_t balance;
    uint64_t income;
public:
    BankUser(std::string ID_, std::string accountType_, uint64_t balance_, uint64_t income_)
    : ID(ID_), accountType(accountType_), balance(balance_), income(income_){}

    BankUser() { /// no arguments - random values
        ID = std::to_string(rn(10000, 99999)) + (rn(0, 9) ? "" : "FAKE"); /// 10% chance of person having fake ID
        accountType = rn(0, 12) ? "NORMAL" : "VIP"; /// 8,(3)% chance of person having VIP account
        balance = rn(0, 12000);
        income = rn(1000, 6000);
    }

    const std::string &getId() const {
        return ID;
    }

    const std::string &getAccountType() const {
        return accountType;
    }

    uint64_t getBalance() const {
        return balance;
    }

    uint64_t getIncome() const {
        return income;
    }

    virtual void TellWithdrawalQuery(uint64_t amount) = 0;

    virtual void greetCashier() = 0;

};

class Humanoid : public BankUser {
public:
    Humanoid(std::string name_, int age, bool canUseBank, std::string ID_, std::string accountType_, uint64_t balance_, uint64_t income_)
    : BankUser(ID_, accountType_, balance_, income_) {
    }

    Humanoid() { /// no arguments - random values
        name = names[rn(0, names.size()-1)] + ' ' + surnames[rn(0,surnames.size()-1)];
        age = rn(0,99);
        canUseBank = rn(0, 9);
        std::vector<std::string> queries {};
    }

    std::string getName() {
        return name;
    }
    std::string getSpecies() {
        return species;
    }
    bool ableToUseBank() {
        return canUseBank;
    }
protected:
    std::string name;
    std::string species;
    int age;
    bool canUseBank;

};


class Query_ {
public:
    bool resolved = false;
    std::string type;
    Humanoid* person;
    int points = 0;
    Query_(std::string type_, Humanoid* person_) : type(type_), person(person_){}
    
    void resolveQuery() {
        resolved = true;
    }

    void withdrawal_displayOptions(){
        std::cout << "Type in a number that corresponds to the text next to it.\n"
                     "| 1. accept the query\n"
                     "| 2. deny the query\n"
                     "| 3. check whether ID is fake\n"
                     "| 4. check whether the person has enough money to withdraw\n"
                     "| 5. check whether the person can use bank\n"
                     "==========================================================\n";
    }

    int handleQuery() {
        if (type == "withdrawal"){
            uint64_t withdrawal_amount = rn(1,1500);

            person->greetCashier();
            person->TellWithdrawalQuery(withdrawal_amount);

            std::cout << '\n';
            withdrawal_displayOptions();

//            person->ID = "00000FAKE";

            while (!resolved) {
                int t;
                std::cin >> t;

                if (t == 1) {
                    std::string error_message = "ERROR: ";
                    
                    if (person->getId().substr(5,4) == "FAKE"){
                        error_message += "This person's ID is fake; ";
                        points -= 15;
                    }
                    if (person->getBalance() < withdrawal_amount){
                        error_message += "This person doesn't have enough money on their bank account; ";
                        points -= 10;
                    }
                    if (!person->ableToUseBank()){
                        error_message += "This person is banned from using bank; ";
                        points -= 15;
                    }
                    
                    if (person->getAccountType() == "VIP" && points > 0) {
                        points = -1; ///that's right
                    }


                    if (points < 0) {
                        std::cout << error_message << "\nYou made a mistake while dealing with client. Your points decreased by " << points
                                  << " points\n";
                    }
                    else {
                        if (person->getAccountType() == "VIP") {
                            std::cout << "You successfully handled the task. Good job! (+10 points)\n";
                            points += 10;
                        }
                        else {
                            std::cout << "You successfully handled the task. Good job! (+5 points)\n";
                            points += 5;
                        }
                    }
                    
                    this->resolveQuery();
                }

                else if (t == 2) {

                    if (person->getId().substr(5,4) != "FAKE"
                    &&  person->getBalance() >= withdrawal_amount
                    &&  person->ableToUseBank())
                    {
                        std::cout << "This person was not guilty of anything\n";

                        if (person->getAccountType() == "VIP") {
                            points -= 30;
                        }
                        else points -= 20;
                    }

                    else {
                        if (person->getAccountType() == "VIP") {
                            std::cout << "You successfully handled the task. Good job! (+10 points)\n";
                            points += 10;
                        }
                        else {
                            std::cout << "You successfully handled the task. Good job! (+5 points)\n";
                            points += 5;
                        }
                    }

                    this->resolveQuery();
                }

                else if (t == 3)
                    std::cout << person->getName() << "'s ID is " << person->getId() << '\n';
                else if (t == 4)
                    std::cout << person->getName() << "'s balance is " << person->getBalance() << " UAH and they want to withdraw "
                    << withdrawal_amount << " UAH\n";
                else if (t == 5)
                    std::cout << person->getName() << ' ' << (person->ableToUseBank() ? "can use bank\n" : "is banned from using bank\n");
            }
        }
        return points;
    }
};

class Human : public Humanoid {

public:
    Human() : Humanoid() {
        species = "human";
    }

    Human(std::string name_, int age_, bool canUseBank_, std::string ID_, std::string accountType_, uint64_t balance_, uint64_t income_)
    : Humanoid(name_, age_, canUseBank_, ID_, accountType_, balance_, income_) {
        species = "human";
    }

    void greetCashier() override {
        std::cout << "Hello! my name is " << this->name << '\n';
    }

    void TellWithdrawalQuery(uint64_t amount) override {
        std::cout << "I would like to withdraw " + std::to_string(amount) + " UAH from my bank account.\n";
    }
};


#include <vector>

constexpr int min_points = -50;


int main() {
    int score = 0;
    while (true){
        std::cout << "\n\n\n\n\n";
        Humanoid* humaa = new Human();
        Query_ q("withdrawal", humaa);
        score += q.handleQuery();

        if (score < min_points) {
            std::cout << "GAME OVER.";
            break;
        }
    }
}
