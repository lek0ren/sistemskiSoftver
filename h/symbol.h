#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "regexes.h"

class Section;

class Symbol
{
protected:
    struct STForwartRefs
    {
        int patch;
        STForwartRefs *next;
    };
    int offset;
    int num;
    bool local;
    std::string name;
    int *section;
    bool defined;
    STForwartRefs *flink;

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

    friend std::ostream &operator<<(std::ostream &output, const Symbol &s);
};