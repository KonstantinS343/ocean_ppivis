//
// Created by konstantin on 29.09.22.
//
#include "living.h"

seaweed::seaweed(const int temp[]) {
    this->size = temp[2];
    this->name = " ";
}

std::string seaweed::who() {return "водоросли "+name;}

std::pair<int,int> seaweed::go(const std::vector<std::vector<std::vector<class living*>>>& field) {

    step++;

    std::pair<int,int> points(0,0);
    return points;
}

void seaweed::setEat(bool eat) {
    size -= 20;
}

bool seaweed::check_die() {
    return true;
}

seaweed::~seaweed() {
    delete this;
}

std::string seaweed::getInfo() {return "\tHP: "+std::to_string(this->size);}

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

}

std::pair<int, int> seaweed::see(const std::vector<std::vector<std::vector<struct living *>>> &) {
    return std::pair<int, int>();
}

int seaweed::getSize() {
    return size;
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

living *seaweed::getEntity() {
    return this;
}
