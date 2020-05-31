#pragma once
#include <regex>

extern std::regex reg_emtpy_line;
extern std::regex reg_section;
extern std::regex reg_label;
extern std::regex reg_labelWout;
extern std::regex reg_jmpInstr;
extern std::regex reg_global;
extern std::regex reg_extern;
extern std::regex reg_end;
extern std::regex reg_oneOpInstr;
extern std::regex reg_twoOpInstr;
extern std::regex reg_noOp;
extern std::regex reg_equ;
extern std::regex reg_byte;
extern std::regex reg_word;
extern std::regex reg_skip;

extern std::regex reg_literal_imm;
extern std::regex reg_symbol_imm;
extern std::regex reg_reg_dir;
extern std::regex reg_reg_ind;
extern std::regex reg_literal_reg_off;
extern std::regex reg_symbol_reg_off;
extern std::regex reg_pc_rel;
extern std::regex reg_literal_dir;
extern std::regex reg_symbol_dir;

extern std::regex reg_jmp_literal_imm;
extern std::regex reg_jmp_symbol_imm;
extern std::regex reg_jmp_reg_dir;
extern std::regex reg_jmp_reg_ind;
extern std::regex reg_jmp_literal_reg_off;
extern std::regex reg_jmp_symbol_reg_off;
extern std::regex reg_jmp_pc_rel;
extern std::regex reg_jmp_literal_dir;
extern std::regex reg_jmp_symbol_dir;