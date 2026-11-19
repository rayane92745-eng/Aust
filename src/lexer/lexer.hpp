#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <vector>
#include <string>

class Lexer {
public:
    Lexer(const std::string& source);
    std::vector<Token> scanTokens();

private:
    std::string source;
    std::vector<Token> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

    bool isAtEnd();
    char advance();
    char peek();
    char peekNext();
    bool check(char c);
    bool match(char expected);
    void addToken(TokenType type);
    void identifier();
    void number();
};

#endif
