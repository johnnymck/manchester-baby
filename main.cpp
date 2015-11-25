#include <iostream>
#include <string>
#include "baby.hpp"

using namespace std;

int main(int argc, char** argv)
{
   if (argc < 2) 
    {
        cout << "Error: no input file selected" << endl;
        exit(EXIT_FAILURE);
    } else {
        MB test = MB(string(argv[1]));
        test.run();
    }

    return 0;
}
