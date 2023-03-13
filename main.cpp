#include <iostream>
#include <vector>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <stdlib.h>

using std::string;
extern std::vector<string> AvailableNames;
extern std::vector<string> AvailableSurnames;

class Account;
class BankAccount;
class BankAccountVIP;

uint64_t randomNumber(uint64_t lower, uint64_t higher) {
    std::uniform_int_distribution number_distribution(lower, higher);
    std::mt19937_64 generator {static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
    return number_distribution(generator);
}

class Account {
public:
    long double balance;
    string ID;
    string type = "UNKNOWN";

    string getID() const {
        return ID;
    }
    void setID(string _id) {
        Account::ID = _id;
    }

    virtual void withdrawMoney(uint64_t val)=0;
    virtual void depositMoney(uint64_t val)=0;
};

class BankAccount : public Account {
public:
    BankAccount() {
        type = "NORMAL";
    }
    void withdrawMoney(uint64_t amount) override {
        balance -= amount*0.75;
    }
    void depositMoney(uint64_t amount) override {
        balance += amount*0.75;
    }
};

class BankAccountVIP : public Account {
public:
    BankAccountVIP(){
        type = "VIP";
    }
    void withdrawMoney(uint64_t amount) override {
        balance -= amount*0.99;
    }
    void depositMoney(uint64_t amount) override {
        balance += amount*0.99;
    }
};

class Person {
    string name_and_surname;/// to look for a person in database
    string age;/// to check whether they can have a bank account
    string id;/// if doesn't start with 097 hand them over to police because it's fake
    bool brought_a_pet; /// if they brought a pet tell them that pets are not allowed inside a bank

    Account* personal_account = nullptr;

public:
    Account *getPersonalAccount() const {
        return personal_account;
    }

    static void setPersonalAccount(Account *personalAccount) {
        personal_account = personalAccount;
    }

public:

    const string &getNameAndSurname() const {
        return name_and_surname;
    }
    void setNameAndSurname(const string &nameAndSurname) {
        name_and_surname = nameAndSurname;
    }


    const string &getAge() const {
        return age;
    }
    void setAge(const string &_age) {
        Person::age = _age;
    }


    const string &getId() const {
        return id;
    }
    void setId(const string &_id) {
        Person::id = _id;
    }


    bool BroughtAPet() const {
        return brought_a_pet;
    }
    void setBroughtAPet(bool broughtAPet) {
        brought_a_pet = broughtAPet;
    }

    static Person generatePerson(const string& _name_and_surname, const string& _age, const string& _id, bool _brought_a_pet, int account_type) {

        Person P;
        P.setNameAndSurname(_name_and_surname);
        P.setAge(_age);
        P.setId(_id);
        P.setBroughtAPet(_brought_a_pet);

        if (account_type == 0) {
            P.personal_account = nullptr;
        }
        else if (account_type == 1) {
            P.personal_account = new BankAccount;
        }
        else if (account_type == 2) {
            P.personal_account = new BankAccountVIP;
        }
        return P;
    }

    static Person generateRandomPerson() {
        return Person::generatePerson( (AvailableNames[randomNumber(0,148)] + AvailableSurnames[randomNumber(0,246)]),
                                       std::to_string(randomNumber(0,120)),
                                       std::to_string(randomNumber(10000, 20000)),
                                       randomNumber(0,15), /// 1/15 chance ~ 6,6%
                                       randomNumber(0,3)); /// ~33,3% chance

    }
};


void createBankAccount(Person& P, string type) {
    if (type == "NORMAL") {
        Account* acc = new BankAccount;
        acc->setID(P.getId());
        P.setPersonalAccount(acc);
    }
    else if (type == "VIP") {
        Account* acc = new BankAccountVIP;
        acc->setID(P.getId());
        P.setPersonalAccount(acc);
    }
    else if (type == "ILLEGAL") {
        Account* acc = new BankAccountVIP;
        acc->setID("9999900000");
        P.setPersonalAccount(acc);
    }
}

void listPrimaryOptions() {
    std::cout << "| Your options: (select one by typing a number)\n"
                 "| 1. Check client's balance before withdrawing\n"
                 "| 2. Point a shotgun at them and shoot\n"
                 "| 3. Look whether they brought an animal with them\n"
                 "| 4. Validate their ID\n"
                 "| 5. Check whether they have a bank account\n"
                 "| 6. Fulfil request without any hesitation\n";
}


class RandomRequestGenerator {
public:
    void generateRequest(Person& P) {

        switch(randomNumber(0,0)) {
            case 0:
            {

                int withdrawal_amount = randomNumber(10, 5000);
                std::cout << "Client: Hello, I would like to withdraw " << withdrawal_amount << "UAH from my balance.\n";
                std::cout << "You: Hello, please wait a minute.\n";
                int temp;

                listPrimaryOptions();

                std::cin >> temp;

                switch (temp) {
                    case 1:
                        if (P.getPersonalAccount() == nullptr) {
                            std::cout << "You don't have a bank account. I'll register one for you and then attempt to fulfil your request\n";
                            Person::setPersonalAccount(P);
                        }
                        if (P.getPersonalAccount()->getID() != P.getId()){
                            std::cout << "You forgot to validate client's ID with bank account's ID and it turned out to be fake\n"
                                         "You were sent to prison.\n"
                                         "GAME OVER.";
                            return;
                        }
                        if (P.BroughtAPet()){
                            std::cout << "You served a client with a pet, which is not allowed in the bank\n"
                                         "You were fired.\n"
                                         "GAME OVER.";
                            return;
                        }


                        if (P.getPersonalAccount()->balance < withdrawal_amount) {
                            std::cout << "Sorry, sir but you don't have enough money to do that. Please leave.\n";
                            return;
                        }
                        else {
                            P.getPersonalAccount()->balance -= withdrawal_amount;
                            std::cout << "Here goes your money sir. Your balance now is " << P.getPersonalAccount()->balance<< " UAH Thanks for choosing our bank.\\n";
                        }

                        break;
                    case 2:
                        std::cout << "The client didn't deserve that...\n"
                                     "You were sent to prison.\n"
                                     "GAME OVER.";
                        return;

                }

                        break;
            }
        }
                break;

            case 1:
                break;
            case 2:
                break;
            default:
                break;
        }
    }
};

