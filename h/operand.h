#include <string>

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
        SYMBOL_DIR = 4
    };

private:
    Type type;
    char opCode;
    int size;

public:
    Operand(std::string name);
    char getOpCode();
    Type getType;
};