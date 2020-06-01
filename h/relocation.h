#pragma once
#include <iostream>

class Relocation
{
public:
    enum class Type
    {
        R_16 = 0,
        R_16_PC,
        R_8
    };

private:
    int offset;
    int *value;
    Type type;

public:
    Relocation(int offset, Type type, int *value);

    int getOffset()
    {
        return offset;
    }

    int *getValue()
    {
        return value;
    }

    Type getType()
    {
        return type;
    }

    friend std::ostream &operator<<(std::ostream &output, const Relocation &s);
};