#include <iostream>
#include "oceanfield/ocean.h"
#include "system/ocean_system.h"
#include "system/file.h"

int input(int,int); //проверка ввода
ocean_system* read_from_file();// чтение из файла

int main() {
    setlocale(LC_ALL,"ru");
    srand(time(NULL));
    int menu;

    do {
        system("clear");
        std::cout << "1.NEW GAME;\n2.EXIT"<<std::endl;// меню игры
        menu = input(1, 2);//проверка наввод
        if(menu == 2){
            return 0;
        }
        system("clear");
        ocean_system *ocean = read_from_file();
        ocean->run();
    } while (true);
}

int input(int begin, int end){
    int user_input;
    std::cin>>user_input;

    while(user_input < begin || user_input > end ){
        std::cout<<"Oops, please, check if the input is correct!\n";
        std::cin.clear();
        std::cin.ignore(255,'\n');
        std::cin>>user_input;
    }
    return user_input;
}

ocean_system* read_from_file(){
    std::string name_file;
    std::cout<<"Enter a name of file: ";
    std::cin>>name_file;
    std::fstream load_from_file;
    load_from_file.exceptions(std::fstream::badbit | std::fstream::failbit);

    try{
        load_from_file.open(name_file, std::ifstream::in);
    }catch (const std::exception& e){
        std::cout<<e.what()<<std::endl;
    }

    ocean_system *system = new file(load_from_file);
    load_from_file.close();

    return system;
}
