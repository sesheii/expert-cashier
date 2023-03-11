#include <iostream>
#include <random>
#include <chrono>
#include <vector>

uint64_t randomNumber(uint64_t lower, uint64_t higher) {
    std::uniform_int_distribution number_distribution(lower, higher);
    std::mt19937_64 generator {static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
    return number_distribution(generator);
}

class Entity {
public:
    std::string age;
    std::string name;

    virtual void go_to_cashier() {
        std::cout << "hi, cashier!\n";
    }
};

static std::vector<Entity>* clients;

class God : public Entity {
public:
    God() {
        name = "Jesus";
        age = std::to_string(1.0/0);
    }

    void createPerson();
    void createAnimal();

    void go_to_cashier() override {
        std::cout << "Long before time had a name, the first Spinjutsu master created Ninjago!...\n";
        /// trigger custom event
    }
};

class Person : public God {

public:

    std::string surname;
    std::string ID;
    std::string occupation;
    std::string income;
};

class Animal : God {

};


void God::createPerson() {
}


int main() {
    Entity* per = new Person();
    std::cout << randomNumber(0, 100);
}


///----------IDEA----------///
/// you are a bank worker
/// people come to you and make a request
/// depending on a request, as a response you look for a person in a bank's database or add to database, or pull out a gun

///----------PERSON----------///
/// has the following attributes: age, occupation, ID number, address, income


///----------BANK ACCOUNT----------///
