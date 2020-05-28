#pragma once
#include <string>
#include <regex>

class Operand
{
public:
    enum class Type
    {
        LITERAL_IMM = 0,
        SYMBOL_IMM,
        REG_DIR,
        REG_IND,
        LITERAL_REG_OFF,
        SYMBOL_REG_OFF,
        PC_RELATIVE,
        LITERAL_DIR,
        SYMBOL_DIR,
        JMP_LITERAL_IMM, //
        JMP_SYMBOL_IMM,  //
        JMP_REG_DIR,     ///
        JMP_REG_IND,
        JMP_LITERAL_REG_OFF,
        JMP_SYMBOL_REG_OFF,
        JMP_PC_RELATIVE,
        JMP_LITERAL_DIR,
        JMP_SYMBOL_DIR
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

    void addSymbolToCode(std::string name, std::smatch &m);

    typedef std::map<Type, char> OperandTypeCode;
    static OperandTypeCode OperandTypeCode_;

public:
    Operand(std::string name);
    unsigned char *getOpCode();
    int getType(int i);
    Type getType();
    int getSize();
    std::string getName();
};