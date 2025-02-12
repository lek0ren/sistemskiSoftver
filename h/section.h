#pragma once
#include <vector>
#include <memory>
#include "symbol.h"
#include "relocation.h"

class Section : public Symbol
{
private:
    int size;
    std::shared_ptr<std::vector<unsigned char>> code;
    std::shared_ptr<std::vector<std::shared_ptr<Relocation>>> relocations;
    std::shared_ptr<std::map<std::shared_ptr<Relocation>, std::shared_ptr<Symbol>>> pendingRelocations;

public:
    Section(std::string name, int off, int &s);

    void setToGlobal() override;

    void setSize(int s)
    {
        size = s;
    }

    void appendCode(std::vector<unsigned char> opCode);

    void addRelocation(int offset, Relocation::Type type, int &value);

    void addPendingRelocation(std::shared_ptr<Symbol> sym, int offset, Relocation::Type type, int &value);

    std::shared_ptr<std::vector<std::shared_ptr<Relocation>>> getRelTable();

    std::shared_ptr<std::map<std::shared_ptr<Relocation>, std::shared_ptr<Symbol>>> getPendingRel();

    friend std::ostream &operator<<(std::ostream &output, const Section &s);

    friend class Assembler;
};