#include <iostream>
#include "../h/assembler.h"
#include <string.h>
#include "../h/util.h"
#include "../h/regexes.h"
#include <regex>
#include "../h/symbol.h"
#include "../h/symTable.h"
#include "../h/instruction.h"
#include "../h/jmpInst.h"
#include "../h/skip.h"
#include "../h/word.h"
#include "../h/byte.h"
#include "../h/oneOp.h"
#include "../h/twoOp.h"
#include "../h/noOp.h"
#include "../h/tableOfUnSym.h"

bool Assembler::setOutputFile(char *output)
{
    outfile.open(output);
    if (!outfile.is_open())
    {
        std::cout << "Fajl sa imenom" << output << " ne postoji!" << std::endl;
        return false;
    }
    return true;
}

bool Assembler::setInputFile(char *input)
{
    infile.open(input);
    if (!infile.is_open())
    {
        std::cout << "Fajl sa imenom" << input << " ne postoji!" << std::endl;
        return false;
    }
    return true;
}

void Assembler::updateLocationCounter(int num)
{
    locationCounter += num;
}

Assembler &Assembler::instance()
{
    static Assembler inst;
    return inst;
}

void Assembler::setCurrSection(std::shared_ptr<Section> s)
{
    currSection = s;
}

void Assembler::assembly()
{
    int undNum = -1;

    while (std::getline(infile, line) && toContinue)
    {

        std::smatch m;
        //proveriti regexom da li je dobra struktura linije, da li postoje svi ,

        if (std::regex_match(line, m, reg_emtpy_line))
        {
            std::cout << "prazna linija\n";
            continue;
        }

        tokens->clear();

        char *token = new char[255];
        token = strtok(stringToCharArray(line, token), " ,\n\t");

        while (token)
        {
            std::shared_ptr<Token> t = std::make_shared<Token>(token);
            tokens->push_back(t);
            std::cout << t->getToken() << std::endl;
            token = strtok(nullptr, " ,\n\t");
        }

        //prepoznati koja je instrukcija u pitanju

        std::string start = (*tokens)[0]->getToken();

        //prepoznavanje .global
        if (std::regex_match(start, m, reg_global))
        {
            if (tokens->size() >= 2)
            {
                for (int i = 1; i < tokens->size(); i++)
                {
                    std::shared_ptr<Symbol> symGlob;
                    if (!currSection)
                    {
                        symGlob = std::make_shared<Symbol>((*tokens)[i]->getToken(), locationCounter, Assembler::zero);
                        if (!SymTable::instance().addSymbol(symGlob))
                        {
                            toContinue = false;
                            std::cout << "Multiple definision of symbol " << symGlob->getName() << "!\n";
                            break;
                        }
                        else
                        {
                            std::cout << "Dosao ovde " << symGlob->getName() << "!\n";
                            symGlob->setToGlobal();
                        }
                    }
                }
                tokens->clear();
            }
        }

        //prepoznavanje .extern
        if (std::regex_match(start, m, reg_extern))
        {

            if (tokens->size() >= 2)
            {
                for (int i = 1; i < tokens->size(); i++)
                {
                    std::shared_ptr<Symbol> symExtern;
                    if (!currSection)
                    {
                        symExtern = std::make_shared<Symbol>((*tokens)[i]->getToken(), locationCounter, SymTable::instance().getUND()->getNumber());
                        if (!SymTable::instance().addSymbol(symExtern))
                        {
                            toContinue = false;
                            std::cout << "Multiple definision of symbol " << symExtern->getName() << "!\n";
                            break;
                        }
                        else
                        {
                            symExtern->setToGlobal();
                            //symExtern->setNumber(numGen++);
                        }
                    }
                }
                tokens->clear();
            }
        }
        //prepoznavanje sekcija
        if (std::regex_match(start, m, reg_section))
        {
            std::cout << "ovde2\n";
            std::shared_ptr<Section> newSection;
            if (currSection)
            {
                currSection->setSize(locationCounter);
                locationCounter = 0;
                sections->push_back(currSection);
                std::cout << "changing curr section\n";
            }
            newSection = std::make_shared<Section>((*tokens)[1]->getToken(), 0, undNum);
            if (!SymTable::instance().addSymbol(newSection))
            {
                toContinue = false;
                std::cout << "Multiple definision of symbol " << newSection->getName() << "!\n";
                break;
            }
            else
            {
                newSection->setDefined();
                //newSection->setNumber(numGen++);
            }
            currSection = newSection;
            if (tokens->size() > 2)
            {
                toContinue = false;
                std::cout << "Invalid input when declaring section " << newSection->getName() << "!\n";
                break;
            }
            tokens->clear();
            start = "";
            //ne sme nista drugo da ostane, da se proveri
        }

        //prepoznavanje labela
        if (std::regex_match(start, m, reg_label))
        {
            std::shared_ptr<Symbol> symLabel;
            if (currSection)
            {
                symLabel = std::make_shared<Symbol>(start, locationCounter, currSection->getNumber());
                if (!SymTable::instance().addSymbol(symLabel, true))
                {
                    toContinue = false;
                    std::cout << "Multiple definision of symbol " << symLabel->getName() << "!\n";
                    break;
                }
                else
                {
                    std::smatch match_name;
                    std::regex_match(start, match_name, reg_labelWout);
                    symLabel = SymTable::instance().getSymbol(match_name.str(1));
                    symLabel->setDefined();
                    symLabel->setSection(currSection->getNumber());
                    //symLabel->setNumber(numGen++);
                }
                tokens->erase(tokens->begin());
            }
            else
            {
                toContinue = false;
                std::cout << "Symbol definition outside of a section "
                          << "!\n";
                break;
            }
        }

        if (std::regex_match(start, m, reg_end))
        {
            currSection->setSize(locationCounter);
            sections->push_back(currSection);
            toContinue = false;
            if (tokens->size() > 1)
            {
                //err
            }
            continue;
        }

        if (std::regex_match(start, m, reg_equ))
        {
            start = tokens->at(1)->getToken();
            std::string equSym;
            //proveriti da li je izraz ispravan!!!!!!!!!
            if (std::regex_match(start, m, reg_labelWout))
            {
                std::cout << "Usao ovde 2\n";
                tokens->erase(tokens->begin(), tokens->begin() + 2);
                std::shared_ptr<std::vector<std::shared_ptr<Token>>> __tokens = std::make_shared<std::vector<std::shared_ptr<Token>>>(*tokens);
                createEquSymbol(start, __tokens);
            }

            std::cout << "Usao ovde 1\n";
            //preskaci za sata
        }
        //prepoznavanje instrukcija
        if (!tokens->empty())
        {
            start = (*tokens)[0]->getToken();

            tokens->erase(tokens->begin(), tokens->begin() + 1);
            Instruction *instruction;
            if (std::regex_match(start, m, reg_jmpInstr))
            {
                instruction = new JmpInst(start, tokens);
            }
            else if (std::regex_match(start, m, reg_oneOpInstr))
            {

                instruction = new OneOp(start, tokens);
            }
            else if (std::regex_match(start, m, reg_twoOpInstr))
            {
                instruction = new TwoOp(start, tokens);
            }
            else if (std::regex_match(start, m, reg_byte))
            {
                instruction = new Byte(start, tokens);
            }
            else if (std::regex_match(start, m, reg_word))
            {
                instruction = new Word(start, tokens);
            }
            else if (std::regex_match(start, m, reg_skip))
            {
                instruction = new Skip(start, tokens);
            }
            else
            {
                instruction = new NoOp(start, tokens);
            }

            updateLocationCounter(instruction->getSize());
            currSection->appendCode(instruction->getOpCode());

            std::vector<unsigned char> instCode = instruction->getOpCode();
            for (int i = 0; i < instruction->getSize(); i++)
            {

                if (i == 0)
                {
                    std::cout << "instrukcija " << start << ": \t";
                }
                std::cout << hex(instCode[i]) << ' ';
            }
            std::cout << std::endl
                      << std::endl;
        }
        delete token;
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        std::vector<std::shared_ptr<Symbol>> toRemove;
        for (auto &unsolvedSym : *(TableOfUnSym::instance().symbols))
        {
            std::cout << unsolvedSym.first->name << std::endl;
            if (createEquSymbol(unsolvedSym.first->name, unsolvedSym.second))
            {
                changed = true;
                toRemove.push_back(unsolvedSym.first);
            }
        }
        for (auto s : toRemove)
        {
            TableOfUnSym::instance().removeSymbol(s);
        }
    }
    if (!TableOfUnSym::instance().symbols->empty())
    {
        std::cout << "ERROR\n";
    }
    else
    {
        backPatch();
        SymTable::instance().print();
        print();
    }
}

