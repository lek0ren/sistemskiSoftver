#pragma once
#include <string>
#include <memory>
#include <iostream>
#include "regexes.h"

class Section;

class Symbol
{
private:
    struct STForwartRefs
    {
        int patch;
        STForwartRefs *next;
    };
    int offset;
    int num;
    bool local;
    std::string name;
    std::shared_ptr<Section> section;
    bool defined;
    STForwartRefs *flink;

public:
    Symbol(std::string name, int off, std::shared_ptr<Section> s);

    void setToGlobal()
    {
        local = false;
    }

    void setNumber(int num)
    {
        this->num = num;
    }

    void setDefined()
    {
        defined = true;
    }

    std::string getName() const
    {
        return name;
    }

    friend std::ostream &operator<<(std::ostream &output, const Symbol &s);
};