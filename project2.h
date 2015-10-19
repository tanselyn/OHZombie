//
//  project2.h
//  OHZombie
//
//  Created by Hannah Wang on 10/17/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#ifndef OHZombie_project2_h
#define OHZombie_project2_h

#include <vector>
#include <deque>
#include <stack>
#include <string>

struct Player {
    unsigned int quiverCap;
    unsigned int health;
    
    Player(): quiverCap(0), health(0) {}
};


struct Zombie {
    std::string name;
    int distance;
    int speed;
    int health;
    int rounds;
    
    Zombie(std::string name, int distance, int speed, int health):
            name(name), distance(distance), speed(speed),
            health(health), rounds(0) {}
    
};

struct Compare {
    bool operator() (Zombie &lhs, Zombie &rhs) {
        int lhsEta = lhs.distance / lhs.speed;
        int rhsEta = rhs.distance / rhs.speed;
        if (lhsEta == rhsEta) {
            if (lhs.health == rhs.health) {
                return lhs.name > rhs.name;
            }
            else return lhs.health > rhs.health;
        }
        else return lhsEta > rhsEta;
    }
};

void readInput(Player &you, int &seed, int &maxDistance,
               int &maxSpeed, int &maxHealth);

#endif
