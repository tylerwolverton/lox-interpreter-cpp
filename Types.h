#pragma once
#include <string>

enum ETokenType
{
	// Single-character tokens.                      
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
	COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

	// One or two character tokens.                  
	BANG, BANG_EQUAL,
	EQUAL, EQUAL_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	// Literals.                                     
	IDENTIFIER, STRING, NUMBER,

	// Keywords.                                     
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
	PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

	END_OF_FILE
};

class Token
{
public:
	Token(ETokenType type, std::string lexeme, int m_lineNum)
		: m_type(type),
		  m_lexeme(lexeme),
		  m_lineNum(m_lineNum)
	{}

	ETokenType GetType() { return m_type; }
	std::string GetLexeme() { return m_lexeme; }
	int GetLineNum() { return m_lineNum; }

	/*template <typename T>
	T GetLiteralValue()
	{
		if (m_type == ETokenType::IDENTIFIER)
		{
			return m_lexeme;
		}
		else if (m_type == ETokenType::STRING)
		{
			return m_lexeme.substr(1, m_lexeme.size() - 1);
		}
		else if (m_type == ETokenType::NUMBER)
		{
			return std::stod(lexeme);
		}

		return NULL;
	}*/

	//const std::string ToString() const { return tokenStr; }

private:
	ETokenType m_type;
	std::string m_lexeme;
	int m_lineNum;
};