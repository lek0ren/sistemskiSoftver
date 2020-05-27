#pragma once

#include "section.h"
#include "label.h"
#include "Token.h"
#include <memory>
#include <fstream>
#include <iostream>
#include <vector>

class Assembler
{
private:
    int locationCounter;
    std::shared_ptr<Section> currSection;
    static Assembler inst;
    std::shared_ptr<Label> unfinishedLabel;
    std::ifstream infile;
    std::ofstream outfile;
    std::string line;
    std::shared_ptr<std::vector<std::shared_ptr<Section>>> sections;
    std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens;

    Assembler()
    {
        toContinue = true;
        locationCounter = 0;
        currSection = nullptr;
        unfinishedLabel = nullptr;
        sections = std::make_shared<std::vector<std::shared_ptr<Section>>>();
        tokens = std::make_shared<std::vector<std::shared_ptr<Token>>>();
    }

public:
    Assembler(Assembler const &) = delete;

    void operator=(Assembler const &) = delete;

    void setCurrSection(std::shared_ptr<Section> s);

    static Assembler &instance();

    void updateLocationCounter(int num);

    bool setInputFile(char *input);

    bool setOutputFile(char *output);

    void assembly();

    int getLocationCounter();

    std::shared_ptr<Section> getCurrentSection();

    int zero = 0;
    int numGen = 1;
    bool toContinue = true;
};