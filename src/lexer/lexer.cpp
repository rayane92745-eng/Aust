#include "lexer.hpp"
#include <cctype>

Lexer::Lexer(const std::string& source) : source(source) {}

std::vector<Token> Lexer::scanTokens() {
    while (!isAtEnd()) {
        start = current;
        char c = advance();
        switch (c) {
            case '(': addToken(TokenType::LEFT_PAREN); break;
            case ')': addToken(TokenType::RIGHT_PAREN); break;
            case '{': addToken(TokenType::LEFT_BRACE); break;
            case '}': addToken(TokenType::RIGHT_BRACE); break;
            case ',': addToken(TokenType::COMMA); break;
            case '.': addToken(TokenType::DOT); break;
            case '-': addToken(TokenType::MINUS); break;
            case '+': addToken(TokenType::PLUS); break;
            case ';': addToken(TokenType::SEMICOLON); break;
            case '/': addToken(TokenType::SLASH); break;
            case '*': addToken(TokenType::STAR); break;
            case ' ': 
            case '\r':
            case '\t': break; // Ignore whitespace
            case '\n': line++; break;
            default:
                if (isdigit(c)) {
                    number();
                } else if (isalpha(c) || c == '_') {
                    identifier();
                } else {
                    // Error handling could go here
                }
                break;
        }
    }

    tokens.push_back({TokenType::EOF_TOKEN, "", line});
    return tokens;
}

bool Lexer::isAtEnd() { return current >= source.length(); }

char Lexer::advance() { return source[current++]; }

char Lexer::peek() { return isAtEnd() ? '\0' : source[current]; }

char Lexer::peekNext() { if (current + 1 >= source.length()) return '\0'; return source[current + 1]; }

bool Lexer::check(char c) { return !isAtEnd() && source[current] == c; }

bool Lexer::match(char expected) {
    if (isAtEnd() || source[current] != expected) return false;
    current++;
    return true;
}

void Lexer::addToken(TokenType type) {
    std::string text = source.substr(start, current - start);
    tokens.push_back({type, text, line});
}

void Lexer::identifier() {
    while (isalnum(peek()) || peek() == '_') advance();
    addToken(TokenType::IDENTIFIER);
}

void Lexer::number() {
    while (isdigit(peek())) advance();
    addToken(TokenType::NUMBER);
}
