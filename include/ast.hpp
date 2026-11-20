#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>

// Base class for all expressions
class Expr {
public:
    virtual ~Expr() = default;
    virtual std::string toString() const = 0;
};

// Literal Expression (Numbers, Strings, etc.)
class LiteralExpr : public Expr {
public:
    std::string value;
    LiteralExpr(std::string val) : value(std::move(val)) {}
    std::string toString() const override { return value; }
};

// Variable Expression
class VariableExpr : public Expr {
public:
    std::string name;
    VariableExpr(std::string n) : name(std::move(n)) {}
    std::string toString() const override { return name; }
};

// Binary Expression (e.g., a + b)
class BinaryExpr : public Expr {
public:
    std::unique_ptr<Expr> left;
    std::string op;
    std::unique_ptr<Expr> right;

    BinaryExpr(std::unique_ptr<Expr> l, std::string o, std::unique_ptr<Expr> r)
        : left(std::move(l)), op(std::move(o)), right(std::move(r)) {}

    std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

// Base class for all statements
class Stmt {
public:
    virtual ~Stmt() = default;
    virtual std::string toString() const = 0;
};

// Variable Declaration Statement (e.g., var x = 10;
class VarStmt : public Stmt {
public:
    std::string name;
    std::unique_ptr<Expr> initializer;

    VarStmt(std::string n, std::unique_ptr<Expr> init) 
        : name(std::move(n)), initializer(std::move(init)) {}

    std::string toString() const override {
        return "var " + name + " = " + (initializer ? initializer->toString() : "nil") + ";";
    }
};

#endif
