#include "../h/symTable.h"
#include <iostream>

bool SymTable::addSymbol(std::shared_ptr<Symbol> s)
{
    if (symbols->find(s->getName()) == symbols->end())
    {
        symbols->emplace(std::make_pair(s->getName(), s));
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
    for (auto symbol : *symbols)
    {
        std::cout << symbol.second->getName() << std::endl;
    }
}