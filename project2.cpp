//
//  main.cpp
//  OHZombie
//
//  Created by Hannah Wang on 10/16/15.
//  Copyright (c) 2015 Hannah. All rights reserved.
//

#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <iostream>
#include <getopt.h>
#include <string>
#include "project2.h"
#include "binary_priority_queue.h"
#include "pairing_priority_queue.h"
#include "poorman_priority_queue.h"
#include "RandomZombieGenerator.h"
#include "sorted_priority_queue.h"
#include "eecs281_priority_queue.h"
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

// Getopt options for command arguments
static struct option longopts[] = {
    {"help", no_argument, nullptr, 'h'},
    {"container", required_argument, nullptr, 'c'},
    {"statistics", required_argument, nullptr, 's'},
    {"verbose", no_argument, nullptr, 'v'},
    {nullptr, 0, nullptr, 0}
};

// Poorman Priority Queue Implementations:


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
    unsigned int statisticNum = 0;
    unsigned int inputNum;
    
    Player you;
    int seed = 0;
    int maxDistance = 0;
    int maxSpeed = 0;
    int maxHealth = 0;
    
    unsigned int roundCounter = 1;
    unsigned int roundNum = 0;
    unsigned int randZombieNum = 0;
    unsigned int namedZombieNum = 0;
    deque<Zombie> zombieList;
    Compare order;
    
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
        cin >> label >> roundNum;
        if (roundNum == roundCounter) {
            cin >> label >> inputNum;
            randZombieNum = inputNum;
        
            onslaught::RandomZombieStats stats{maxDistance, maxSpeed, maxHealth};
            onslaught::RandomZombieGenerator generator{seed, stats};
            
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
        
        if (containerMarker == 1) {
            poorman_priority_queue<Zombie*, Compare> poorQueue(order);
            
            for (deque<Zombie>::iterator it = zombieList.begin();
                 it < zombieList.end(); ++it) {
                poorQueue.push(&(*it));
            }
            
        }
        
        if (containerMarker == 2) {
            
            
        }
        
        if (containerMarker == 3) {
            
        }
        
        if (containerMarker == 4) {
            
            
        }
        
        ++roundCounter;
    }

    
    
    
    // If statistics specified on command line:
    if (statisticNum != 0) {
        
    }
    
    
    // If verbose specified on comman line:
    if (verbose) {
        
        
    }
    return 0;
}

