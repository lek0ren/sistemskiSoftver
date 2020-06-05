#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
#include <stdio.h>
#include "../h/assembler.h"
#include "../h/util.h"

int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        std::cout << "Nema dovoljno argumenata" << std::endl;
    }
    else
    {
        char *inputFIle, *outputFile;
        for (int i = 1; i < 4; i++)
        {
            if (argv[i] == std::string("-o"))
            {
                outputFile = argv[i + 1];
                i++;
            }
            else
            {
                inputFIle = argv[i];
            }
        }
        bool ok1 = Assembler::instance().setInputFile(inputFIle);
        bool ok2 = Assembler::instance().setOutputFile(outputFile);
        if (ok1)
        {
            Assembler::instance().assembly();
        }
        std::cout << "output file " << outputFile << std::endl;
    }
    return 0;
}