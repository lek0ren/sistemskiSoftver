#include "../h/symTable.h"
#include "../h/section.h"
#include "../h/assembler.h"
#include "../h/symbol.h"
#include <iostream>

int SymTable::zero = 0;

bool SymTable::addSymbol(std::shared_ptr<Symbol> s, bool declaration)
{
    if (symbols->find(s->getName()) == symbols->end())
    {
        symbols->emplace(std::make_pair(s->getName(), s));
        s->setNumber(Assembler::instance().numGen++);
        return true;
    }
    else if (!symbols->find(s->getName())->second->getDefined() && declaration) //deklarisan kao globalan ali nije definisan
    {
        std::cout << "Usao u deklarisano prethodno!" << std::endl;
        std::shared_ptr<Symbol> inTable = symbols->find(s->getName())->second;
        inTable->setDefined();
        inTable->setOffset(s->getOffset());
        inTable->setSection(s->getSection());
        return true;
    }
    return false;
}

SymTable &SymTable::instance()
{
    static SymTable inst;
    return inst;
}

void SymTable::print()
{
    std::vector<std::shared_ptr<Symbol>> symbolsToPrint;
    for (auto s : *symbols)
    {
        symbolsToPrint.push_back(s.second);
    }

    std::sort(symbolsToPrint.begin(), symbolsToPrint.end(), [](std::shared_ptr<Symbol> &a, const std::shared_ptr<Symbol> &b) -> bool {
        if (std::dynamic_pointer_cast<Section>(a) == std::dynamic_pointer_cast<Section>(b))
        {
            if (a->getSection() == b->getSection())
                return a->getOffset() < b->getOffset();
            else
            {
                return a->getSection() < b->getSection();
            }
        }
        if (std::dynamic_pointer_cast<Section>(a))
        {
            return true;
        }
        return false;
    });

    std::cout << "Tabela Simbola" << std::endl;
    std::cout << "Name"
              << "\t|"
              << "Sect."
              << "\t|"
              << "Value"
              << "\t|"
              << "Visib."
              << "\t|"
              << "Serial"
              << "\t|"
              << "Defined" << std::endl;

    std::cout << "================================================" << std::endl;
    for (auto symbol : symbolsToPrint)
    {
        std::cout << *symbol << std::endl;
        std::cout << "================================================" << std::endl;
    }

    std::cout << std::endl
              << std::endl;

    for (auto symbol : *symbols)
    {
        std::shared_ptr<Section> section = std::dynamic_pointer_cast<Section>(symbol.second);
        if (section)
        {
            std::cout << ".rel." << symbol.second->getName() << std::endl;
            std::cout << "offset\t|      "
                      << "Type\t| "
                      << "value\t|  " << std::endl;
            std::cout << "================================================" << std::endl;
            for (auto rel : *(section->getRelTable()))
            {
                std::cout << *rel << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

std::shared_ptr<Symbol> SymTable::getUND()
{
    return symbols->find("UND")->second;
}

std::shared_ptr<Symbol> SymTable::getSymbol(std::string name)
{
    std::map<std::string, std::shared_ptr<Symbol>>::iterator res = symbols->find(name);
    if (res != symbols->end())
    {
        return res->second;
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<std::map<std::string, std::shared_ptr<Symbol>>> SymTable::getSymbols()
{
    return symbols;
}