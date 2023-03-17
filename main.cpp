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
    virtual void TellDepositQuery(uint64_t amount) = 0;
    virtual void TellLoanQuery(uint64_t amount, uint64_t years) = 0;
    virtual void TellRobQuery(int lower, int higher) = 0;

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

    void deposit_displayOptions(){
        std::cout << "Type in a number that corresponds to the text next to it.\n"
                     "| 1. accept the query\n"
                     "| 2. deny the query\n"
                     "| 3. check whether ID is fake\n"
                     "| 4. check whether the person can use bank\n"
                     "==========================================================\n";
    }

    void loan_displayOptions(){
        std::cout << "Type in a number that corresponds to the text next to it.\n"
                     "| 1. accept the query\n"
                     "| 2. deny the query\n"
                     "| 3. check whether ID is fake\n"
                     "| 4. check whether the person can use bank\n"
                     "| 5. check person's income\n"
                     "==========================================================\n";
    }

    void robbery_displayOptions(){
        std::cout << "Type in a number that corresponds to the text next to it.\n"
                     "| 1. give all money\n"
                     "| 2. shoot them with shotgun\n"
                     "| 3. try to guess number\n"
                     "==========================================================\n";
    }

    int handleQuery() {
        if (type == "withdrawal"){
            uint64_t withdrawal_amount = rn(1,5000);

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
                            std::cout << " (-30 points)";
                            points -= 30;
                        }
                        else {
                            std::cout << " (-20 points)";
                            points -= 20;
                        }
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
        else if (type == "deposit"){
            uint64_t deposit_amount = rn(1,5000);

            person->greetCashier();
            person->TellDepositQuery(deposit_amount);

            std::cout << '\n';
            deposit_displayOptions();

            while (!resolved) {
                int t;
                std::cin >> t;

                if (t == 1) {
                    std::string error_message = "ERROR: ";

                    if (person->getId().substr(5,4) == "FAKE"){
                        error_message += "This person's ID is fake; ";
                        points -= 15;
                    }
                    if (!person->ableToUseBank()){
                        error_message += "This person is banned from using bank; ";
                        points -= 15;
                    }

                    if (person->getAccountType() == "VIP" && points < 0) {
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

                    if (person->getId().substr(5,4) != "FAKE" && person->ableToUseBank())
                    {
                        std::cout << "This person was not guilty of anything\n";

                        if (person->getAccountType() == "VIP") {
                            std::cout << " (-30 points)";
                            points -= 30;
                        }
                        else {
                            std::cout << " (-20 points)";
                            points -= 20;
                        }
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
                    std::cout << person->getName() << ' ' << (person->ableToUseBank() ? "can use bank\n" : "is banned from using bank\n");
            }
        }
        else if (type == "robbery") {
            person->greetCashier();
            int higher = rn(0, 100);
            int lower = rn(0, higher);
            person->TellRobQuery(lower, higher);
            robbery_displayOptions();
            int j;
            std::cin >> j;
            if (j == 3){
                int answer = rn(lower, higher);

                int max_guesses = 0;
                int powOf2 = 1;
                while (powOf2 <= answer) {
                    powOf2 <<= 1;
                    max_guesses++;
                }

                for (int i = 0; i < max_guesses; ++i) {
                    int t;
                    std::cin >> t;
                    if (t == answer) {
                        std::cout << "You defeated the robber! (+15 points)\n";
                        points += 15;
                        resolveQuery();
                        return points;
                    }
                    if (t > answer) {
                        std::cout << "Too high!\n";
                    } else {
                        std::cout << "Too low!\n";
                    }
                }

                std::cout << "You lost! (-50 points)\n";
                points -= 50;
            }
            else if (j == 1) {
                std::cout << "You lost! (-50 points)\n";
                points -= 50;
                return points;
            }

            else if (j == 2) {
                if (rn(0,1)){
                    std::cout << "You lost! (-50 points)\n";
                    points -= 50;
                    return points;
                }
                else {
                    std::cout << "You got lucky! (+20 points)\n";
                    points += 20;
                    return points;
                }

            }

        }

        else if (type == "loan") {

            person->greetCashier();

            int amount = rn(0, 10000);
            int years = rn(1, 30);
            person->TellLoanQuery(amount, years);

            loan_displayOptions();

            while (!resolved) {
                int t;
                std::cin >> t;

                if (t == 1) {
                    std::string error_message = "ERROR: ";

                    if (person->getIncome()*years < amount){
                        error_message += "This person isn't able to pay off a loan; ";
                        points -= 15;
                    }
                    if (person->getId().substr(5, 4) == "FAKE") {
                        error_message += "This person's ID is fake; ";
                        points -= 10;
                    }
                    if (!person->ableToUseBank()) {
                        error_message += "This person is banned from using bank; ";
                        points -= 10;
                    }

                    if (person->getAccountType() == "VIP" && points < 0) {
                        points = -5; ///that's right
                    }


                    if (points < 0) {
                        std::cout << error_message
                                  << "\nYou made a mistake while dealing with client. Your points decreased by "
                                  << points
                                  << " points\n";
                    } else {
                        if (person->getAccountType() == "VIP") {
                            std::cout << "You successfully handled the task. Good job! (+10 points)\n";
                            points += 10;
                        } else {
                            std::cout << "You successfully handled the task. Good job! (+5 points)\n";
                            points += 5;
                        }
                    }

                    this->resolveQuery();
                }

                else if (t == 2) {

                    if (person->getId().substr(5,4) != "FAKE"
                    && person->ableToUseBank()
                    && person->getIncome()*years >= amount)
                    {
                        std::cout << "This person was not guilty of anything\n";

                        if (person->getAccountType() == "VIP") {
                            std::cout << " (-30 points)";
                            points -= 30;
                        }
                        else {
                            std::cout << " (-20 points)";
                            points -= 20;
                        }
                    }

                    else {
                        if (person->getAccountType() == "VIP") {
                            std::cout << "You successfully handled the task. Good job! (+11 points)\n";
                            points += 11;
                        }
                        else {
                            std::cout << "You successfully handled the task. Good job! (+7 points)\n";
                            points += 7;
                        }
                    }

                    this->resolveQuery();
                }

                else if (t == 3)
                    std::cout << person->getName() << "'s ID is " << person->getId() << '\n';
                else if (t == 4)
                    std::cout << person->getName() << ' ' << (person->ableToUseBank() ? "can use bank\n" : "is banned from using bank\n");
                else if (t == 5)
                    std::cout << person->getName() << "'s income is " << person->getIncome() << '\n';
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

    void TellRobQuery(int lower, int higher) override {
        std::cout << "HAHA, i'm a robber. Give me all your money or die or guess a number between "
        << lower << " and " << higher << " and have a nice day\n";
    }

    void TellLoanQuery(uint64_t amount, uint64_t years) override {
        std::cout << "I would like to take a loan in the size of " + std::to_string(amount) + " UAH for " << years << " years with a 0 interest rate.\n";
    }

    void TellDepositQuery(uint64_t amount) override {
        std::cout << "I would like to deposit " + std::to_string(amount) + " UAH into my bank account.\n";
    }

    void TellWithdrawalQuery(uint64_t amount) override {
        std::cout << "I would like to withdraw " + std::to_string(amount) + " UAH from my bank account.\n";
    }
};

class Alien : public Humanoid {

public:
    Alien() : Humanoid() {
        species = "alien";
    }

    Alien(std::string name_, int age_, bool canUseBank_, std::string ID_, std::string accountType_, uint64_t balance_, uint64_t income_)
            : Humanoid(name_, age_, canUseBank_, ID_, accountType_, balance_, income_) {
        species = "alien";
    }

    void greetCashier() override {
        std::cout << "H3LL0/?.,MY N4M3 1$:; " << this->name << '\n';
    }

    void TellLoanQuery(uint64_t amount, uint64_t years) {
        std::cout << "I W4Nt% T4K3 L0An., " + std::to_string(amount) + " U4H f0R^ " << years << " Y34RS.., 0 1nterest r4te.\n";
    }

    void TellRobQuery(int lower, int higher) override {
        std::cout << "+&$HF, B(!|B ?+!^C D_ S;& ]qd08 ->R0BB3R. G1V3 4LL Y0UR M0N3Y 0R D13 0R GU3$$ NUMB3R B3TW33N "
                  << lower << " 4ND " << higher << " 4ND H4VE 4 N1C3 D4Y\n";
    }

    void TellDepositQuery(uint64_t amount) override {
        std::cout << "%!^*@#~[]|/=&$> ->D3P0S1T " + std::to_string(amount) + " U4H <^%#~!?>.\n";
    }

    void TellWithdrawalQuery(uint64_t amount) override {
        std::cout << "}; '.>>/?]{0(3 A43{//|d:' ;'' ->W1THDR4W " + std::to_string(amount) + " U4H {0(383[X. ]}\\\n";
    }
};


#include <vector>

constexpr int min_points = -50;


int main() {

    std::vector<Humanoid*> clients(rn(20, 120));

    for (auto& i : clients) {
        int random_number = rn(0,3) == 0;

        if (random_number == 0)
            i = new Alien();
        else if (random_number == 1)
            i = new Human();
    }

    std::cout << clients.size() << " clients today!\n";
    int score = 0;
    std::vector<std::string> QUERY_TYPE ={"deposit", "withdrawal", "robbery", "loan"};
    for (auto i : clients){

        std::cout << "\n\n\n\n";

        int random = rn(0,QUERY_TYPE.size()-1);

        Query_ q(QUERY_TYPE[random], i);
        score += q.handleQuery();

        std::cout << "points: " << score << '\n';
        if (score < min_points) {
            std::cout << "GAME OVER. Thanks for playing";
            break;
        }
    }
}
