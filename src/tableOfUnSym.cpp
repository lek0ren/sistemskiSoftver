#include "../h/tableOfUnSym.h"
#include <map>

std::shared_ptr<std::vector<std::shared_ptr<Token>>> TableOfUnSym::getTokensForSymbol(std::shared_ptr<Symbol> sym)
{
    auto fetchedSym = symbols->find(sym);
    return fetchedSym == symbols->end() ? nullptr : fetchedSym->second;
}

void TableOfUnSym::addSymbol(std::shared_ptr<Symbol> sym, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens)
{
    symbols->emplace(std::pair<std::shared_ptr<Symbol>, std::shared_ptr<std::vector<std::shared_ptr<Token>>>>(sym, tokens));
}

TableOfUnSym &TableOfUnSym::instance()
{
    static TableOfUnSym inst;
    return inst;
}

void TableOfUnSym::removeSymbol(std::shared_ptr<Symbol> sym)
{
    symbols->erase(sym);
}