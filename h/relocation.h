#pragma once
#include <iostream>

class Relocation
{
public:
    enum class Type
    {
        R_64 = 0,
        R_64_PC
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