#include "symbol.h"
#include <map>
#include "Token.h"

class TableOfUnSym
{
private:
    static TableOfUnSym inst;

    TableOfUnSym()
    {
        symbols = std::make_shared<std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::vector<std::shared_ptr<Token>>>>>();
    }

public:
    std::shared_ptr<std::map<std::shared_ptr<Symbol>, std::shared_ptr<std::vector<std::shared_ptr<Token>>>>> symbols;

    static TableOfUnSym &instance();

    std::shared_ptr<std::vector<std::shared_ptr<Token>>> getTokensForSymbol(std::shared_ptr<Symbol> sym);

    void addSymbol(std::shared_ptr<Symbol> sym, std::shared_ptr<std::vector<std::shared_ptr<Token>>> tokens);

    void removeSymbol(std::shared_ptr<Symbol> sym);
};