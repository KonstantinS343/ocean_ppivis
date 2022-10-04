//
// Created by konstantin on 29.09.22.
//
#include "living.h"

anchovys::anchovys(std::string name, int temp[]) {
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

std::string anchovys::who() { return "анчоус " + name;}

bool anchovys::check_die() {
    if(hunger < 10){
        std::cout<<who()<<" died of hunger"<<std::endl;
        return true;
    }else if(age >= 15){
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
anchovys::~anchovys() {
    delete this;
}

std::string anchovys::getInfo() {
    return "Age: " + std::to_string(this->age) + "\tSize: " + std::to_string(this->size)+
           "\tSex: " + std::to_string(this->living_sex) + "\tHunger: " + std::to_string(this->hunger);
}

state anchovys::getType() {
    return state::anchovys;
}

bool anchovys::eat(living * who, const std::vector<std::vector<std::vector<struct living *>>> & field) {
    if(!who->getCheckStep()) {
        if (who->hide(field)) {
            std::cout << who->who() << " hid)" << std::endl;
            return false;
        } else {
            hunger += 10;
            std::cout << who->who() << " was eaten(" << std::endl;
            return true;
        }
    }
    return false;
}

std::pair<int, int> anchovys::go(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;
    step++;
    check_step = true;

    if(step % 3 == 0){
        allow_propogate = true;
    }

    if(check_die()){
        std::cout<<who()<<" dies and can't move anywhere"<<std::endl;
        return points;
    }else{

        if(point_hide.first != -1 && can_hide){
            return point_hide;
        }

        if(stop){
            point.first = points.first;
            point.second = points.second;
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

bool anchovys::propagate() {
    return this->allow_propogate;
}

sex anchovys::getSex() {
    return this->living_sex;
}

int anchovys::getSize() {
    return this->size;
}
void anchovys::victim(living *alive) {
    this->alives = alive;
}

living* anchovys::die_from_other() {
    return nullptr;
}

void anchovys::setStop() {
    this->stop = true;
    this->propogate = true;
}

std::string anchovys::getName() {
    return this->name;
}

void anchovys::setPropogate() {
    this->allow_propogate = false;
    this->propogate = false;
    this->stop = false;
}

bool anchovys::hide(const std::vector<std::vector<std::vector<class living*>>>& field) {
    can_hide = false;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
            if (alive->getAmouont() > 20) {
                point_hide.first = points.first;
                point_hide.second = points.second;
                can_hide = true;
                return true;
            }
        }
    }

    if (points.first > 0) {
        for (auto &alive: field.at(points.first - 1).at(points.second)) {
            if(field.at(points.first - 1).at(points.second).size() > 3){
                break;
            }
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getAmouont() > 20) {
                    point_hide.first = points.first - 1;
                    point_hide.second = points.second;
                    can_hide = true;
                    return true;
                }
            }
        }
    }

    if (points.second > 0) {
        for (auto &alive: field.at(points.first).at(points.second - 1)) {
            if(field.at(points.first).at(points.second-1).size() > 3){
                break;
            }
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getAmouont() > 20) {
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
            if(field.at(points.first + 1).at(points.second).size() > 3){
                break;
            }
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getAmouont() > 20) {
                    point_hide.first = points.first+1;
                    point_hide.second = points.second;
                    can_hide = true;
                    return true;
                }
            }
        }
    }

    if (points.second < field.at(0).size()-1) {
        for (auto &alive: field.at(points.first).at(points.second + 1)) {
            if(field.at(points.first ).at(points.second+ 1).size() > 3){
                break;
            }
            if (alive->getType() == state::corals || alive->getType() == state::seaweed) {
                if (alive->getAmouont() > 20) {
                    point_hide.first = points.first+1;
                    point_hide.second = points.second;
                    can_hide = true;
                }
            }
        }
    }

    return can_hide;
}

std::pair<int, int> anchovys::see(const std::vector<std::vector<std::vector<struct living *>>> & field) {
    std::pair<int,int> point;

    for (auto &alive: field.at(points.first).at(points.second)) {
        if (alive->getType() == state::anchovys && alive != this){
            if(alive->getSex() != living_sex && age > 5){
                point.first = points.first;
                point.second = points.second;
                if(allow_propogate && alive->propagate()) {
                    alive->setStop();
                    allow_propogate = false;
                    return point;

                }
            }
        }
    }

    if (points.first > 0) {
        for (auto &alive: field.at(points.first - 1).at(points.second)) {
            if(field.at(points.first - 1).at(points.second).size() > 3){
                break;
            }
            if (alive->getType() == state::anchovys && alive != this){
                if(alive->getSex() != living_sex && age > 5){
                    point.first = points.first - 1;
                    point.second = points.second;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }

        }
    }

    if (points.second > 0) {
        for (auto &alive: field.at(points.first).at(points.second - 1)) {
            if(field.at(points.first).at(points.second-1).size() > 3){
                break;
            }
            if (alive->getType() == state::anchovys && alive != this){
                if(alive->getSex() != living_sex && age > 5){
                    point.first = points.first ;
                    point.second = points.second - 1;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }
        }
    }

    if (points.first < field.size() - 1) {
        for (auto &alive: field.at(points.first + 1).at(points.second)) {
            if(field.at(points.first + 1).at(points.second).size() > 3){
                break;
            }
            if (alive->getType() == state::anchovys && alive != this){
                if(alive->getSex() != living_sex && age > 5){
                    point.first = points.first + 1;
                    point.second = points.second;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
                }
            }
        }
    }

    if (points.second < field.at(0).size()-1) {
        for (auto &alive: field.at(points.first).at(points.second + 1)) {
            if(field.at(points.first ).at(points.second+ 1).size() > 3){
                break;
            }
            if (alive->getType() == state::anchovys && alive != this){
                if(alive->getSex() != living_sex && age > 5){
                    point.first = points.first;
                    point.second = points.second + 1;
                    if(allow_propogate && alive->propagate()) {
                        alive->setStop();
                        allow_propogate = false;
                        return point;

                    }
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
                if(field.at(points.first - 1).at(points.second).size() > 3){
                    break;
                }
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
                if(field.at(points.first).at(points.second-1).size() > 3){
                    break;
                }
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
                if(field.at(points.first + 1).at(points.second).size() > 3){
                    break;
                }
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
                if(field.at(points.first ).at(points.second+ 1).size() > 3){
                    break;
                }
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
                if(field.at(points.first - 1).at(points.second).size() > 3){
                    continue;
                }
                point.first = points.first - 1;
                point.second = points.second;
                return point;
            }
        }

        if(rands == 1) {
            if (points.second > 0) {
                if(field.at(points.first).at(points.second-1).size() > 3){
                    continue;
                }
                point.first = points.first ;
                point.second = points.second - 1;
                return point;
            }
        }

        if(rands == 2) {
            if (points.first < field.size() - 1) {
                if(field.at(points.first + 1).at(points.second).size() > 3){
                    continue;
                }
                point.first = points.first + 1;
                point.second = points.second;
                return point;
            }
        }

        if(rands == 3) {
            if (points.second < field.at(0).size() - 1) {
                if(field.at(points.first ).at(points.second+ 1).size() > 3){
                    continue;
                }
                point.first = points.first;
                point.second = points.second + 1;
                return point;
            }
        }
    }
}

std::pair<int, int> anchovys::getPoint() {
    return points;
}

int anchovys::getAmouont() {
    return 0;
}

bool anchovys::getCheckStep() {
    return check_step;
}

void anchovys::setCheckStep() {
    this->check_step = false;
}

bool anchovys::getPropogate_state() {
    return this->propogate;
}
