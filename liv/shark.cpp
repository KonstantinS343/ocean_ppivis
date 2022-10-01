//
// Created by konstantin on 29.09.22.
//
#include "living.h"

shark::shark(std::string name, int temp[]) {
    this->name = name;
    this->points.first = temp[0];
    this->points.second = temp[1];
    this->age = temp[2];
    if (temp[3] == 0) {
        this->living_sex = male;
    } else {
        this->living_sex = female;
    }
    this->size = temp[4];
    this->hunger = temp[5];

    this->list_of_priority[0] = state::salmon;
    this->list_of_priority[1] = state::puffer;
    this->list_of_priority[2] = state::clown;
    this->list_of_priority[3] = state::anchovys;
}

std::string shark::who() {return "акула " + name;}

bool shark::eat(living* who, const std::vector<std::vector<std::vector<class living*>>>& file) {

    if(who->getType() == list_of_priority[0]){
        hunger+=20;
        std::cout<<who->who()<<" was eaten(";
        who->setStop();
        delete who;
        who = nullptr;
        return true;
    }else{
        if(who->hide(file)){
            std::cout<<who->who()<<" hid)";
            return false;
        }else{
            who->setEat(true);
            who->setStop();
            hunger+=10;
            std::cout<<who->who()<<" was eaten(";
            delete who;
            who = nullptr;
            return true;
        }
    }

}

std::pair<int,int> shark::go(const std::vector<std::vector<std::vector<class living*>>>& field) {

    std::pair<int,int> point;
    step++;

    if(check_die()){
        std::cout<<who()<<" dies and can't move anywhere"<<std::endl;
        return points;
    }else{
        if(stop){
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

bool shark::propagate() {
    return this->propogate;
}

bool shark::check_die() {
    if(hunger < 10){
        std::cout<<who()<<" died of hunger"<<std::endl;
        return true;
    }else if(age >= 25){
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

shark::~shark() {
    delete this;
}

std::string shark::getInfo() {
    return "Age: " + std::to_string(this->age) + "\tSize: " + std::to_string(this->size)+
           "\tSex: " + std::to_string(this->living_sex) + "\tHunger: " + std::to_string(this->hunger);
}

state shark::getType() {
    return state::shark;
}

int shark::getSize() { return size;}

sex shark::getSex() {return living_sex;}

std::pair<int,int> shark::see(const std::vector<std::vector<std::vector<class living*>>>& field) {

    std::pair<int,int> point;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::shark){
            if(alive->getSex() != living_sex && age > 10){
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
            if (alive->getType() == state::shark){
                if(alive->getSex() != living_sex && age > 10){
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
            if (alive->getType() == state::shark){
                if(alive->getSex() != living_sex && age > 10){
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
            if (alive->getType() == state::shark){
                if(alive->getSex() != living_sex && age > 10){
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
            if (alive->getType() == state::shark){
                if(alive->getSex() != living_sex && age > 10){
                    point.first = points.first;
                    point.second = points.second + 1;
                    alive->setStop();
                    alive->setPropogate();
                    return point;
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (auto &alive: field.at(points.first).at(points.second)) {
            if (alive->getType() == list_of_priority[i]){
                if(this->size >= alive->getSize()){
                    point.first = points.first;
                    point.second = points.second;
                    eat(alive, field);
                    return point;
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

bool shark::hide(const std::vector<std::vector<std::vector<class living*>>>& file) {
    return false;
}

bool shark::getEat() {
    return false;
}

void shark::setEat(bool eat) {
    this->food = eat;
}

void shark::setStop() {
    this->stop = true;
}

std::string shark::getName() {
    return this->name;
}

void shark::setPropogate() {
    this->propogate = true;
}

living *shark::getEntity() {
    return this;
}
