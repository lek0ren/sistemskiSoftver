#pragma once
#include <vector>
#include <memory>
#include "symbol.h"

class Section : public Symbol
{
private:
    int size;
    std::shared_ptr<std::vector<std::string>> code;

public:
    Section(std::string name, int off, std::shared_ptr<Section> s);

    void setSize(int s)
    {
        size = s;
    }

    void appendCode(std::vector<std::string> opCode);
};