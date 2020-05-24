#include "../h/symTable.h"
#include <iostream>

int SymTable::zero = 0;

bool SymTable::addSymbol(std::shared_ptr<Symbol> s)
{
    if (symbols->find(s->getName()) == symbols->end())
    {
        symbols->emplace(std::make_pair(s->getName(), s));
        return true;
    }
    else if (!symbols->find(s->getName())->second->getDefined()) //deklarisan kao globalan ali nije definisan
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
    std::cout << "Tabela Simbola" << std::endl;
    std::cout << "Name"
              << "\t"
              << "Section"
              << "\t"
              << "Value"
              << "\t"
              << "Visib."
              << "\t"
              << "Serial#"
              << "\t"
              << "Defined" << std::endl;
    for (auto symbol : *symbols)
    {
        std::cout << *symbol.second << std::endl;
    }
}

std::shared_ptr<Symbol> SymTable::getUND()
{
    return symbols->find("UND")->second;
}

std::shared_ptr<Symbol> SymTable::getSymbol(std::string name)
{
    return symbols->find(name)->second;
}