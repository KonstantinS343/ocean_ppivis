//
// Created by konstantin on 29.09.22.
//

#ifndef OCEAN_LIVING_H
#define OCEAN_LIVING_H

#include "../oceanfield/ocean.h"
#include <iostream>

class living;

enum state{
    shark,// 0
    salmon,// 1
    clown,// 2
    puffer,// 3
    corals,// 4
    seaweed,// 5
    anchovys,//6
    kril //7
};

enum sex{
    male,
    female
};

class living{
public:
    virtual std::string who() = 0;//проверка,кто в клетке

    virtual bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) = 0;//метод, чтобы есть

    virtual std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) = 0;//передвижение

    virtual bool propagate() = 0;//размножение

    virtual bool check_die() = 0;//проверка на смерть

    virtual std::string getInfo() = 0;

    virtual state getType() = 0;

    virtual int getSize() = 0;

    virtual sex getSex() = 0;

    virtual bool hide(const std::vector<std::vector<std::vector<class living*>>>&) = 0;

    virtual bool getEat() = 0;

    virtual void setEat(bool) = 0;

    virtual void setStop() = 0;

    virtual std::string getName() = 0;

    virtual void setPropogate() = 0;

    virtual living* getEntity() = 0;

};


class shark : public living{//акула
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    shark(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    living* getEntity() override;

    ~shark();
private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::shark;

    state list_of_priority[4];

    int step = 0;

    bool food = false;

    bool propogate = false;

    bool stop = false;

    living* entity;
};

class salmon : public living{//лосось
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    salmon(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    living* getEntity() override;

    ~salmon();
private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::salmon;

    state list_of_priority[3];

    int step = 0;

    bool food = false;

    bool propogate = false;

    bool stop = false;

    living* entity;
};

class puffer : public living{//фугу
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    puffer(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    living* getEntity() override;

    void setPropogate() override;

    ~puffer();
private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::puffer;

    state list_of_priority[4];

    int step = 0;

    bool food = false;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    living* entity;
};

class clown : public living{//рыба-клоун
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    clown(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    living* getEntity() override;

    ~clown();
private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::clown;

    state list_of_priority[2];

    int step = 0;

    bool food = false;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    living* entity;
};

class anchovys : public living{//анчоус
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    anchovys(std::string, int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    living* getEntity() override;

    ~anchovys();
private:
    int age;

    sex living_sex;

    int size;

    int hunger;

    std::string name;

    std::pair<int,int> points;

    const state type = state::anchovys;

    state list_of_priority[2];

    int step = 0;

    bool food = false;

    bool propogate = false;

    bool stop = false;

    bool can_hide = false;

    std::pair <int,int> point_hide;

    living* entity;
};

class kril : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    kril(int []);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setStop() override;

    std::string getName() override;

    void setPropogate() override;

    living* getEntity() override;

    ~kril();
private:
    int size;

    std::string name;

    const state type = state::kril;

    int hp = 100;

    int step;

    std::pair<int,int> points;

    bool stop = false;

    living* entity;
};

class corals : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    corals(const int[]);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setPropogate() override;

    std::string getName() override;

    void setStop() override;

    living* getEntity() override;

    ~corals();
private:
    int size;

    int step = 0;

    std::string name;

    const state type = state::corals;

    living* entity;
};

class seaweed : public living{
public:
    bool hide(const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::string who()override;

    bool eat(living*, const std::vector<std::vector<std::vector<class living*>>>&) override;

    std::pair<int,int> go(const std::vector<std::vector<std::vector<class living*>>>&) override;

    bool propagate() override;

    bool check_die() override;

    seaweed(const int[]);

    std::string getInfo() override;

    state getType() override;

    std::pair<int,int> see(const std::vector<std::vector<std::vector<class living*>>>&);

    int getSize() override;

    sex getSex() override;

    bool getEat() override;

    void setEat(bool) override;

    void setPropogate() override;

    std::string getName() override;

    void setStop() override;

    living* getEntity() override;

    ~seaweed();
private:
    int size;

    int step = 0;

    std::string name;

    const state type = state::seaweed;

    living* entity;
};

#endif //OCEAN_LIVING_H
