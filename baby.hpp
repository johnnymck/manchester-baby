#pragma once

#include <cassert>
#include <cstdint>

using namespace std;

class MB
/* Singleton Class for the manchester baby emulator */
{
    public:
        MB(string filepath);
        void run();

    private:
        bool debug = false;
        int32_t store[32];
        int32_t accumulator = 0;
        int32_t controlInstruction = 0;
        int32_t presentInstruction;
        // present instruction register not necissary

        string toString(int32_t word);

        int32_t& storeAt(int idx)
        {
            assert(idx >= 0 && idx < 32);
            return store[idx];
        }

        void load();
        void decode();
        // machine instructions
        void jmp(int32_t operand);
        void jrp(int32_t operand);
        void ldn(int32_t operand);
        void sto(int32_t operand);
        void sub(int32_t operand);
        void cmp();
        void stp();
};
