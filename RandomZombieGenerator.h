/*
 * Random Zombie Generator (TM). See `testRandomZombieGenerator.cpp` for an
 * example of how to use it.
 */
#ifndef RANDOM_ZOMBIE_GENERATOR_H
#define RANDOM_ZOMBIE_GENERATOR_H

#include <string>

namespace onslaught {
    // Random zombies stats, as read in by the input.
    struct RandomZombieStats {
        int maxRandDistance;
        int maxRandSpeed;
        int maxRandHealth;
    };

    class RandomZombieGenerator {
    public:
        RandomZombieGenerator(int seed, RandomZombieStats stats);
        ~RandomZombieGenerator();

        // If you really want one of these methods, you can implement it
        // yourself.
        RandomZombieGenerator(const RandomZombieGenerator& other) = delete;
        RandomZombieGenerator(RandomZombieGenerator&& other) = delete;
        void operator=(const RandomZombieGenerator& other) = delete;
        void operator=(RandomZombieGenerator&& other) = delete;

        // The following methods must be called in this order to generate a new
        // zombie. See the spec for a description of all of these fields. See
        // also `testRandomZombieGenerator.cpp` for an example on how to call
        // these methods.
        std::string getNextZombieName();
        int getNextZombieSpeed();
        int getNextZombieDistance();
        int getNextZombieHealth();

    private:
        // Pointer-to-implementation (PIMPL) idiom, so that you don't have to
        // view the packaged random number generator and all that.
        class Impl;
        Impl& impl_;
    };
}

#endif
