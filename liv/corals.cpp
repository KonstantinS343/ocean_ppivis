//
// Created by konstantin on 29.09.22.
//
#include "living.h"

corals::corals(const int temp[]) {
    this->size = temp[2];
    this->name = " ";

}

std::string corals::who() {return "кораллы "+name;}


bool corals::propagate() {
    return false;
}

bool corals::check_die() {
    return false;
}

corals::~corals() {
    delete this;
}

std::string corals::getInfo() {return "\tHP: "+std::to_string(this->size);}


state corals::getType() {
    return state::corals;
}

bool corals::eat(living* ,const std::vector<std::vector<std::vector<class living*>>>&) {

}

bool corals::hide(const std::vector<std::vector<std::vector<class living*>>>&) {
    return false;
}

std::pair<int, int> corals::go(const std::vector<std::vector<std::vector<struct living *>>> &) {
    step++;

    std::pair<int,int> points(0,0);
    return points;
}

std::pair<int, int> corals::see(const std::vector<std::vector<std::vector<struct living *>>> &) {
    return std::pair<int, int>();
}

int corals::getSize() {
    return size;
}

bool corals::getEat() {
    return false;
}

void corals::setEat(bool) {
    size -= 20;
}

sex corals::getSex() {
    return female;
}

void corals::setPropogate() {

}

std::string corals::getName() {
    return std::string();
}

void corals::setStop() {

}

living *corals::getEntity() {
    return this;
}

