#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, 
    LEFT_BRACE, RIGHT_BRACE, 
    COMMA, DOT, MINUS, PLUS, 
    SEMICOLON, SLASH, STAR, 

    // One-character tokens
    EQUAL, EQUAL_EQUAL, // = , ==

    // Literals
    IDENTIFIER, STRING, NUMBER, 

    // Keywords
    VAR, PRINT, IF, ELSE, WHILE, FOR, 

    // End of file
    EOF
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;

    Token(TokenType t, std::string l, int ln) 
        : type(t), lexeme(std::move(l)), line(ln) {}
};

#endif
