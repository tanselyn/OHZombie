/*
 * This file is:
 *
 *   1. An example of a test case. Run `make alltests` to compile all of your
 *   tests. Then you can run `./testRandomZombieGenerator` to run the unit
 *   tests for the Random Zombie Generator (TM).
 *   2. An example of how to use the Random Zombie Generator (TM).
 *
 * You don't need to keep this file.
 */
#include "RandomZombieGenerator.h"

#include <cassert>
#include <iostream>

int main() {
    using onslaught::RandomZombieStats;
    using onslaught::RandomZombieGenerator;

    RandomZombieStats stats{1, 2, 3};
    RandomZombieGenerator generator{0, stats};

    for (int i = 0; i < 1000; i++) {
        std::string name = generator.getNextZombieName();
        int speed = generator.getNextZombieSpeed();
        int distance = generator.getNextZombieDistance();
        int health = generator.getNextZombieHealth();

        std::cout << "Name: " << name << std::endl;
        std::cout << "Speed: " << speed << std::endl;
        std::cout << "Distance: " << distance << std::endl;
        std::cout << "Health: " << health << std::endl;

        assert(0 < speed && speed <= stats.maxRandSpeed);
        assert(0 < distance && distance <= stats.maxRandDistance);
        assert(0 < health && health <= stats.maxRandHealth);
    }
}
