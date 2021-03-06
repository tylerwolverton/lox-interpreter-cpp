#pragma once
#include "Types.h"
#include "Expr.h"
#include "Stmt.h"
#include <vector>
#include <map>
#include <memory>

class Interpreter;

class Resolver : public ExprVisitor, public StmtVisitor
{
public:
	Resolver(const std::shared_ptr<Interpreter>& interpreter);
	~Resolver();

	void Resolve(const std::vector<std::shared_ptr<Stmt>>& statements);

	std::shared_ptr<void> visitAssignExpr(const std::shared_ptr<AssignExpr>& expr) override;
	std::shared_ptr<void> visitBinaryExpr(const std::shared_ptr<BinaryExpr>& expr) override;
	std::shared_ptr<void> visitGetExpr(const std::shared_ptr<GetExpr>& expr) override;
	std::shared_ptr<void> visitGroupingExpr(const std::shared_ptr<GroupingExpr>& expr) override;
	std::shared_ptr<void> visitLiteralExpr(const std::shared_ptr<LiteralExpr>& expr) override;
	std::shared_ptr<void> visitLogicalExpr(const std::shared_ptr<LogicalExpr>& expr) override;
	std::shared_ptr<void> visitUnaryExpr(const std::shared_ptr<UnaryExpr>& expr) override;
	std::shared_ptr<void> visitCallExpr(const std::shared_ptr<CallExpr>& expr) override;
	std::shared_ptr<void> visitSetExpr(const std::shared_ptr<SetExpr>& expr) override;
	std::shared_ptr<void> visitSuperExpr(const std::shared_ptr<SuperExpr>& expr) override;
	std::shared_ptr<void> visitThisExpr(const std::shared_ptr<ThisExpr>& expr) override;
	std::shared_ptr<void> visitVariableExpr(const std::shared_ptr<VariableExpr>& expr) override;

	void visitExpressionStmt(const std::shared_ptr<ExpressionStmt>& stmt) override;
	void visitBlockStmt(const std::shared_ptr<BlockStmt>& stmt) override;
	void visitClassStmt(const std::shared_ptr<ClassStmt>& stmt) override;
	void visitIfStmt(const std::shared_ptr<IfStmt>& stmt) override;
	void visitFunctionStmt(const std::shared_ptr<FunctionStmt>& stmt) override;
	void visitPrintStmt(const std::shared_ptr<PrintStmt>& stmt) override;
	void visitReturnStmt(const std::shared_ptr<ReturnStmt>& stmt) override;
	void visitVarStmt(const std::shared_ptr<VarStmt>& stmt) override;
	void visitWhileStmt(const std::shared_ptr<WhileStmt>& stmt) override;

private:
	enum EFunctionType
	{
		NONE_FUNC,
		FUNCTION,
		INITIALIZER,
		METHOD
	};

	enum EClassType
	{
		NONE_CLASS,
		CLASS,
		SUBCLASS
	};

	std::shared_ptr<Interpreter> m_interpreter;
	EFunctionType m_curFunctionType;
	EClassType m_curClassType;

	void resolve(const std::shared_ptr<Stmt>& stmt);
	void resolve(const std::shared_ptr<Expr>& expr);
	void resolveLocal(const std::shared_ptr<Expr>& expr, Token name);
	void resolveFunction(const std::shared_ptr<FunctionStmt>& function, EFunctionType type);

	void beginScope();
	void endScope();

	void declare(Token name);
	void define(Token name);

	std::vector<std::map<std::string, bool>> m_scopeStack;
};

