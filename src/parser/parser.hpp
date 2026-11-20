#ifndef PARSER_HPP
#define PARSER_HPP

#include "../../include/token.hpp"
#include "../../include/ast.hpp"
#include <vector>
#include <memory>
#include <string>

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::vector<std::unique_ptr<Stmt>> parse();

private:
    std::vector<Token> tokens;
    int current = 0;

    // Parsing rules
    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> primary();

    // Helpers
    bool isAtEnd();
    Token advance();
    Token peek();
    Token previous();
    bool check(TokenType type);
    bool match(std::vector<TokenType> types);
    void consume(TokenType type, const std::string& message);
};

#endif
