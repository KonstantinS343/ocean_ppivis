//
// Created by konstantin on 29.09.22.
//

#include "ocean_system.h"
#include "iostream"
#include <iomanip>

void ocean_system::run() {

    std::string menu;
    bool exit = false;

    show_ocean();

    std::cout<<"Enter a symbol(n - next, e - exit, s - state of cell): ";
    menu = check_input_char();

    while (!exit) {
       if(menu == "s" || menu == "S"){
           std::cout << "Enter a points of cell:";
           cell_state(input(0, ocean_field.at(0).size()),
                      input(0, ocean_field.size()));
       }else if(menu == "e" || menu == "E"){
           delete_ocean();
           exit = true;
       }else if(menu == "n" || menu == "N"){
           next();
       }else{
           std::cout<<"Error"<<std::endl;
       }

        if(!exit){
            std::cout<<"Enter a symbol(n - next, e - exit, s - state of cell): ";
            menu = check_input_char();
        }
    }
}

void ocean_system::show_ocean() {
    int counter = 0, memory = 0, jmemory = 0;

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            jmemory = j;
            for(int k = 0; k < 32*ocean_field.at(i).size(); k++){
                std::cout<<"#";
            }
            std::cout<<std::endl;
            memory = 0;
            for(int i_1 = 0; i_1 < 5; i_1++){
                int ocean_size = 0;
                while(ocean_size <= ocean_field.at(i).at(j).size()){
                    if(i_1<ocean_field.at(i).at(j).size()){
                        for(living* alive : ocean_field.at(i).at(j)){
                            if(counter==memory){
                                std::cout<<"\t"<<alive->who()<<std::setw(10)<<"\t|";
                                break;
                            }
                            counter++;
                        }
                    } else {
                        std::cout<<"\t "<<"----- -----"<<std::setw(10)<<"\t|";
                    }

                    j++;
                    counter=0;
                    if(ocean_field.at(i).size()<=j){
                        break;
                    }
                }
                counter=0;
                memory++;
                j = jmemory;
                std::cout<<std::endl;
            }
            break;
        }
    }
    for(int k = 0; k < 32*ocean_field.at(0).size(); k++){
        std::cout<<"#";
    }
    std::cout<<std::endl;

}

void ocean_system::cell_state(int index_2, int index_1) {
    for(int i = 0; i < 20; i++){
        std::cout<<"#";
    }

    std::cout<<"\tCell state( 0 - male, 1 - female):"<<std::endl;

    for(auto & alive : ocean_field.at(index_1).at(index_2)){
        std::cout<<alive->who()<<"\t"<<alive->getInfo()<<std::endl;
    }
    for(int i = 0; i < 20; i++){
        std::cout<<"#";
    }
    std::cout<<std::endl;
}

int ocean_system::input(int begin, int end){
    int user_input;
    std::cin>>user_input;

    while(user_input < (begin + 1)  || user_input >= (end + 1) ){
        std::cout<<"Oops, please, check if the input is correct!\n";
        std::cin.clear();
        std::cin.ignore(255,'\n');
        std::cin>>user_input;
    }
    return user_input - 1;
}

char ocean_system::check_input_char() {

    char temp;
    std::cin>>temp;

    while(temp != 69 && temp != 101 && temp != 78 &&
          temp != 110 && temp != 115  && temp != 83){
        std::cout<<"Something went wrong. Try again."<<std::endl;
        std::cin>>temp;

    }

    return  temp;

}

