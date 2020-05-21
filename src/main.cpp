#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
#include <stdio.h>
#include "../h/assembler.h"
#include "../h/util.h"

int main(int argc, char *argv[])
{
    
    if (argc < 2)
    {
        std::cout << "Nema dovoljno argumenata"<< std::endl;
    }
    else
    {
        char *inputFIle = argv[1];
        bool ok = Assembler::instance().setInputFile(inputFIle);


        if(ok){
            Assembler::instance().assembly();
        }
    }
    return 0;
}