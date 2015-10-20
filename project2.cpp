//
//  main.cpp
//  OHZombie
//
//  Created by Hannah Wang on 10/16/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#include <vector>
#include <deque>
#include <iostream>
#include <getopt.h>
#include <string>
#include "project2.h"
#include "RandomZombieGenerator.h"
#include <fstream>
#include <sstream>

using namespace std;

void readInput(Player &you, int &seed, int &maxDistance,
               int &maxSpeed, int &maxHealth) {
    string label;
    unsigned int nums = 0;
    
    getline(cin, label);
    cin >> label >> nums;
    you.quiverCap = nums;
    
    cin >> label >> nums;
    you.health = nums;
    
    cin >> label >> nums;
    seed = nums;
    
    cin >> label >> nums;
    maxDistance = nums;
    
    cin >> label >> nums;
    maxSpeed = nums;
    
    cin >> label >> nums;
    maxHealth = nums;
}

void fillPoormanQueue(poorman_priority_queue<Zombie*, CompareZombie> &poorQueue,
                      std::deque<Zombie> &zombieList, const int roundCounter,
                      int &listedZombies) {
    if (roundCounter == 1) {
        for (deque<Zombie>::iterator it = zombieList.begin();
             it < zombieList.end(); ++it) {
            poorQueue.push(&(*it));
            ++listedZombies;
        }
    }
    else {
        while (listedZombies < zombieList.size()) {
            poorQueue.push(&zombieList[listedZombies]);
            ++listedZombies;
        }
    }
}

void fillSortedQueue(sorted_priority_queue<Zombie*, CompareZombie> &sortedQueue,
                     std::deque<Zombie> &zombieList, const int roundCounter,
                     int &listedZombies) {
    if (roundCounter == 1) {
        for (deque<Zombie>::iterator it = zombieList.begin();
             it < zombieList.end(); ++it) {
            sortedQueue.push(&(*it));
            ++listedZombies;
        }
    }
    else {
        while (listedZombies < zombieList.size()) {
            sortedQueue.push(&zombieList[listedZombies]);
            ++listedZombies;
        }
    }
    
}

void fillBinaryQueue(binary_priority_queue<Zombie*, CompareZombie> &binaryQueue,
                     std::deque<Zombie> &zombieList, const int roundCounter,
                     int &listedZombies) {
    if (roundCounter == 1) {
        for (deque<Zombie>::iterator it = zombieList.begin();
             it < zombieList.end(); ++it) {
            binaryQueue.push(&(*it));
            ++listedZombies;
        }
    }
    else {
        while (listedZombies < zombieList.size()) {
            binaryQueue.push(&zombieList[listedZombies]);
            ++listedZombies;
        }
    }
}

void fillPairingQueue(pairing_priority_queue<Zombie*, CompareZombie> &pairingQueue,
                      std::deque<Zombie> &zombieList, const int roundCounter,
                      int &listedZombies) {
    if (roundCounter == 1) {
        for (deque<Zombie>::iterator it = zombieList.begin();
             it < zombieList.end(); ++it) {
            pairingQueue.push(&(*it));
            ++listedZombies;
        }
    }
    else {
        while (listedZombies < zombieList.size()) {
            pairingQueue.push(&zombieList[listedZombies]);
            ++listedZombies;
        }
    }
}


// Getopt options for command arguments
static struct option longopts[] = {
    {"help", no_argument, nullptr, 'h'},
    {"container", required_argument, nullptr, 'c'},
    {"statistics", required_argument, nullptr, 's'},
    {"verbose", no_argument, nullptr, 'v'},
    {nullptr, 0, nullptr, 0}
};

