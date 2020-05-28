#pragma once
#include <string>
#include <iomanip>

char *stringToCharArray(std::string s, char *array);

char *readToken(char *line, char *token);

struct HexCharStruct
{
    unsigned char c;
    bool fill;
    HexCharStruct(unsigned char _c, bool f) : c(_c), fill(f) {}
};

inline std::ostream &operator<<(std::ostream &o, const HexCharStruct &hs)
{
    //auto flags = o.flags();
    if (hs.fill)
        o << std::setfill('0');
    o << std::hex << std::right << std::setw(2) << (int)hs.c;
    //o.flags(flags);
    return o;
}

inline HexCharStruct hex(unsigned char _c, bool f = true)
{
    return HexCharStruct(_c, f);
}