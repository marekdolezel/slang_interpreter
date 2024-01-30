/** @file Token.hpp
 *  @brief Token class for Slang
 *  @author Marek Dolezel
 *  @version 0.1
 *  @copyright Copyright (c) 2023
 */
#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include <string>
#include <unordered_map>

enum class TokenType {
  Identifier,

  // Literals
  LiteralInt,
  LiteralDouble,
  LiteralString,
  LiteralChar,

  // Operators
  OperatorAssignment,
  OperatorComparison,
  OperatorGreaterThan,
  OperatorGreaterThanEqual,
  OperatorLessThan,
  OperatorLessThanEqual,
  OperatorNotEqual,

  // Potential Binary Operations
  Plus,
  Minus,
  Slash,
  Star,

  // Braces
  LeftBrace,
  RightBrace,
  LeftParenthesis,
  RightParenthesis,

  // Keywords
  KeywordBoolean,
  KeywordBreak,
  KeywordCharacter,
  KeywordContinue,
  KeywordDo,
  KeywordDouble,
  KeywordElse,
  KeywordFalse,
  KeywordFor,
  KeywordFunc,
  KeywordIf,
  KeywordInt,
  KeywordReturn,
  KeywordString,
  KeywordTrue,
  KeywordVar,
  KeywordVoid,
  KeywordWhile,

  // Misc tokens
  Arrow,
  Semicolon,
  Comma,
  Colon,

  // Special tokens
  EndOfFile,
  Error
};

class Token {
private:
  TokenType m_type;
  std::string m_attribute;
public:

  

public:
  Token() : m_type(TokenType::None) { setKeywordType(); }
  Token(TokenType type) : m_type(type) {  }
  Token(TokenType type, std::string value) : m_type(type), m_attribute(value) { if (type == TokenType::Identifier) setKeywordType(); }
  TokenType getType() { return m_type; }
  std::string getAttribute() { return m_attribute; }
  void setValue(std::string value) { this->m_attribute = value; }
  void setType(TokenType type) { this->m_type = type; }

  void printToken() {
    std::cout << "TokenType is: " << tokenTypeToString(m_type) << " value is: " << m_attribute << std::endl;
  }
  
  
};

#endif // !TOKEN_HPP