int Assembler::getLocationCounter()
{
    return locationCounter;
}

std::shared_ptr<Section> Assembler::getCurrentSection()
{
    return currSection;
}

void Assembler::print()
{
    std::cout << std::endl
              << std::endl
              << "Sections" << std::endl;
    for (auto section : *sections)
    {
        std::cout << *section;
    }
    std::cout << std::endl;
}

void Assembler::backPatch()
{
    for (auto sym : *(SymTable::instance().getSymbols()))
    {
        for (auto forw : *(sym.second->flink))
        {
            if (forw.rel)
            {
                int number = forw.section->code->at(forw.patch) | forw.section->code->at(forw.patch + 1) << 8;
                number += sym.second->getOffset();
                forw.section->code->at(forw.patch) = number & 0xff;
                forw.section->code->at(forw.patch + 1) = number >> 8;
            }
            else
            {
                if (forw.twoByte)
                    forw.section->code->at(forw.patch + 1) = sym.second->getOffset() >> 8;
                forw.section->code->at(forw.patch) = sym.second->getOffset() & 0xFF;
            }
        }
    }
}

bool Assembler::createEquSymbol(std::string name, std::shared_ptr<std::vector<std::shared_ptr<Token>>> __tokens)
{
    std::shared_ptr<Symbol> sym = SymTable::instance().getSymbol(name);
    std::smatch m;
    int value = 0;
    if (!sym)
    {
        sym = std::make_shared<Symbol>(name, 0, SymTable::instance().getUND()->getNumber());
        if (!SymTable::instance().addSymbol(sym))
        {
            //ispisi gresku
        }
    }
    std::shared_ptr<Symbol> exprSymbol;

    std::string sign = "+";
    for (auto token : *__tokens)
    {
        std::string tok = token->getToken();
        std::cout << value << " " << tok << std::endl;
        if (tok == "+" || tok == "-")
        {
            sign = tok;
        }
        else
        {
            if (std::regex_match(tok, m, reg_literal_dir))
            {
                if (sign == "+")
                {
                    value += stoi(m[1].str());
                }
                else
                {
                    value -= stoi(m[1].str());
                }
            }
            else if (std::regex_match(tok, m, reg_symbol_dir))
            {

                exprSymbol = SymTable::instance().getSymbol(tok);
                if (exprSymbol)
                {
                    if (!exprSymbol->getDefined())
                    {
                        TableOfUnSym::instance().addSymbol(sym, __tokens);
                        return false;
                    }
                    if (sign == "+")
                    {
                        value += exprSymbol->getOffset();
                    }
                    else
                    {
                        value -= exprSymbol->getOffset();
                    }
                }
                else
                {
                    TableOfUnSym::instance().addSymbol(sym, __tokens);
                    return false;
                }
            }
        }
    }
    std::cout << value << std::endl;
    sym->setOffset(value);

    return true;
}