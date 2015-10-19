#include "RandomZombieGenerator.h"

#include <string>
#include <vector>

namespace onslaught {
    const std::vector<std::string> ZOMBIE_NAMES = {
        "paoletti",
        "darden",
        "luum",
        "anna",
        "waleed",
        "spencer",
        "morteza",
        "jessica",
        "nikhill",
        "aary",
        "david",
        "laura",
        "chun",
        "potatobot",
    };
        
    /**
    * C++ Mersenne Twister wrapper class written by
    * Jason R. Blevins <jrblevin@sdf.lonestar.org> on July 24, 2006.
    * Based on the original MT19937 C code by
    * Takuji Nishimura and Makoto Matsumoto.
    */
    class P2random {
    public:
        void srand(int seed);
        unsigned int rand();

        /*
        A C-program for MT19937, with initialization improved 2002/1/26.
        Coded by Takuji Nishimura and Makoto Matsumoto.

        Before using, initialize the state by using init_genrand(seed)
        or init_by_array(init_key, key_length).

        Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
        All rights reserved.

        Redistribution and use in source and binary forms, with or without
        modification, are permitted provided that the following conditions
        are met:

        1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

        3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
        "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
        LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
        A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
        CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
        EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
        PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
        PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
        LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
        NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
        SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

        Any feedback is very welcome.
        http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
        email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
        */
        class MersenneTwister {
        public:
            MersenneTwister(void);
            ~MersenneTwister(void);

            void print(void);

            void init_genrand(unsigned long s);

            unsigned long genrand_int32(void);

        private:
            static const int N = 624;
            static const int M = 397;
            // constant vector a
            static const unsigned long MATRIX_A = 0x9908b0dfUL;
            // most significant w-r bits
            static const unsigned long UPPER_MASK = 0x80000000UL;
            // least significant r bits
            static const unsigned long LOWER_MASK = 0x7fffffffUL;

            unsigned long *mt_;                  // the state vector
            int mti_;                            // mti == N+1 means mt not initialized

            unsigned long *init_key_;            // Storage for the seed vector
            int key_length_;                     // Seed vector length
            unsigned long s_;                    // Seed integer
            bool seeded_by_array_;               // Seeded by an array
            bool seeded_by_int_;                 // Seeded by an integer
        };

    public:
        MersenneTwister mt;
    };

    void P2random::srand(int seed) {
        mt.init_genrand(seed);
    }

    unsigned int P2random::rand() {
        return mt.genrand_int32();
    }
    /**
    * Constructor
    */
    P2random::MersenneTwister::MersenneTwister(void) :
    mt_(new unsigned long[N]), mti_(N + 1),
    init_key_(nullptr), key_length_(0), s_(0),
    seeded_by_array_(false), seeded_by_int_(false) {
        init_genrand(0);
    }

    /**
    * Destructor
    */
    P2random::MersenneTwister::~MersenneTwister(void) {
        delete[] mt_;
        mt_ = nullptr;
    }

    /**
    * Initializes the Mersenne Twister with a seed.
    *
    * \param s seed
    */
    void P2random::MersenneTwister::init_genrand(unsigned long s) {
        mt_[0] = s & 0xffffffffUL;
        for (mti_ = 1; mti_<N; mti_++) {
            mt_[mti_] =
                (1812433253UL * (mt_[mti_ - 1] ^ (mt_[mti_ - 1] >> 30)) + mti_);
            /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
            /* In the previous versions, MSBs of the seed affect   */
            /* only MSBs of the array mt_[].                        */
            /* 2002/01/09 modified by Makoto Matsumoto             */
            mt_[mti_] &= 0xffffffffUL;
            /* for >32 bit machines */
        }
        // Store the seed
        s_ = s;
        seeded_by_array_ = false;
        seeded_by_int_ = true;
    }

    /**
    * Generates a random number on [0,0xffffffff]-interval
    *
    * \return random number on [0, 0xffffffff]
    */
    unsigned long P2random::MersenneTwister::genrand_int32(void) {
        unsigned long y;
        static unsigned long mag01[2] = { 0x0UL, MATRIX_A };
        /* mag01[x] = x * MATRIX_A  for x=0,1 */

        if (mti_ >= N) { /* generate N words at one time */
            int kk;

            if (mti_ == N + 1)   /* if init_genrand() has not been called, */
                init_genrand(5489UL); /* a default initial seed is used */

            for (kk = 0; kk<N - M; kk++) {
                y = (mt_[kk] & UPPER_MASK) | (mt_[kk + 1] & LOWER_MASK);
                mt_[kk] = mt_[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
            }
            for (; kk<N - 1; kk++) {
                y = (mt_[kk] & UPPER_MASK) | (mt_[kk + 1] & LOWER_MASK);
                mt_[kk] = mt_[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
            }
            y = (mt_[N - 1] & UPPER_MASK) | (mt_[0] & LOWER_MASK);
            mt_[N - 1] = mt_[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

            mti_ = 0;
        }

        y = mt_[mti_++];

        /* Tempering */
        y ^= (y >> 11);
        y ^= (y << 7) & 0x9d2c5680UL;
        y ^= (y << 15) & 0xefc60000UL;
        y ^= (y >> 18);

        return y;
    }

    class RandomZombieGenerator::Impl {
    public:
        Impl(int seed, RandomZombieStats stats):
            stats_(stats)
        {
            random_.srand(seed);
        }

        std::string getNextZombieName() {
            int index = zombieCounter;
            zombieCounter++;

            const auto& name = ZOMBIE_NAMES[index % ZOMBIE_NAMES.size()];
            return name + std::to_string(index);
        }

        int getNextZombieSpeed() {
            return getNextInt(stats_.maxRandSpeed);
        }

        int getNextZombieDistance() {
            return getNextInt(stats_.maxRandDistance);
        }

        int getNextZombieHealth() {
            return getNextInt(stats_.maxRandHealth);
        }

    private:
        P2random random_;
        RandomZombieStats stats_;

        int zombieCounter{0};

        int getNextInt(int maxValue) {
            return random_.rand() % maxValue + 1;
        }
    };

    RandomZombieGenerator::RandomZombieGenerator(
        int seed,
        RandomZombieStats stats
    ):
        impl_(*(new RandomZombieGenerator::Impl{seed, stats}))
    {}

    RandomZombieGenerator::~RandomZombieGenerator() {
        delete &impl_;
    }

    std::string RandomZombieGenerator::getNextZombieName() {
        return impl_.getNextZombieName();
    }

    int RandomZombieGenerator::getNextZombieSpeed() {
        return impl_.getNextZombieSpeed();
    }

    int RandomZombieGenerator::getNextZombieDistance() {
        return impl_.getNextZombieDistance();
    }

    int RandomZombieGenerator::getNextZombieHealth() {
        return impl_.getNextZombieHealth();
    }
}
