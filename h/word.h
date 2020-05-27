#pragma once

#include "instruction.h"

class Word : public Instruction
{
public:
    Word(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);
};