#include <iostream>
#include "Fish.h"
#include <array>
#include <ctime>
#include <algorithm>

void PrintField(std::array<Empty *, 9>& field){
    int i = 0;
    for(auto& el : field){
        std::cout << i << ": " << el->GetName() << std::endl;
        i++;
    }
}
int main() {
    int sector;
    bool game = true;
    int countEmpty = 0, countBoot = 0;
    std::array<Empty *, 9> field;
    Empty* ptrEmpty = new Empty();
    Empty* ptrBoot = new Boot();
    Empty* ptrFish = new Fish();
    for(auto& el : field){
        el = ptrEmpty;
    }
    std::srand(std::time(nullptr));
    field.at(std::rand() % 9) = ptrFish;
    while (countBoot < 3){
        int i = std::rand() % 9;
        if(field.at(i)->GetType() != FieldType::empty) continue;
        else{
            field.at(i) = ptrBoot;
            countBoot++;
        }
    }
    PrintField(field);
    ///////////////////////////////
    while (game) {
        while (true) {
            std::cout << "Input sector number(from 0 to 8): ";
            std::cin >> sector;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Bad input! Try again." << std::endl;
            }
            else if(sector < 0 || sector > 8){
                std::cout << "Bad input! Try again." << std::endl;
            }
            else break;
        }
        try {
            field.at(sector)->cast();
        }
        catch (NewException &exc) {
            std::cout << exc.what() << std::endl;
            if (exc.GetType() == FieldType::fish) {
                std::cout << "Game over! You caught a fish in " << ++countEmpty << " attempts." << std::endl;
                game = false;
            }
            else if(exc.GetType() == FieldType::empty){
                countEmpty++;
            }
            else if (exc.GetType() == FieldType::boot) {
                std::cout << "Game over!" << std::endl;
                game = false;
            }
        }
    }
    return 0;
}
