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
        bool rel = false;
        bool twoByte = true;
    };
    int offset;
    int num;
    bool local;
    std::string name;
    int section;
    int defined;
    bool apsRelocatable = false;
    std::shared_ptr<std::vector<ST_forwardref>> flink;

public:
    Symbol(std::string name, int off, int &s);

    virtual void setToGlobal()
    {
        local = false;
    }

    void setNumber(int num);

    void setDefined();

    void setDefined(int i);

    void setOffset(int off);

    void setName(std::string name);

    void setSection(int s);

    std::string getName() const;

    int &getNumber();

    bool getDefined();

    int getOffset();

    bool getLocal();

    void setApsRelocatable();

    bool getApsRelocatable();

    std::string getName();

    int &getSection();

    void addPatch(int p, bool rel = false, bool twoByte = true);

    friend std::ostream &operator<<(std::ostream &output, const Symbol &s);

    friend class Assembler;
};