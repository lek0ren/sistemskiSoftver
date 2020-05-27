#pragma once
#include <string>

char *stringToCharArray(std::string s, char *array);

char *readToken(char *line, char *token);

struct HexCharStruct
{
    unsigned char c;
    HexCharStruct(unsigned char _c) : c(_c) {}
};

inline std::ostream &operator<<(std::ostream &o, const HexCharStruct &hs)
{
    auto flags = o.flags();
    o << std::hex << (unsigned char)hs.c;
    o.flags(flags);
    return o;
}

inline HexCharStruct hex(unsigned char _c)
{
    return HexCharStruct(_c);
}