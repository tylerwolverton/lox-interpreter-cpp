#include "Interpreter.h"

#include <iostream>

Interpreter::Interpreter()
{
	//m_environment = Environment();
}

Interpreter::~Interpreter()
{
}

void Interpreter::Interpret(const std::vector<std::shared_ptr<Stmt>>& statements)
{
	for (auto stmt : statements)
	{
		//std::shared_ptr<Token> value = std::static_pointer_cast<Token>(evaluate(expr));
		execute(stmt);
	}
}

std::shared_ptr<void> Interpreter::visitAssignExpr(const std::shared_ptr<AssignExpr>& expr)
{
	std::shared_ptr<Token> value = std::static_pointer_cast<Token>(evaluate(expr->m_value));

	m_environment.Assign(expr->m_name, value);
	return value;
}

std::shared_ptr<void> Interpreter::visitBinaryExpr(const std::shared_ptr<BinaryExpr>& expr)
{
	std::shared_ptr<Token> left = std::static_pointer_cast<Token>(evaluate(expr->m_left));
	std::shared_ptr<Token> right = std::static_pointer_cast<Token>(evaluate(expr->m_right));

	switch (expr->m_op.GetType())
	{
		case ETokenType::BANG_EQUAL:
				return std::make_shared<bool>(!isEqual(left, right));
		case ETokenType::EQUAL_EQUAL:
			return std::make_shared<bool>(isEqual(left, right));
	}

	if (left->GetType() == ETokenType::NUMBER
		&& right->GetType() == ETokenType::NUMBER)
	{
		switch (expr->m_op.GetType())
		{
			case ETokenType::GREATER:
				return createTruthToken(left->GetLexemeAsDouble() > right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::GREATER_EQUAL:
				return createTruthToken(left->GetLexemeAsDouble() >= right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::LESS:
				return createTruthToken(left->GetLexemeAsDouble() < right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::LESS_EQUAL:
				return createTruthToken(left->GetLexemeAsDouble() <= right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::MINUS:
				return createNumberToken(left->GetLexemeAsDouble() - right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::SLASH:
				return createNumberToken(left->GetLexemeAsDouble() / right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::STAR:
				return createNumberToken(left->GetLexemeAsDouble() * right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
			case ETokenType::PLUS:
				return createNumberToken(left->GetLexemeAsDouble() + right->GetLexemeAsDouble(), expr->m_op.GetLineNum());
		}
	}

	if (left->GetType() == ETokenType::STRING
		&& right->GetType() == ETokenType::STRING
		&& expr->m_op.GetType() == ETokenType::PLUS)
	{
		return createStringToken(left->GetLexeme() + right->GetLexeme(), expr->m_op.GetLineNum());
	}

	// Unreachable
	return nullptr;
}

std::shared_ptr<void> Interpreter::visitGroupingExpr(const std::shared_ptr<GroupingExpr>& expr)
{
	return evaluate(expr->m_expr);
}

std::shared_ptr<void> Interpreter::visitLiteralExpr(const std::shared_ptr<LiteralExpr>& expr)
{
	return std::make_shared<Token>(expr->m_literal);
}

std::shared_ptr<void> Interpreter::visitUnaryExpr(const std::shared_ptr<UnaryExpr>& expr)
{
	std::shared_ptr<Token> right = std::static_pointer_cast<Token>(evaluate(expr->m_right));

	switch (expr->m_op.GetType())
	{
		case ETokenType::BANG:
			return createTruthToken(!isTruthy(right), right->GetLineNum());
		case ETokenType::MINUS:
			if (right->GetType() == ETokenType::NUMBER)
			{
				return createNumberToken(-(right->GetLexemeAsDouble()), right->GetLineNum());
			}
			else
			{
				// Throw type error
			}
	}

	// Unreachable
	return nullptr;
}

std::shared_ptr<void> Interpreter::visitVariableExpr(const std::shared_ptr<VariableExpr>& expr)
{
	return m_environment.Get(expr->m_name);
}

void Interpreter::visitBlockStmt(const std::shared_ptr<BlockStmt>& stmt)
{
	executeBlock(stmt->m_statements, Environment(std::make_shared<Environment>(m_environment)));
}

void Interpreter::executeBlock(std::vector<std::shared_ptr<Stmt>> statements, Environment environment)
{
	Environment previous = m_environment;
	try 
	{
		m_environment = environment;

		for (const auto& statement : statements) 
		{
			execute(statement);
		}

		m_environment = previous;
	}
	catch(...)
	{
		m_environment = previous;
	}
}

void Interpreter::visitExpressionStmt(const std::shared_ptr<ExpressionStmt>& stmt)
{
	evaluate(stmt->m_expr);
}

void Interpreter::visitPrintStmt(const std::shared_ptr<PrintStmt>& stmt)
{
	std::shared_ptr<Token> value = std::static_pointer_cast<Token>(evaluate(stmt->m_expr));
	std::cout << stringify(value) << std::endl;
}

void Interpreter::visitVarStmt(const std::shared_ptr<VarStmt>& stmt)
{
	std::shared_ptr<Token> value = nullptr;
	if (stmt->m_initializer != nullptr)
	{
		value = std::static_pointer_cast<Token>(evaluate(stmt->m_initializer));
	}

	m_environment.Define(stmt->m_name.GetLexeme(), value);
}

std::shared_ptr<void> Interpreter::evaluate(std::shared_ptr<Expr> expr)
{
	return expr->accept(*this);
}

bool Interpreter::isTruthy(std::shared_ptr<Token> token)
{
	switch (token->GetType())
	{
		case ETokenType::STRING:
		case ETokenType::NUMBER:
		case ETokenType::TRUE:
			return true;
	}

	return false;
}

void Interpreter::execute(std::shared_ptr<Stmt> stmt) 
{
	stmt->accept(*this);
}

bool Interpreter::isEqual(std::shared_ptr<Token> left, std::shared_ptr<Token> right)
{
	return false;
}

std::shared_ptr<Token> Interpreter::createTruthToken(bool value, int lineNum)
{
	ETokenType type = value ? ETokenType::TRUE : ETokenType::FALSE;
	std::string lexeme = value ? "true" : "false";

	return std::make_shared<Token>(type, lexeme, lineNum);
}

std::shared_ptr<Token> Interpreter::createNumberToken(double value, int lineNum)
{
	return std::make_shared<Token>(ETokenType::NUMBER, std::to_string(value), lineNum);
}

std::shared_ptr<Token> Interpreter::createStringToken(std::string value, int lineNum)
{
	return std::make_shared<Token>(ETokenType::STRING, value, lineNum);
}

std::string Interpreter::stringify(std::shared_ptr<Token> value)
{
	switch (value->GetType())
	{
	case ETokenType::NUMBER:
		return std::to_string(value->GetLexemeAsDouble());
	default:
		return value->GetLexeme();
	}
}