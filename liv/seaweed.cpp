//
// Created by konstantin on 29.09.22.
//
#include "living.h"

seaweed::seaweed(const int temp[]) {
    this->amount = temp[2];
    this->name = " ";
}

std::string seaweed::who() {return "водоросли "+name;}

std::pair<int,int> seaweed::go(const std::vector<std::vector<std::vector<class living*>>>& field) {

    step++;

    std::pair<int,int> points(0,0);
    return points;
}

void seaweed::setEat(bool eat) {
    amount -= 20;
}

bool seaweed::check_die() {
    return true;
}

seaweed::~seaweed() {
    delete this;
}

std::string seaweed::getInfo() {return "\tHP: "+std::to_string(this->amount);}

state seaweed::getType() {
    return state::seaweed;
}

bool seaweed::propagate() {
    return false;
}

bool seaweed::hide(const std::vector<std::vector<std::vector<class living*>>>&) {
    return false;
}

bool seaweed::eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) {
return false;
}

std::pair<int, int> seaweed::see(const std::vector<std::vector<std::vector<struct living *>>> &) {
    return std::pair<int, int>();
}

int seaweed::getSize() {
    return 0;
}

sex seaweed::getSex() {
    return female;
}

bool seaweed::getEat() {
    return false;
}

void seaweed::setPropogate() {

}

std::string seaweed::getName() {
    return std::string();
}

void seaweed::setStop() {

}

std::pair<int, int> seaweed::getPoint() {
    return std::pair<int, int>();
}

int seaweed::getAmount() {
    return this->amount;
}
