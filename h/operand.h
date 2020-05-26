#pragma once
#include <string>
#include <regex>

class Operand
{
public:
    enum Type
    {
        LITERAL_IMM = 0,
        SYMBOL_IMM = 0,
        REG_DIR = 1,
        REG_IND = 2,
        LITERAL_REG_OFF = 3,
        SYMBOL_REG_OFF = 3,
        PC_RELATIVE = 2,
        LITERAL_DIR = 4,
        SYMBOL_DIR = 4,
        JMP_LITERAL_IMM = 0, //
        JMP_SYMBOL_IMM = 0,  //
        JMP_REG_DIR = 1,     ///
        JMP_REG_IND = 2,
        JMP_LITERAL_REG_OFF = 3,
        JMP_SYMBOL_REG_OFF = 3,
        JMP_PC_RELATIVE = 2,
        JMP_LITERAL_DIR = 4,
        JMP_SYMBOL_DIR = 4

    };

private:
    Type type;
    unsigned char opCode[3];
    int size;
    std::string name;

    void extractLiteralAndOffset(std::smatch &s);
    void extractLiteral(std::smatch &s);
    void extractSymbolAndOffset(std::smatch &s);
    void extractSymbol(std::smatch &s);
    void extractReg(std::smatch &s);

public:
    Operand(std::string name);
    unsigned char *getOpCode();
    Type getType();
    int getSize();
    std::string getName();
};