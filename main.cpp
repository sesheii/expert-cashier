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

    virtual std::string TellWithdrawalQuery(uint64_t amount) = 0;

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

//    std::string getName() {
//        return name;
//    }
//    std::string getSpecies() {
//        return species;
//    }
//    bool ableToUseBank() {
//        return canUseBank;
//    }

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
    Query_(std::string type_, Humanoid* person_) : type(type_), person(person_){}

    void acceptQuery(){
        resolved = true;
    }

    void denyQuery() {
        resolved = true;
    }

    void withdrawal_displayOptions(){
        std::cout << "Type in a number that corresponds to the text nex to it.\n"
                     "| 1. accept the query\n"
                     "| 2. deny the query\n"
                     "| 3. check whether ID is fake\n"
                     "| 4. check whether the person has enough money\n"
                     "| 5. check account type (can be normal or VIP)\n"
                     "==========================================================\n";
    }

    void handleQuery() {
        if (type == "withdrawal"){
            uint64_t withdraw_amount = rn(1,1500);

            person->greetCashier();
            person->TellWithdrawalQuery(withdraw_amount);

            std::cout << '\n';
            withdrawal_displayOptions();
            
            while (!resolved) {
                int t;
                std::cin >> t;
            }
        }
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

    std::string TellWithdrawalQuery(uint64_t amount) override {
        return "I would like to withdraw " + std::to_string(amount) + " UAH\n";
    }
};


#include <vector>

int main() {
    std::vector<Human*> h(100);
    for (auto& i : h)
        i = new Human();

    for (int i = 0; i < 100; ++i)
        std::cout << h[i]->name << ' ' << h[i]->getBalance() << ' ' << h[i]->getId() << ' ' << h[i]->getAccountType() << ' ' << h[i]->getIncome() << ' ' << '\n';
    ///array here
}
