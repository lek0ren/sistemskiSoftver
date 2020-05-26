#include "../h/regexes.h"

std::regex reg_section = std::regex(".section");
std::regex reg_label = std::regex("[\\w\\d]+:");
std::regex reg_labelWout = std::regex("\\.{0,1}([\\w\\d]+):{0,1}");
std::regex reg_jmpInstr = std::regex("(jmp|call|jeq|jne|jgt)");
std::regex reg_oneOpInstr = std::regex("(int|push|pop)(b|w)?");
std::regex reg_twoOpInstr = std::regex("(xchg|mov|add|sub|mul|div|cmp|not|and|or|xor|test|shl|shr)(b|w)?");

std::regex reg_global(".global");
std::regex reg_extern(".extern");
std::regex reg_end(".end");
std::regex reg_equ(".equ");

//dodati svuda pocetak stringa
std::regex reg_literal_imm("\\$([\\d]+)$");
std::regex reg_symbol_imm("\\$([\\w][\\d\\w]*)$");
std::regex reg_reg_dir("%r(([0-6])|pc)(l|h)?$");
std::regex reg_reg_ind("\\(%(r[0-6]||pc)\\)$");
std::regex reg_literal_reg_off("([\\d]+)\\(%(r([0-6])|pc)\\)$"); //mozda treba b 2 puta da se esc
std::regex reg_symbol_reg_off("([\\w][\\d\\w]*)\\(%(r([0-6])|pc)\\)$");
std::regex reg_pc_rel("([\\w][\\d\\w]*)\\(%(r7|pc)\\)$");
std::regex reg_literal_dir("([\\d]+)$");
std::regex reg_symbol_dir("([\\w][\\d\\w]*)$");

std::regex reg_jmp_literal_imm("([\\d]+)$");
std::regex reg_jmp_symbol_imm("([\\w][\\d\\w]*)$");
std::regex reg_jmp_reg_dir("\\*%(r([0-7])|pc)(l|h)?$");
std::regex reg_jmp_reg_ind("\\*\\(%(r([0-7])|pc)\\)$");
std::regex reg_jmp_literal_reg_off("\\*([\\d]+)\\(%(r[0-7]|pc)\\)$");
std::regex reg_jmp_symbol_reg_off("\\*([\\w][\\d\\w]*)\\(%(r[0-7]|pc)\\)$");
std::regex reg_jmp_pc_rel("\\*([\\w][\\d\\w]*)\\(%(r7|pc)\\)$");
std::regex reg_jmp_literal_dir("\\*([\\d]+)$");
std::regex reg_jmp_symbol_dir("\\*([\\w][\\d\\w]*)$");