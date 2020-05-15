#include <iostream>
#include <fstream>
#include <regex>
#include <string.h>
#include <stdio.h>

std::regex label("[/w]+:");

class Token
{
private:
    std::string token;

    enum type {
        INSTR = 1,
        LABEL,
        LITERAL,
        SIMBOL,
        REGVAL,
        MEMREGVAL,
        MEMVALWITHREG
    };

public:
    Token(std::string token) : token(token) {}

    Token(char *string) {
        token = std::string(string);
    }

    std::string getToken()
    {
        return token;
    }
};

char *stringToCharArray(std::string string, char *array)
{
    strcpy(array, string.c_str());
    return array;
}



int main()
{
    std::ifstream in("kod.s");

    if (!in)
    {
        std::cout << "Cannot open input file.\n";
    }

    std::string line;

    char *array = (char *)std::malloc(255 * sizeof(char));

    while (std::getline(in, line))
    {
        //replace starting offset with nothing
        //std::cout << line << std::endl;
        char *token = strtok(stringToCharArray(line, array), " ,\n\t");
        std::vector<Token> instruction;

        while (token)
        {
            Token t(token);
            instruction.push_back(t);
            std::cout << t.getToken() << std::endl;
            token = strtok(nullptr, " ,\n\t");
        }
    }
    in.close();
    return 0;
}