int main(int argc, char * argv[]) {
    
    // turn off synchronization
    ios_base::sync_with_stdio(false);
    
    ostringstream os;
    
    bool verbose = false;
    
    char type;
    const char* poorMan = "POOR_MAN";
    const char* sorted = "SORTED";
    const char* binary = "BINARY";
    const char* pairing = "PAIRING";
    string label;
    
    int idx = 0;
    int containerCounter = 0;
    // Initialized to 0. If container argument is poor man,
    // containerMarker equals 1. If sorted, 2. If binary, 3.
    // If pairing, 4. If illegal command line input, stays 0.
    int containerMarker = 0;
    int listedZombies = 0;
    int activeZombies = 0;
    unsigned int statisticNum = 0;
    unsigned int inputNum = 0;
    unsigned int quiverInv = 0;
    
    Player you;
    int seed = 0;
    int maxDistance = 0;
    int maxSpeed = 0;
    int maxHealth = 0;
    
    unsigned int roundCounter = 0;
    unsigned int roundInput = 0;
    unsigned int randZombieNum = 0;
    unsigned int namedZombieNum = 0;
    Zombie* eater = nullptr;
    Zombie* target = nullptr;
    deque<Zombie> zombieList;
    deque<Zombie> deadZombies;
    CompareZombie order1;
    CompareRounds order2;
    
    poorman_priority_queue<Zombie*, CompareZombie> poorQueue(order1);
    sorted_priority_queue<Zombie*, CompareZombie> sortedQueue(order1);
    binary_priority_queue<Zombie*, CompareZombie> binaryQueue(order1);
    pairing_priority_queue<Zombie*, CompareZombie> pairingQueue(order1);
    
    // Follow command line arguments
    while ((type = getopt_long(argc, argv, "hc:s:v", longopts, &idx)) != -1) {
        switch (type) {
            case 'h':
                cout << "Please specify some command line arguments: "
                << "container followed by specify priority queue type, "
                << "statistics followed by a non-neg int for statistics "
                << "at the end of program, and verbose for extra messages.\n";
                exit(0);
                break;
            case 'c':
                ++containerCounter;
                if (poorMan == optarg) containerMarker = 1;
                if (sorted == optarg) containerMarker = 2;
                if (binary == optarg) containerMarker = 3;
                if (pairing == optarg) containerMarker = 4;
                break;
            case 's':
                statisticNum = *optarg - '0';
                break;
            case 'v':
                verbose = true;
                break;
        }
    }
    
    if (containerCounter == 0 || containerCounter > 1) {
        cerr << "Pick only one priority queue type!\n";
        exit(1);
    }
    if (containerMarker == 0) {
        cerr << "This is not an available priority queue type.\n";
        exit(1);
    }
    
    readInput(you, seed, maxDistance, maxSpeed, maxHealth);
    
    cin >> label;
    while (label == "---") {
        ++roundCounter;
        
        if (verbose) {
            os << "Round: " << roundCounter << '\n';
        }
        quiverInv = you.quiverCap;
        
        // Update alive zombies
        for (deque<Zombie>::iterator it = zombieList.begin();
             it < zombieList.end(); ++it) {
            if (it->alive) {
                it->distance = max(0, it->distance - it->speed);
                if (verbose) {
                    os << "Moved: " << it->name << " (health: " << it->health << ")"
                        << '\n';
                }
                if (it->distance == 0) {
                    --you.health;
                    if (you.health == 0) {
                        eater = &(*it);
                    }
                }
            }
        }

        cin >> label >> roundInput;
        
        // Update current round information
        if (roundInput == roundCounter) {
            cin >> label >> inputNum;
            randZombieNum = inputNum;
        
            onslaught::RandomZombieStats stats{maxDistance, maxSpeed, maxHealth};
            onslaught::RandomZombieGenerator generator{seed, stats};
            
            // Create random zombies and add them to deque
            for (int i = 0; i < randZombieNum; ++i) {
                string name = generator.getNextZombieName();
                int speed = generator.getNextZombieSpeed();
                int distance = generator.getNextZombieDistance();
                int health = generator.getNextZombieHealth();
                
                Zombie x(name,distance,speed,health);
                zombieList.push_back(x);
            }
        
            cin >> label >> inputNum;
            namedZombieNum = inputNum;
        
            cin >> label;
            // Create named zombies and add them to deque
            if (inputNum > 0) {
                while (label != "---") {
                    Zombie x(label,0,0,0);
                    cin >> label >> inputNum;
                    x.distance = inputNum;
                    cin >> label >> inputNum;
                    x.speed = inputNum;
                    cin >> label >> inputNum;
                    x.health = inputNum;
                
                    zombieList.push_back(x);
                    cin >> label;
                }
            }
        }
        
        if (verbose) {
            for (int i = listedZombies; i < zombieList.size(); ++i) {
                os << "Created: " << zombieList[i].name << " (distance: "
                    << zombieList[i].distance << ")" << '\n';
            }
        }
        
        if (you.health <= 0) {
            os << "DEFEAT IN ROUND " << roundCounter << "! " << eater->name
                << " ate your brains!" << '\n';
            break;
        }
        
        switch(containerMarker) {
            case 1:
                fillPoormanQueue(poorQueue, zombieList, roundCounter, listedZombies);
                break;
            case 2:
                fillSortedQueue(sortedQueue, zombieList, roundCounter, listedZombies);
                break;
            case 3:
                fillBinaryQueue(binaryQueue, zombieList, roundCounter, listedZombies);
                break;
            case 4:
                fillPairingQueue(pairingQueue, zombieList, roundCounter, listedZombies);
                break;
        }
        
        while (quiverInv > 0) {
            switch(containerMarker) {
                case 1:
                    target = poorQueue.top();
                    break;
                case 2:
                    target = sortedQueue.top();
                    break;
                case 3:
                    target = binaryQueue.top();
                    break;
                case 4:
                    target = pairingQueue.top();
                    break;
            }
            --target->health;
            
            if (target->health == 0)  {
                target->alive = false;
                deadZombies.push_back(*target);
                switch(containerMarker) {
                    case 1:
                        poorQueue.pop();
                        break;
                    case 2:
                        sortedQueue.pop();
                        break;
                    case 3:
                        binaryQueue.pop();
                        break;
                    case 4:
                        pairingQueue.pop();
                        break;
                }
            }
            --quiverInv;
        }
    }

    // All zombies are killed. You survived all rounds.
    if (you.health > 0) {
        os << "VICTORY IN ROUND " << roundCounter << "! " << target->name
        << " was the last zombie. You survived with " << you.health
        << " health left." << '\n';
    }
    
    // If statistics specified on command line:
    if (statisticNum != 0) {
        if (you.health <= 0) {
            for (deque<Zombie>::iterator it = zombieList.begin();
                 it < zombieList.end(); ++it) {
                if (it->alive) {
                    ++activeZombies;
                }
            }
        }
        os << "Zombies still active: " << activeZombies << '\n';
        
        if (!deadZombies.empty()) {
            
            os << "First zombies killed:" << '\n';
            for (int i = 0; i < statisticNum; ++i) {
                if (i >= deadZombies.size()) {
                    break;
                }
                else os << deadZombies[i].name << " " << i + 1 << '\n';
            }
            
            os << "Last zombies killed:" << '\n';
            for (int i = 0; i < statisticNum; ++i) {
                if (i >= deadZombies.size()) {
                    break;
                }
                if (deadZombies.size() < statisticNum) {
                    os << deadZombies[deadZombies.size() - 1 - i].name
                        << " " << deadZombies.size() - i << '\n';
                }
                else os << deadZombies[deadZombies.size() - 1 - i].name
                        << " " << statisticNum - i << '\n';
            }
        }
        
        os << "Most active zombies:" << '\n';
        sort(zombieList.begin(), zombieList.end(), order2);
        if (zombieList.size() <= statisticNum) {
            for (deque<Zombie>::iterator it = zombieList.end() - 1;
                 it >= zombieList.begin(); --it) {
                os << it->name << " " << it->rounds << '\n';
            }
        }
        else {
            for (int i = 0; i < statisticNum; ++i) {
                os << zombieList[zombieList.size() - 1 - i].name << " "
                << zombieList[zombieList.size() - 1 - i].rounds << '\n';
            }
        }
        
        os << "Lease active zombies:" << '\n';
        if (zombieList.size() <= statisticNum) {
            for (deque<Zombie>::iterator it = zombieList.begin();
                 it < zombieList.end(); ++it) {
                os << it->name << " " << it->rounds << '\n';
            }
        }
        else {
            for (int i = 0; i < statisticNum; ++i) {
                os << zombieList[i].name << " "
                    << zombieList[i].rounds << '\n';
        }
        
    }
    
    cout << os.str();
    return 0;
}











