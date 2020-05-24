#include <iostream>
#include "../h/assembler.h"
#include <string.h>
#include "../h/util.h"
#include "../h/regexes.h"
#include <regex>
#include "../h/symbol.h"
#include "../h/symTable.h"

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
    bool toContinue = true;
    int undNum = -1;
    int zero = 0;
    int numGen = 1;

    while (std::getline(infile, line) && toContinue)
    {
        //proveriti regexom da li je dobra struktura linije, da li postoje svi ,

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

        std::smatch m;
        std::string start = (*tokens)[0]->getToken();

        //prepoznavanje .global
        if (std::regex_search(start, m, reg_global))
        {
            if (tokens->size() >= 2)
            {
                for (int i = 1; i < tokens->size(); i++)
                {
                    std::shared_ptr<Symbol> symGlob;
                    if (!currSection)
                    {
                        symGlob = std::make_shared<Symbol>((*tokens)[i]->getToken(), locationCounter, zero);
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
        if (std::regex_search(start, m, reg_extern))
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
                            symExtern->setNumber(numGen++);
                        }
                    }
                }
                tokens->clear();
            }
        }

        //prepoznavanje sekcija
        if (std::regex_search(start, m, reg_section))
        {
            std::shared_ptr<Section> newSection;
            if (currSection)
            {
                currSection->setSize(locationCounter);
                locationCounter = 0;
                sections->push_back(currSection);
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
                newSection->setNumber(numGen++);
            }
            currSection = newSection;
            if (tokens->size() > 2)
            {
                toContinue = false;
                std::cout << "Invalid input when declaring section " << newSection->getName() << "!\n";
                break;
            }

            //ne sme nista drugo da ostane, da se proveri
        }

        //prepoznavanje labela
        if (std::regex_search(start, m, reg_label))
        {
            std::shared_ptr<Symbol> symLabel;
            if (currSection)
            {
                symLabel = std::make_shared<Symbol>(start, locationCounter, currSection->getNumber());
                if (!SymTable::instance().addSymbol(symLabel))
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
                    symLabel->setNumber(numGen++);
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

        if (std::regex_search(start, m, reg_end))
        {
            currSection->setSize(locationCounter);
            sections->push_back(currSection);
            toContinue = false;
            if (tokens->size() > 1)
            {
                //err
            }
        }
        //prepoznavanje instrukcija
        if (!tokens->empty())
        {
        }
        delete token;
    }
    SymTable::instance().print();
}