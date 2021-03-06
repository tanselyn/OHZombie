//
//  project2.h
//  OHZombie
//
//  Created by Hannah Wang on 10/17/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#ifndef OHZombie_project2_h
#define OHZombie_project2_h

#include <deque>
#include <string>
#include "binary_priority_queue.h"
#include "pairing_priority_queue.h"
#include "poorman_priority_queue.h"
#include "sorted_priority_queue.h"
#include "eecs281_priority_queue.h"

struct Player {
    int quiverCap;
    int health;
    
    Player(): quiverCap(0), health(0) {}
};


struct Zombie {
    std::string name;
    int distance;
    int speed;
    int health;
    int rounds;
    bool alive;
    
    Zombie(): name("a"), distance(0), speed(0), health(0), rounds(1),
    alive(true) {}
    
    Zombie(std::string name, int distance, int speed, int health):
    name(name), distance(distance), speed(speed),
    health(health), rounds(1), alive(true) {}
    
};

struct CompareZombie {
    bool operator() (Zombie* lhs, Zombie* rhs) const {
        int lhsEta = lhs->distance / lhs->speed;
        int rhsEta = rhs->distance / rhs->speed;
        if (lhsEta == rhsEta) {
            if (lhs->health == rhs->health) {
                return lhs->name > rhs->name;
            }
            else return lhs->health > rhs->health;
        }
        else return lhsEta > rhsEta;
    }
};

struct CompareMostRounds {
    bool operator() (Zombie lhs, Zombie rhs) const {
        if (lhs.rounds == rhs.rounds) {
            return lhs.name > rhs.name;
        }
        return lhs.rounds < rhs.rounds;
    }
};

struct CompareLeastRounds {
    bool operator() (Zombie lhs, Zombie rhs) const {
        if (lhs.rounds == rhs.rounds) {
            return lhs.name < rhs.name;
        }
        return lhs.rounds < rhs.rounds;
    }
};

void readInput(Player &you, int &seed, int &maxDistance,
               int &maxSpeed, int &maxHealth);


#endif