#pragma once
#include <string>

class Token{
    private:
    std::string token;
    public:
    Token(std::string s){
        token = s;
    }

    std::string getToken(){
        return token;
    }
};