#pragma once
#include <memory>
#include <map>
#include "symbol.h"

class SymTable
{
private:
    std::shared_ptr<std::map<std::string, std::shared_ptr<Symbol>>> symbols;
    static SymTable inst;

    SymTable()
    {
        symbols = std::make_shared<std::map<std::string, std::shared_ptr<Symbol>>>();
    }

public:
    SymTable(SymTable const &) = delete;

    void operator=(SymTable const &) = delete;

    static SymTable &instance();

    bool addSymbol(std::shared_ptr<Symbol> s);

    void print();
};