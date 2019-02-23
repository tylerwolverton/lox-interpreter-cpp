#pragma once
#include "Types.h"
#include <memory>

// This file was generated from ExprGenerator.exe. 
// If changes are needed, modify ExprGenerator/main.cpp 

class ExpressionStmt;
class PrintStmt;
class VarStmt;

class StmtVisitor { 
public:
    virtual void visitExpressionStmt(const std::shared_ptr<ExpressionStmt>& stmt) = 0;
    virtual void visitPrintStmt(const std::shared_ptr<PrintStmt>& stmt) = 0;
    virtual void visitVarStmt(const std::shared_ptr<VarStmt>& stmt) = 0;
};

class Stmt {
    public:
    virtual void accept(StmtVisitor& visitor) = 0;
};

class ExpressionStmt : public Stmt {
    public:
    ExpressionStmt( std::shared_ptr<Expr> expr ) 
      : m_expr(expr)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitExpressionStmt(std::make_shared<ExpressionStmt>(*this));
    }

    std::shared_ptr<Expr> m_expr;
};

class PrintStmt : public Stmt {
    public:
    PrintStmt( std::shared_ptr<Expr> expr ) 
      : m_expr(expr)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitPrintStmt(std::make_shared<PrintStmt>(*this));
    }

    std::shared_ptr<Expr> m_expr;
};

class VarStmt : public Stmt {
    public:
    VarStmt( Token name, std::shared_ptr<Expr> initializer ) 
      : m_name(name),
      m_initializer(initializer)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitVarStmt(std::make_shared<VarStmt>(*this));
    }

    Token m_name;
    std::shared_ptr<Expr> m_initializer;
};
