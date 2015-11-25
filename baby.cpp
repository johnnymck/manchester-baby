#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include "baby.hpp"

using namespace std;

MB::MB(string filepath)
{
    ifstream inputFile;
    inputFile.open(filepath);
    string input;
    if (inputFile.is_open())
    {
        int i = 0;
        while (!inputFile.eof() && i < 32) 
        {
            getline(inputFile, input);
            // Clear CR on Unix.
            if(!input.empty() && input.back() == '\r') input.pop_back();
            // Reverse endianness.
            reverse(input.begin(), input.end());
            this->storeAt(i) = bitset<32>(input).to_ulong();
            i++;
        }
        if (!inputFile.eof())
        {
            cout << "Input file too long! Skipping rest.\n";
        }
    }
}

void MB::run()
{
    while (true)
    {
        //increment
        this->controlInstruction++;
        //fetch
        this->presentInstruction = this->storeAt(this->controlInstruction);
        //decode & operand fetch
        this->decode();
    }
}

void MB::decode()
{
    // Print accumulator.
    if(debug) cerr << "ACC: " << toString(this->accumulator) << "\n";
    // Print instruction index.
    if(debug) cerr << "CI: "<< this->controlInstruction << "\n";
    // Print memory.
    for (int i = 0; i < 32; ++i)
    {
        // Line number.
        cout << setw(2) << i << setw(0) << ": ";
        // RAM contents.
        cout << toString(store[i]) << "\n";
    }
    cout << "\n";
    int instruction = ((this->presentInstruction >> 13) & 7);
    int operand = (this->presentInstruction & 0x31);
    switch (instruction)
    {
        case 0:
            this->jmp(operand);
            break;
        case 1:
            this->jrp(operand);
            break;
        case 2:
            this->ldn(operand);
            break;
        case 3:
            this->sto(operand);
            break;
        case 4:
            this->sub(operand);
            break;
        case 5:
            this->sub(operand);
            break;
        case 6:
            this->cmp();
            break;
        case 7:
            this->stp();
            break;
    }
}

string MB::toString(int32_t word)
{
    string s = bitset<32>(word).to_string();
    reverse(s.begin(), s.end());
    return s;
}

void MB::jmp(int32_t operand)
{
    if(debug) cerr << "jmp " << operand << "\n";
    int32_t value = this->storeAt(operand);
    this->controlInstruction = value;
}

void MB::jrp(int32_t operand)
{
    if(debug) cerr << "jrp " << operand << "\n";
    int32_t value = this->storeAt(operand);
    this->controlInstruction = value + this->controlInstruction;
}

void MB::ldn(int32_t operand)
{
    if(debug) cerr << "ldn " << operand << "\n";
    this->accumulator = this->storeAt(operand) ^ 0xFFFFFFFF;
}

void MB::sto(int32_t operand)
{
    if(debug) cerr << "sto " << operand << "\n";
    this->storeAt(operand) = this->accumulator;
}

void MB::sub(int32_t operand)
{
    if(debug) cerr << "sub " << operand << "\n";
    this->accumulator = accumulator - this->storeAt(operand);
}

void MB::cmp()
{
    if(debug) cerr << "cmp\n";
    if (this->accumulator < 0) controlInstruction++;
}

void MB::stp()
{
    cout << "STOP LAMP LIT!" << endl;
    exit(EXIT_SUCCESS);
}
