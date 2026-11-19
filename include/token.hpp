#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

enum class TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR

    // One or more character tokens
    IDENTIFIER, STRING, NUMBER

    // Literals
    IDENTIFIER_KEYWORD, // e.g., 'func', 'if', 'return'

    // End of file
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};

#endif
