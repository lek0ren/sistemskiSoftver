#pragma once
#include <memory>
#include <map>
#include "symbol.h"

class SymTable
{
private:
    std::shared_ptr<std::map<std::string, std::shared_ptr<Symbol>>> symbols;
    static SymTable inst;
    static int zero;

    SymTable()
    {
        symbols = std::make_shared<std::map<std::string, std::shared_ptr<Symbol>>>();
        symbols->insert(std::make_pair("UND", std::make_shared<Symbol>("UND", 0, zero)));
    }

public:
    SymTable(SymTable const &) = delete;

    void operator=(SymTable const &) = delete;

    static SymTable &instance();

    bool addSymbol(std::shared_ptr<Symbol> s, bool declaration = false);

    std::shared_ptr<Symbol> getUND();

    std::shared_ptr<Symbol> getSymbol(std::string);

    std::shared_ptr<std::map<std::string, std::shared_ptr<Symbol>>> getSymbols();

    void print();
};