int main() {

    bool isAlive = true;

    while (isAlive) {
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; /// clear console
        Person P = Person::generateRandomPerson();

        RandomRequestGenerator::generateRequest(P);


    }


//    std::cout << AvailableNames[randomNumber(0,148)] + ' ' + AvailableSurnames[randomNumber(0,246)];
    return 0;
}


std::vector<string> AvailableNames { /// size() = 149, generate between 0 and 148
    "Andriy", "Oleksiy", "Mykhailo", "Ivan", "Volodymyr", "Dmytro", "Serhiy", "Petro", "Yaroslav", "Bohdan",
    "Taras", "Yevhen", "Orest", "Anatoliy", "Viktor", "Maksym", "Denys", "Kyrylo", "Oleh", "Vitaliy",
    "Roman", "Borys", "Vasyl", "Hryhorii", "Fedir", "Hryhoriy", "Nazar", "Oleksandr", "Anatolii", "Olexandr",
    "Sergiy", "Mykola", "Ihor", "Anton", "Yuriy", "Olexiy", "Yosyp", "Kostyantyn", "Ruslan", "Maksymilian",
    "Olexander", "Dmytrov", "Zakhar", "Lev", "Rostyslav", "Leonid", "Ostap", "Vasyl'", "Bohdan", "Heorhii",
    "Hryts'", "Oksana", "Andrii", "Mstyslav", "Nazar", "Yaroslav", "Vasylyna", "Volodymyr", "Dmytro", "Roman",
    "Mykhailo", "Ivan", "Petro", "Serhiy", "Viktor", "Oleh", "Taras", "Maksym", "Yevhen", "Kyrylo",
    "Orest", "Borys", "Vitaliy", "Hryhorii", "Sergiy", "Fedir", "Vasyl", "Anatoliy", "Hryhoriy", "Ihor",
    "Mykola", "Anton", "Oleksandr", "Yuriy", "Zakhar", "Ruslan", "Kostyantyn", "Olexander", "Lev", "Dmytrov",
    "Olexiy", "Rostyslav", "Leonid", "Ostap", "Vasyl'", "Bohdan", "Heorhii", "Hryts'","Anna", "Maria", "Oksana",
    "Iryna", "Olha", "Tetiana", "Svitlana", "Natalia", "Kateryna", "Yuliya",
    "Mariya", "Daryna", "Veronika", "Yana", "Valentyna", "Liliya", "Halyna", "Zoryana", "Yaroslava", "Ivanna",
    "Olena", "Viktoriya", "Marianna", "Ludmyla", "Nadiya", "Bohdana", "Anastasiya", "Vira", "Solomiya", "Karina",
    "Marta", "Yelyzaveta", "Viktoriia", "Alina", "Oleksandra", "Ivanka", "Inna", "Lyudmyla", "Irina", "Lyubov",
    "Nina", "Zlata", "Olesya", "Anhelina", "Margarita", "Marina", "Valeria", "Iryna", "Nataliya", "Yuliia",
    "Yaroslavna"};

