//
// Created by konstantin on 29.09.22.
//
#include "living.h"

clown::clown(std::string name, int temp[]) {
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

    this->list_of_priority[0] = state::seaweed;
    this->list_of_priority[1] = state::kril;

    this->point_hide.first = -1;
    this->point_hide.second = -1;
}

std::string clown::who() {return "рыба-клоун "+name;}

bool clown::check_die() {
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
    };
}

clown::~clown() {
    delete this;
}

std::string clown::getInfo() {
    return "Age: " + std::to_string(this->age) + "\tSize: " + std::to_string(this->size)+
           "\tSex: " + std::to_string(this->living_sex) + "\tHunger: " + std::to_string(this->hunger);
}

state clown::getType() {
    return state::clown;
}

bool clown::hide(const std::vector<std::vector<std::vector<struct living *>>> & field){
    can_hide = false;

    for(auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
            if (alive->getSize() > 20) {
                point_hide.first = points.first;
                point_hide.second = points.second - 1;
                can_hide = true;
                return true;
            }
        }
    }

    if (points.first > 0) {
        for (auto &alive: field.at(points.first - 1).at(points.second)) {
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getSize() > 20) {
                    point_hide.first = points.first;
                    point_hide.second = points.second - 1;
                    can_hide = true;
                    return true;
                }
            }
        }
    }

    if (points.second > 0) {
        for (auto &alive: field.at(points.first).at(points.second - 1)) {
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getSize() > 20) {
                    point_hide.first = points.first;
                    point_hide.second = points.second - 1;
                    can_hide = true;
                    return true;
                }
            }
        }
    }

    if (points.first < field.size() - 1) {
        for (auto &alive: field.at(points.first + 1).at(points.second)) {
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getSize() > 20) {
                    point_hide.first = points.first;
                    point_hide.second = points.second - 1;
                    can_hide = true;
                    return true;
                }
            }
        }
    }

    if (points.second < field.at(0).size()-1) {
        for (auto &alive: field.at(points.first).at(points.second + 1)) {
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getSize() > 20) {
                    point_hide.first = points.first;
                    point_hide.second = points.second - 1;
                    can_hide = true;
                }
            }
        }
    }

    return can_hide;
}

bool clown::eat(living * who,const std::vector<std::vector<std::vector<struct living *>>> & field) {
    if(!food) {
        if (who->hide(field)) {
            std::cout << who->who() << " hid)"<<std::endl;
            return false;
        } else {
            who->setEat(true);
            who->setStop();
            hunger += 10;
            std::cout << who->who() << " was eaten("<<std::endl;
            return true;
        }
    }

    return false;
}

bool clown::propagate() {
    return this->propogate;
}

std::pair<int, int> clown::go(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;
    step++;

    if(check_die()){
        std::cout<<who()<<" dies and can't move anywhere"<<std::endl;
        return points;
    }else{

        if(point_hide.first != -1 && can_hide){
            return point_hide;
        }

        if(stop || food){
            point.first = -1;
            point.second = -1;
        }else {
            point = see(field);
            hunger -= 5;
            if (step % 2 == 0) {
                age++;
            }
            points.first = point.first;
            points.second = point.second;
        }
        return point;
    }
}

std::pair<int, int> clown::see(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::clown){
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
            if (alive->getType() == state::clown){
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
            if (alive->getType() == state::clown){
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
            if (alive->getType() == state::clown){
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
            if (alive->getType() == state::clown){
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

    for (int i = 0; i < 2; i++) {
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
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
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
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first;
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
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
                        point.first = points.first + 1;
                        point.second = points.second;
                        if(eat(alive, field)){
                            return point;
                        }
                    }
                }
            }
        }

        if (points.second < field.at(0).size() - 1) {
            for (auto &alive: field.at(points.first).at(points.second + 1)) {
                if (alive->getType() == list_of_priority[i]) {
                    if (this->size >= alive->getSize()) {
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

int clown::getSize() {
    return this->size;
}

sex clown::getSex() {
    return this->living_sex;
}

bool clown::getEat() {
    return this->food;
}

void clown::setEat(bool eat) {
    this->food = eat;
}

void clown::setStop() {
    this->stop = true;
}

std::string clown::getName() {
    return this->name;
}

void clown::setPropogate() {
    this->propogate = true;
}

std::pair<int, int> clown::getPoint() {
    return points;
}

