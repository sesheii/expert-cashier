#include "utility.h"
#include <vector>
#include <string>
#include <chrono>
#include <random>

int rn(int lower, int higher) {
    std::uniform_int_distribution distribution(lower, higher);
    std::mt19937_64 timeSeededGenerator {static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
    return distribution(timeSeededGenerator);
}

std::vector<std::string> names {"Andriy", "Borys", "Bohdan", "Danylo", "Denys", "Ihor", "Ivan", "Kyrylo", "Maksym", "Mykhailo",
                                      "Nazar", "Oleh", "Orest", "Oleksandr", "Pavlo", "Roman", "Serhiy", "Taras", "Vadym", "Viktor",
                                      "Volodymyr", "Yaroslav", "Yevhen", "Anatoliy", "Anton", "Artem", "Arseniy", "Artemiy", "Artur",
                                      "Vasyl", "Vitaliy", "Volodymyr", "Hryhoriy", "Dmytro", "Zakhar", "Zinoviy", "Ihor", "Ihor",
                                      "Illia", "Yosyp", "Kostyantyn", "Lev", "Luka", "Marko", "Mykola", "Nestor", "Oleksiy", "Olexiy",
                                      "Pavlo", "Petro", "Rostyslav", "Semen", "Stepan", "Sviatoslav", "Taras", "Teodor", "Yakov",
                                      "Yan", "Yaromir", "Yaroslav", "Yulian", "Zakhar", "Zinoviy", "Bohdan", "Dmytro", "Hryhorii",
                                      "Ihor", "Ivan", "Kyrylo", "Levko", "Mykyta", "Oleksandr", "Pavlo", "Serhii", "Vikentiy",
                                      "Volodymyr", "Yevhenii", "Yosyp", "Zakharii", "Zinovii", "Andrii", "Boryslav", "Bohdan",
                                      "Danylo", "Denys", "Ihor", "Ivan", "Kyrylo", "Maksym", "Mykhailo", "Nazar","Anastasiya", "Anna",
                                      "Oksana", "Kateryna", "Tetiana", "Iryna", "Daria", "Yana", "Olena", "Nadia",
                                        "Olha", "Ivanna", "Mariya", "Nina", "Nataliya", "Halyna", "Yuliya", "Larysa", "Liliya", "Zoryana",
                                        "Yaroslava", "Roksolana", "Veronika", "Valentyna", "Vira", "Viktoriya", "Olesya", "Marianna",
                                        "Taisiya", "Valeriya", "Alina", "Karina", "Sofiya", "Yelyzaveta", "Lyudmyla", "Hanna", "Irina",
                                        "Julia", "Nadiia", "Svitlana", "Viktoriia", "Yevheniia", "Anastasiia", "Khrystyna", "Liliia",
                                        "Viktoria", "Zorya", "Anzhelika", "Bohdana", "Daryna", "Olena", "Oksana", "Ruslana", "Solomiya",
                                        "Vasylina", "Yana", "Yuliia", "Zlata", "Zoryana", "Alisa", "Diana", "Ivanka", "Ivanna", "Ivonna",
                                        "Khrystyna", "Lada", "Lidiia", "Liliia", "Liza", "Marharyta", "Marta", "Nataliia", "Oksana",
                                        "Olena", "Olga", "Orysia", "Polina", "Sofiia", "Svitlana", "Tatiana", "Tetiana", "Ulyana",
                                        "Viktoriia", "Vira", "Yarina", "Yelyzaveta", "Yulianna", "Zlata", "Zoriana", "Zoryana",
                                        "Adriana", "Anhelina", "Bohdanna", "Dana"};

std::vector<std::string> surnames {"Shevchenko", "Kovalenko", "Bondarenko", "Tkachenko", "Kravchenko", "Yakovenko", "Petrov",
                                        "Oliynyk", "Moroz", "Kryvyi", "Bilous", "Kostyuk", "Protsenko", "Hrytsenko", "Kolomiyets",
                                        "Chernysh", "Korol", "Klymchuk", "Mykhailiuk", "Kucher", "Bodnar", "Berezhnyi", "Korniienko",
                                        "Melnichenko", "Holovko", "Yefremov", "Hnatyuk", "Lukashenko", "Stupak", "Voloshyn", "Kucherenko",
                                        "Zaharchuk", "Mamchur", "Soroka", "Mykolenko", "Tymchenko", "Sydorenko", "Chernenko", "Kondratiuk",
                                        "Shulga", "Davydenko", "Kuzmenko", "Kozlov", "Kostyuk", "Rudenko", "Krupa", "Drozd", "Tkachuk",
                                        "Bilokin", "Lysenko", "Petryshyn", "Panchenko", "Datsko", "Golub", "Shcherbak", "Khomenko",
                                        "Dubovyi", "Koval", "Zaharchenko", "Shvets", "Ivanyshyn", "Tymoshenko", "Demchuk", "Shcherban",
                                        "Vakarchuk", "Makarenko", "Humeniuk", "Yermolenko", "Kolomiets", "Ovcharenko", "Kovalenko",
                                        "Rybalko", "Pidhirnyi", "Sokolov", "Zhyvotko", "Zaika", "Dmytruk", "Didyk", "Myskiv", "Savenko",
                                        "Popov", "Chumak", "Kravets", "Romanchuk", "Hrab", "Bereza", "Vasylchenko",
                                        "Kovalenko", "Bondarenko", "Tkachenko", "Kravchenko", "Yakovenko", "Kovalchuk", "Oliynyk",
                                          "Moroz", "Shevchenko", "Bilous", "Kryvetska", "Kostyuk", "Protsenko", "Pavlenko", "Hrytsenko",
                                          "Kolomiyets", "Chernysh", "Korol", "Klymchuk", "Mykhailiuk", "Kucher", "Zaytseva", "Berezhna",
                                          "Korniyenko", "Boiko", "Melnichenko", "Holovko", "Yefremova", "Hnatyuk", "Lukashenko", "Stupak",
                                          "Voloshyna", "Kucherenko", "Zakharchenko", "Mamchur", "Soroka", "Mykolenko", "Tymchenko",
                                          "Sydorenko", "Chernenko", "Oliynyk", "Kondratiuk", "Trotsenko", "Davydenko", "Kuzmenko", "Kozlova",
                                          "Kostyuk", "Rudenko", "Krupa", "Sydorova", "Drozd", "Tkachuk", "Bilokon", "Lysenko", "Petryshyn",
                                          "Panchenko", "Datsko", "Golub", "Shcherbak", "Khomenko", "Dubovyi", "Koval", "Zaharchuk",
                                          "Shvets", "Ivanyshyn", "Tymoshenko", "Demchuk", "Shcherban", "Vakarchuk", "Makarenko", "Humeniuk",
                                          "Yermolenko", "Kolomiets", "Ovcharenko", "Kovalenko", "Rybalko", "Pidhirna", "Sokolova",
                                          "Zhyvotko", "Zaika", "Dmytruk", "Didyk", "Myskiv", "Savenko", "Popova", "Chumak", "Krysanova",
                                          "Kravets", "Kopiyka", "Romanchuk", "Hrab", "Bereza", "Vasylchenko"};
