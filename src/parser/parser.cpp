#include "parser.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

std::vector<std::unique_ptr<Stmt>> Parser::parse() {
    std::vector<std::unique_ptr<Stmt>> statements;
    while (!isAtEnd()) {
        statements.push_back(declaration());
    }
    return statements;
}

std::unique_ptr<Stmt> Parser::declaration() {
    if (match({TokenType::VAR})) {
        return varDeclaration();
    }
    return statement();
}

// Simplified var declaration: var <id> = <expr>;
// Note: I'll need to add varDeclaration to parser.hpp or implement it here
// For now, let's implement a simple version within statement()

std::unique_ptr<Stmt> Parser::statement() {
    // For this prototype, we treat everything as a var declaration if it's an identifier
    // In a real parser, we'd distinguish between assignments and declarations
    Token name = consume(TokenType::IDENTIFIER, "Expected variable name.");
    consume(TokenType::EQUAL, "Expected '=' after variable name.");
    auto initializer = expression();
    consume(TokenType::SEMICOLON, "Expected ';' after declaration.");
    
    return std::make_unique<VarStmt>(name.lexeme, std::move(initializer));
}

std::unique_ptr<Expr> Parser::expression() {
    return addition();
}

std::unique_ptr<Expr> Parser::addition() {
    auto expr = multiplication();

    while (match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        auto right = multiplication();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op.lexeme, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::multiplication() {
    auto expr = primary();

    while (match({TokenType::SLASH, TokenType::STAR})) {
        Token op = previous();
        auto right = primary();
        expr = std::make_unique<BinaryExpr>(std::move(expr), op.lexeme, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expr> Parser::primary() {
    if (match({TokenType::NUMBER, TokenType::STRING})) {
        return std::make_unique<LiteralExpr>(previous().lexeme);
    }

    if (match({TokenType::IDENTIFIER})) {
        return std::make_unique<VariableExpr>(previous().lexeme);
    }

    if (match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        return expr;
    }

    throw std::runtime_error("Expected expression.");
}

// Helper implementations

bool Parser::isAtEnd() {
    return tokens[current].type == TokenType::EOF;
}

Token Parser::advance() {
    if (!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() {
    return tokens[current];
}

Token Parser::previous() {
    return tokens[current - 1];
}

bool Parser::check(TokenType type) {
    if (isAtEnd()) return false;
    return tokens[current].type == type;
}

bool Parser::match(std::vector<TokenType> types) {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

void Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        advance();
        return;
    }
    throw std::runtime_error("Error at line " + std::to_string(peek().line) + ": " + message);
}
