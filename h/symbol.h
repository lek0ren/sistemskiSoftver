#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "regexes.h"

class Section;

class Symbol
{
protected:
    struct ST_forwardref
    {
        int patch;
        std::shared_ptr<Section> section;
    };
    int offset;
    int num;
    bool local;
    std::string name;
    int *section;
    bool defined;
    std::shared_ptr<std::vector<ST_forwardref>> flink;

public:
    Symbol(std::string name, int off, int &s);

    void setToGlobal();

    void setNumber(int num);

    void setDefined();

    void setOffset(int off);

    void setName(std::string name);

    void setSection(int &s);

    std::string getName() const;

    int &getNumber();

    bool getDefined();

    int getOffset();

    std::string getName();

    int &getSection();

    void addPatch(int p);

    friend std::ostream &operator<<(std::ostream &output, const Symbol &s);

    friend class Assembler;
};