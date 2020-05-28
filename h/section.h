#pragma once
#include <vector>
#include <memory>
#include "symbol.h"

class Section : public Symbol
{
private:
    int size;
    std::shared_ptr<std::vector<unsigned char>> code;

public:
    Section(std::string name, int off, int &s);

    void setSize(int s)
    {
        size = s;
    }

    void appendCode(std::vector<unsigned char> opCode);

    friend std::ostream &operator<<(std::ostream &output, const Section &s);

    friend class Assembler;
};