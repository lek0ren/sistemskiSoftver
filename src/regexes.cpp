#include "../h/regexes.h"

std::regex reg_section = std::regex(".section");
std::regex reg_label = std::regex("[\\w\\d]+:");
std::regex reg_labelWout = std::regex(":");
std::regex reg_arithInstr = std::regex("(jmp|call|jeq|jne|jgt)");