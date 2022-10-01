//
// Created by konstantin on 29.09.22.
//
#include "living.h"

salmon::salmon(std::string name, int temp[]) {
    this->name = name;
    this->age = temp[2];
    this->points.first = temp[0];
    this->points.second = temp[1];
    if(temp[3]== 0){
        this->living_sex = male;
    }else{
        this->living_sex = female;
    }
    this->size = temp[4];
    this->hunger = temp[5];

    this->list_of_priority[0] = state::puffer;
    this->list_of_priority[1] = state::clown;
    this->list_of_priority[2] = state::anchovys;
}

std::string salmon::who() {return "лосось "+name;}

bool salmon::check_die() {
    if(hunger < 10){
        std::cout<<who()<<" died of hunger"<<std::endl;
        return true;
    }else if(age >= 10){
        if( rand()%2 == 0){
            std::cout<<who()<<" just died"<<std::endl;
            return true;
        }else{
            return false;
        }
    }else{
        return  false;
    }
}

salmon::~salmon() {
    delete this;
}

std::string salmon::getInfo() {
    return "Age: " + std::to_string(this->age) + "\tSize: " + std::to_string(this->size)+
          "\tSex: " + std::to_string(this->living_sex) + "\tHunger: " + std::to_string(this->hunger);
}

state salmon::getType() {
    return state::salmon;
}

bool salmon::hide(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    return false;
}

bool salmon::eat(living * who, const std::vector<std::vector<std::vector<struct living *>>> & field) {
    if(!food) {
        if (who->hide(field)) {
            std::cout << who->who() << " hid)";
            return false;
        } else {
            who->setEat(true);
            who->setStop();
            hunger += 10;
            std::cout << who->who() << " was eaten(";
            delete who;
            who = nullptr;
            return true;
        }
    }
}

std::pair<int, int> salmon::go(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;
    step++;

    if(check_die()){
        std::cout<<who()<<" dies and can't move anywhere"<<std::endl;
        return points;
    }else{
        if(stop || food){
            points.first = -1;
            points.second = -1;
        }else {
            point = see(field);
            hunger -= 5;
            if (step % 2 == 0) {
                age++;
            }
        }
        return point;
    }
}

bool salmon::propagate() {
    return this->propogate;
}

std::pair<int, int> salmon::see(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::salmon){
            if(alive->getSex() != living_sex && age >= 3){
                point.first = points.first;
                point.second = points.second;
                alive->setStop();
                alive->setPropogate();
                return point;
            }
        }
    }

    if (points.first > 0) {
        for (auto &alive: field.at(points.first - 1).at(points.second)) {
            if (alive->getType() == state::salmon){
                if(alive->getSex() != living_sex && age >= 3){
                    point.first = points.first - 1;
                    point.second = points.second;
                    alive->setStop();
                    alive->setPropogate();
                    return point;
                }
            }
        }
    }

    if (points.second > 0) {
        for (auto &alive: field.at(points.first).at(points.second - 1)) {
            if (alive->getType() == state::salmon){
                if(alive->getSex() != living_sex && age >= 3){
                    point.first = points.first ;
                    point.second = points.second - 1;
                    alive->setStop();
                    alive->setPropogate();
                    return point;
                }
            }
        }
    }

    if (points.first < field.size() - 1) {
        for (auto &alive: field.at(points.first + 1).at(points.second)) {
            if (alive->getType() == state::salmon){
                if(alive->getSex() != living_sex && age >= 3){
                    point.first = points.first + 1;
                    point.second = points.second;
                    alive->setStop();
                    alive->setPropogate();
                    return point;
                }
            }
        }
    }

    if (points.second < field.at(0).size()-1) {
        for (auto &alive: field.at(points.first).at(points.second + 1)) {
            if (alive->getType() == state::salmon){
                if(alive->getSex() != living_sex && age >= 3){
                    point.first = points.first;
                    point.second = points.second + 1;
                    alive->setStop();
                    alive->setPropogate();
                    return point;
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (auto &alive: field.at(points.first).at(points.second)) {
            if (alive->getType() == list_of_priority[i]){
                if(this->size >= alive->getSize()){
                    point.first = points.first;
                    point.second = points.second;
                    if(eat(alive, field)){
                        return point;
                    }
                }
            }
        }

        if (points.first > 0) {
            for (auto &alive: field.at(points.first - 1).at(points.second)) {
                if (alive->getType() == list_of_priority[i]){
                    if(this->size >= alive->getSize()){
                        point.first = points.first - 1;
                        point.second = points.second;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.second > 0) {
            for (auto &alive: field.at(points.first).at(points.second - 1)) {
                if (alive->getType() == list_of_priority[i]){
                    if(this->size >= alive->getSize()){
                        point.first = points.first ;
                        point.second = points.second - 1;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.first < field.size() - 1) {
            for (auto &alive: field.at(points.first + 1).at(points.second)) {
                if (alive->getType() == list_of_priority[i]){
                    if(this->size >= alive->getSize()){
                        point.first = points.first + 1;
                        point.second = points.second;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.second < field.at(0).size()-1) {
            for (auto &alive: field.at(points.first).at(points.second + 1)) {
                if (alive->getType() == list_of_priority[i]){
                    if(this->size >= alive->getSize()){
                        point.first = points.first;
                        point.second = points.second + 1;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }
    }


    while(true) {
        int rands = rand() % 4;

        if(rands == 0) {
            if (points.first > 0) {
                point.first = points.first - 1;
                point.second = points.second;
                return point;
            }
        }

        if(rands == 1) {
            if (points.second > 0) {
                point.first = points.first ;
                point.second = points.second - 1;
                return point;
            }
        }

        if(rands == 2) {
            if (points.first < field.size() - 1) {
                point.first = points.first + 1;
                point.second = points.second;
                return point;
            }
        }

        if(rands == 3) {
            if (points.second < field.at(0).size() - 1) {
                point.first = points.first;
                point.second = points.second + 1;
                return point;
            }
        }
    }
}

int salmon::getSize() {
    return this->size;
}

sex salmon::getSex() {
    return this->living_sex;
}

bool salmon::getEat() {
    return this->food;
}

void salmon::setEat(bool eat) {
    this->food = eat;
}

void salmon::setStop() {
    this->stop = true;
}

std::string salmon::getName() {
    return this->name;
}

void salmon::setPropogate() {
    this->propogate = true;
}

living *salmon::getEntity() {
    return this;
}

