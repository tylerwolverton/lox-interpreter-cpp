#pragma once
#include "Types.h"
#include <memory>

#include <vector>
// This file was generated from ExprGenerator.exe. 
// If changes are needed, modify ExprGenerator/main.cpp 

class BlockStmt;
class ClassStmt;
class ExpressionStmt;
class IfStmt;
class FunctionStmt;
class PrintStmt;
class ReturnStmt;
class VarStmt;
class WhileStmt;
class Expr;
class VariableExpr;

class StmtVisitor { 
public:
    virtual void visitBlockStmt(const std::shared_ptr<BlockStmt>& stmt) = 0;
    virtual void visitClassStmt(const std::shared_ptr<ClassStmt>& stmt) = 0;
    virtual void visitExpressionStmt(const std::shared_ptr<ExpressionStmt>& stmt) = 0;
    virtual void visitIfStmt(const std::shared_ptr<IfStmt>& stmt) = 0;
    virtual void visitFunctionStmt(const std::shared_ptr<FunctionStmt>& stmt) = 0;
    virtual void visitPrintStmt(const std::shared_ptr<PrintStmt>& stmt) = 0;
    virtual void visitReturnStmt(const std::shared_ptr<ReturnStmt>& stmt) = 0;
    virtual void visitVarStmt(const std::shared_ptr<VarStmt>& stmt) = 0;
    virtual void visitWhileStmt(const std::shared_ptr<WhileStmt>& stmt) = 0;
};

class Stmt {
    public:
    virtual void accept(StmtVisitor& visitor) = 0;
};

class BlockStmt : public Stmt {
    public:
    BlockStmt( std::vector<std::shared_ptr<Stmt>> statements ) 
      : m_statements(statements)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitBlockStmt(std::make_shared<BlockStmt>(*this));
    }

    std::vector<std::shared_ptr<Stmt>> m_statements;
};

class ClassStmt : public Stmt {
    public:
    ClassStmt( Token name, std::shared_ptr<VariableExpr> superclass, std::vector<std::shared_ptr<FunctionStmt>> methods ) 
      : m_name(name),
      m_superclass(superclass),
      m_methods(methods)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitClassStmt(std::make_shared<ClassStmt>(*this));
    }

    Token m_name;
    std::shared_ptr<VariableExpr> m_superclass;
    std::vector<std::shared_ptr<FunctionStmt>> m_methods;
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

class IfStmt : public Stmt {
    public:
    IfStmt( std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> thenBranch, std::shared_ptr<Stmt> elseBranch ) 
      : m_condition(condition),
      m_thenBranch(thenBranch),
      m_elseBranch(elseBranch)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitIfStmt(std::make_shared<IfStmt>(*this));
    }

    std::shared_ptr<Expr> m_condition;
    std::shared_ptr<Stmt> m_thenBranch;
    std::shared_ptr<Stmt> m_elseBranch;
};

class FunctionStmt : public Stmt {
    public:
    FunctionStmt( Token name, std::vector<std::shared_ptr<Token>> params, std::shared_ptr<BlockStmt> body ) 
      : m_name(name),
      m_params(params),
      m_body(body)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitFunctionStmt(std::make_shared<FunctionStmt>(*this));
    }

    Token m_name;
    std::vector<std::shared_ptr<Token>> m_params;
    std::shared_ptr<BlockStmt> m_body;
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

class ReturnStmt : public Stmt {
    public:
    ReturnStmt( Token keyword, std::shared_ptr<Expr> value ) 
      : m_keyword(keyword),
      m_value(value)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitReturnStmt(std::make_shared<ReturnStmt>(*this));
    }

    Token m_keyword;
    std::shared_ptr<Expr> m_value;
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

class WhileStmt : public Stmt {
    public:
    WhileStmt( std::shared_ptr<Expr> condition, std::shared_ptr<Stmt> body ) 
      : m_condition(condition),
      m_body(body)
        {}

    void accept(StmtVisitor& visitor) override {
        return visitor.visitWhileStmt(std::make_shared<WhileStmt>(*this));
    }

    std::shared_ptr<Expr> m_condition;
    std::shared_ptr<Stmt> m_body;
};