std::vector<string> AvailableSurnames { /// size() = 247, generate between 0 and 246
    "Andrusenko", "Babych", "Berehuliak", "Berezovskyi", "Bilodid", "Bodnarchuk", "Boiko", "Bondarenko", "Bondar",
    "Chornovil", "Chernysh", "Chernyak", "Cherniak", "Danylenko", "Didukh", "Dmytruk", "Dobrianskyi", "Dobrynska",
    "Drozd", "Dubyna", "Dudka", "Dumanskyi", "Dziuba", "Fedirko", "Fedoriv", "Fedun", "Feshchenko", "Fomenko",
    "Franko", "Franchuk", "Galaktionov", "Galich", "Gavrylenko", "Gavryliuk", "Gladkyi", "Gnatenko", "Golub",
    "Golubovych", "Goncharuk", "Gorban", "Gordienko", "Goshovska", "Grabovetska", "Haiduk", "Haran", "Havryliuk",
    "Hayday", "Herasymenko", "Hnatiuk", "Hnatyshyn", "Holovko", "Holovniuk", "Holovnia", "Horodetskyy", "Hrytsyk",
    "Hrytsenko", "Hulko", "Humeniuk", "Humenyuk", "Ivanyshyn", "Ivasiuk", "Kachanovska", "Kalashnik", "Kalyna",
    "Kaminskyi", "Karpyuk", "Kartashova", "Khmelnytskyi", "Khomenko", "Kholodnyi", "Khudoliy", "Khyzhniak", "Kobzar",
    "Kobylianska", "Kobylinska", "Kocherga", "Koliada", "Kondratuk", "Kononenko", "Korpan", "Kovalchuk", "Kovalenko",
    "Kovalska", "Kovtun", "Kozak", "Kozachenko", "Kozytska", "Kravchuk", "Kremenetska", "Kryklyvyi", "Kryvyy",
    "Kucher", "Kudryavtseva", "Kulchytskyi", "Kulynych", "Kushnir", "Kuzma", "Kuznetsova", "Kvitka", "Kvytko",
    "Kyrylenko", "Kyryliv", "Lahuta", "Lapchuk", "Lebedenko", "Levchenko", "Liakh", "Liashko", "Lisova", "Lohvynenko",
    "Lohvyn", "Lomachenko", "Lomovtseva", "Lopatynskyi", "Lukashenko", "Lukianenko", "Lukyanova", "Lupul", "Lyashchuk",
    "Lytvynenko", "Lyubchenko", "Lyubchuk", "Lyubka", "Makarenko", "Makarchuk", "Maksymenko", "Mala", "Malanchuk",
    "Markevych", "Matviienko", "Medvedenko","Melnychuk", "Melnyk", "Melnichenko", "Melnik", "Mikitenko", "Mikloschenko",
    "Mikhailyuk", "Mikhailuk","Miroshnychenko", "Mitin", "Mokrenko", "Monastyrska", "Moroz", "Nahirniak", "Nalysnyk",
    "Nalyvaiko","Narizhnyi", "Nedilko", "Nedostup", "Nedzelskyi", "Nehoda", "Nekrasov", "Nesterenko", "Nesteruk",
    "Nestorenko", "Nezhynska", "Nikitiuk", "Nikitenko", "Nikolaichuk", "Nikolaienko", "Nikolaychuk","Nimchuk", "Nosyk",
    "Novak", "Novikov", "Novytskyi", "Nychyporuk", "Nykytenko", "Ocheretyanyi","Odnoroh", "Ohloblyn", "Ohorodnik",
    "Okara", "Olkhovyk", "Omelchenko", "Onufrienko", "Onyshchenko","Opanasenko", "Opishchuk", "Orlov", "Oros",
    "Orsulik", "Orzhel", "Osadchuk", "Osypenko", "Osyka","Ovcharenko", "Ovchinnikov", "Ovdiienko", "Ovsiienko",
    "Panchenko", "Pankiv", "Panko", "Panteleiev","Pantiukh", "Pashchenko", "Pavlenko", "Pavliuk", "Pavlov", "Pavlyshyn",
    "Pazenko", "Pazych", "Pechko","Pekh", "Pelekh", "Penkovskyi", "Perederii", "Perehrest", "Perepelka", "Perepelytsia",
    "Peresunko","Perfileva", "Petrashenko", "Petrenko", "Petrik", "Petriuk", "Petruk", "Petrunenko", "Petrykiv",
    "Petukhov", "Pichkur", "Pidhirnyi", "Piddubnyi", "Pidhoretskyi", "Pidlisetskyi", "Pidopryhora",
    "Pidvarko", "Pidsadna", "Pilipenko", "Pilipets", "Pinchuk", "Pisarenko", "Pistun", "Pitak","Pityk"
    , "Pivovar", "Pivtorak", "Plakhotniuk", "Platoshyn", "Plyusch", "Pochynok", "Pohorielov",
    "Pokryshka", "Polishchuk", "Poltavets", "Polyakov"};