void ocean_system::next() {

    std::pair<int,int> points;
    int temp[6];
    std::pair<int,int> previous;

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            for(auto & alive: ocean_field.at(i).at(j)){

                if(ocean_field.at(i).at(j).empty()){
                    continue;
                }

                if(alive->getType() == 0){
                    if(alive->getCheckStep()){
                        continue;
                    }

                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        delete alive;
                        continue;
                    }
                   previous.first = alive->getPoint().first;
                   previous.second = alive->getPoint().second;

                   points = alive->go(ocean_field);

                    if(previous.first == points.first && previous.second == points.second) {

                    }else{
                        ocean_field.at(points.first).at(points.second).push_back(alive);

                        for (auto iterator = ocean_field.at(i).at(j).begin();
                             iterator != ocean_field.at(i).at(j).end(); iterator++) {
                            if (*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        if(alive->die_from_other() != nullptr){
                            for (auto iterator = ocean_field.at(points.first).at(points.second).begin();
                                 iterator != ocean_field.at(points.first).at(points.second).end(); iterator++) {
                                if (*iterator == alive->die_from_other()) {
                                    ocean_field.at(points.first).at(points.second).erase(iterator);
                                    break;
                                }
                            }
                            delete alive->die_from_other();
                            alive->victim(nullptr);
                        }
                        continue;
                    }

                   if(alive->propagate() && ocean_field.at(i).at(j).size()<4 && alive->getPropogate_state()){
                       temp[0] = points.first;
                       temp[1] = points.second;
                       temp[2] = 0;
                       temp[3] = alive->getSex();
                       temp[4] = 1;
                       temp[5] = 80;
                       living *new_life = new class shark(alive->getName(), temp);
                       std::cout<<"Was born "<<new_life->getName()<<std::endl;
                       ocean_field.at(previous.first).at(previous.second).push_back(new_life);
                       alive->setPropogate();
                   }

                }else if(alive->getType() == 1){
                    if(alive->getCheckStep()){
                        continue;
                    }
                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        delete alive;
                        continue;
                    }
                    previous.first = alive->getPoint().first;
                    previous.second = alive->getPoint().second;
                    points = alive->go(ocean_field);
                    if(previous.first == points.first && previous.second == points.second) {

                    }else{
                        ocean_field.at(points.first).at(points.second).push_back(alive);

                        for (auto iterator = ocean_field.at(i).at(j).begin();
                             iterator != ocean_field.at(i).at(j).end(); iterator++) {
                            if (*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        if(alive->die_from_other() != nullptr){
                            for (auto iterator = ocean_field.at(points.first).at(points.second).begin();
                                 iterator != ocean_field.at(points.first).at(points.second).end(); iterator++) {
                                if (*iterator == alive->die_from_other()) {
                                    ocean_field.at(points.first).at(points.second).erase(iterator);
                                    break;
                                }
                            }
                            delete alive->die_from_other();
                            alive->victim(nullptr);
                        }
                        continue;
                    }

                    if(alive->propagate() && ocean_field.at(i).at(j).size()<4 && alive->getPropogate_state()){
                        temp[0] = previous.first;
                        temp[1] = previous.second;
                        temp[2] = 0;
                        temp[3] = alive->getSex();
                        temp[4] = 1;
                        temp[5] = 80;
                        alive->setPropogate();
                        living *new_life = new class salmon(alive->getName(), temp);
                        std::cout<<"Was born "<<new_life->getName()<<std::endl;
                        ocean_field.at(previous.first).at(previous.second).push_back(new_life);

                    }

                }else if(alive->getType() == 2){
                    if(alive->getCheckStep()){
                        continue;
                    }

                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }
                    previous.first = alive->getPoint().first;
                    previous.second = alive->getPoint().second;

                    points = alive->go(ocean_field);
                    if(previous.first == points.first && previous.second == points.second) {

                    }else{
                        ocean_field.at(points.first).at(points.second).push_back(alive);

                        for (auto iterator = ocean_field.at(i).at(j).begin();
                             iterator != ocean_field.at(i).at(j).end(); iterator++) {
                            if (*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        if(alive->die_from_other() != nullptr){
                            for (auto iterator = ocean_field.at(points.first).at(points.second).begin();
                                 iterator != ocean_field.at(points.first).at(points.second).end(); iterator++) {
                                if (*iterator == alive->die_from_other()) {
                                    ocean_field.at(points.first).at(points.second).erase(iterator);
                                    break;
                                }
                            }
                            delete alive->die_from_other();
                            alive->victim(nullptr);
                        }
                        continue;
                    }

                    if(alive->propagate() && ocean_field.at(i).at(j).size()<4 && alive->getPropogate_state()){
                        temp[0] = previous.first;
                        temp[1] = previous.second;
                        temp[2] = 0;
                        temp[3] = alive->getSex();
                        temp[4] = 1;
                        temp[5] = 80;
                        alive->setPropogate();
                        living *new_life = new class clown(alive->getName(), temp);
                        std::cout<<"Was born "<<new_life->getName()<<std::endl;
                        ocean_field.at(previous.first).at(previous.second).push_back(new_life);
                    }

                }else if(alive->getType() == 3){
                    if(alive->getCheckStep()){
                        continue;
                    }

                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }
                    previous.first = alive->getPoint().first;
                    previous.second = alive->getPoint().second;

                    points = alive->go(ocean_field);
                    if(previous.first == points.first && previous.second == points.second) {

                    }else{
                        ocean_field.at(points.first).at(points.second).push_back(alive);

                        for (auto iterator = ocean_field.at(i).at(j).begin();
                             iterator != ocean_field.at(i).at(j).end(); iterator++) {
                            if (*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        if(alive->die_from_other() != nullptr){
                            for (auto iterator = ocean_field.at(points.first).at(points.second).begin();
                                 iterator != ocean_field.at(points.first).at(points.second).end(); iterator++) {
                                if (*iterator == alive->die_from_other()) {
                                    ocean_field.at(points.first).at(points.second).erase(iterator);
                                    break;
                                }
                            }
                            delete alive->die_from_other();
                            alive->victim(nullptr);
                        }
                        continue;
                    }

                    if(alive->propagate() && ocean_field.at(i).at(j).size()<4 && alive->getPropogate_state()){
                        temp[0] = previous.first;
                        temp[1] = previous.second;
                        temp[2] = 0;
                        temp[3] = alive->getSex();
                        temp[4] = 1;
                        temp[5] = 80;
                        alive->setPropogate();
                        living *new_life = new class puffer(alive->getName(), temp);
                        std::cout<<"Was born "<<new_life->getName()<<std::endl;
                        ocean_field.at(previous.first).at(previous.second).push_back(new_life);

                    }

                }else if(alive->getType() == 4){
                    points = alive->go(ocean_field);
                    if(alive->getSize() < 0){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }

                }else if(alive->getType() == 5){
                    points = alive->go(ocean_field);
                    if(alive->getSize() < 0){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }

                }else if(alive->getType() == 6){
                    if(alive->getCheckStep()){
                        continue;
                    }

                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }
                    previous.first = alive->getPoint().first;
                    previous.second = alive->getPoint().second;

                    points = alive->go(ocean_field);
                    if(previous.first == points.first && previous.second == points.second) {

                    }else{
                        ocean_field.at(points.first).at(points.second).push_back(alive);

                        for (auto iterator = ocean_field.at(i).at(j).begin();
                             iterator != ocean_field.at(i).at(j).end(); iterator++) {
                            if (*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                                break;
                            }
                        }
                        if(alive->die_from_other() != nullptr){
                            for (auto iterator = ocean_field.at(points.first).at(points.second).begin();
                                 iterator != ocean_field.at(points.first).at(points.second).end(); iterator++) {
                                if (*iterator == alive->die_from_other()) {
                                    ocean_field.at(points.first).at(points.second).erase(iterator);
                                    break;
                                }
                            }
                            delete alive->die_from_other();
                            alive->victim(nullptr);
                        }
                        continue;
                    }

                    if(alive->propagate() && ocean_field.at(i).at(j).size()<4 && alive->getPropogate_state()){
                        temp[0] = previous.first;
                        temp[1] = previous.second;
                        temp[2] = 0;
                        temp[3] = alive->getSex();
                        temp[4] = 1;
                        temp[5] = 80;
                        alive->setPropogate();
                        living *new_life = new class anchovys(alive->getName(), temp);
                        std::cout<<"Was born "<<new_life->getName()<<std::endl;
                        ocean_field.at(previous.first).at(previous.second).push_back(new_life);

                    }

                }else if(alive->getType() == 7){
                    if(alive->getCheckStep()){
                        continue;
                    }

                    if(alive->check_die()){
                        for(auto iterator = ocean_field.at(i).at(j).begin(); iterator != ocean_field.at(i).at(j).end(); iterator++){
                            if(*iterator == alive) {
                                ocean_field.at(i).at(j).erase(iterator);
                            }
                        }
                        delete alive;
                        continue;
                    }
                    previous.first = alive->getPoint().first;
                    previous.second = alive->getPoint().second;

                    points = alive->go(ocean_field);

                    if(points.first != -10){
                        if(previous.first == points.first && previous.second == points.second) {

                        }else{
                            ocean_field.at(points.first).at(points.second).push_back(alive);

                            for (auto iterator = ocean_field.at(i).at(j).begin();
                                 iterator != ocean_field.at(i).at(j).end(); iterator++) {
                                if (*iterator == alive) {
                                    ocean_field.at(i).at(j).erase(iterator);
                                    break;
                                }
                            }
                            continue;
                        }
                    }


                }else{}
            }
        }
    }

    for(int i = 0; i < ocean_field.size(); i++){
        for(int j = 0; j < ocean_field.at(i).size(); j++){
            for(auto & alive: ocean_field.at(i).at(j)) {
                alive->setCheckStep();
            }
        }
    }
    show_ocean();

}
