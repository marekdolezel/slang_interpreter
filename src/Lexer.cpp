/**
 * @file Lexer.cpp
 * @author Marek Dolezel
 * @brief Lexer
 * @version 0.1
 * @copyright Copyright (c) 2023
 */

#include <iostream>
#include "Lexer.hpp"
#include "Token.hpp"
#include <string>

Token* Lexer::getToken() {
  const char *oneCharSymbols = "+-*(){};,:";
  TokenType oneCharSymbols_TokenTypes[] = {
      TokenType::Plus, TokenType::Minus, TokenType::Star, TokenType::LeftParenthesis, TokenType::RightParenthesis,
      TokenType::LeftBrace, TokenType::RightBrace, TokenType::Semicolon, TokenType::Comma, TokenType::Colon};

  std::string attribute; // identifiers and literals have attributes, for example: 42 is represented as token <LiteralInt, "42">

  // Skip over whitespace
  char c = Lexer::GetSymbol();
  while (c == '\t' || c == ' ' || c == '\n')
    c = Lexer::GetSymbol();

  if (c == '\0')
    return new Token(TokenType::EndOfFile);

  // Comments (C style)
  if (c == '/' && Lexer::GetSymbol(false) == '/') {
    while ((c = Lexer::GetSymbol()) != '\n')
      ;
    c = Lexer::GetSymbol();
  }

  // Comment C++ style
  if (c == '/' && Lexer::GetSymbol(false) == '*') {
    Lexer::GetSymbol(); // must eat star after slash
    while ((c = Lexer::GetSymbol()) != '*' || Lexer::GetSymbol(false) != '/')
      ; // TODO fix this condition
  }

  // Just slash, there was no additional slash or star
  if (c == '/') {
    attribute.push_back(c);
    return new Token(TokenType::Slash);
  }

  // identifier
  if (isalpha(c) || c == '$' || c == '_') {
    attribute.push_back(c);
    c = Lexer::GetSymbol();
    while (isalnum(c) || c == '$' || c == '_') {
      attribute.push_back(c);
      c = Lexer::GetSymbol();
    }
    this->m_index--; // do not eat symbol after identifier, keyword
;
    return new Token(TokenType::Identifier);
  }

  // arrow
  if (c == '-' && Lexer::GetSymbol(false) == '>') {
    Lexer::GetSymbol(); // must eat star after minus
                        //
    return new Token(TokenType::Arrow);
  }

  // one symbol tokens
  if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')' || c == '{' ||
      c == '}' || c == ';' || c == ',' || c == ':') {
    attribute.push_back(c);
    for (int i = 0; i < 10; i++)
      if (c == oneCharSymbols[i]) {
        return new Token(oneCharSymbols_TokenTypes[i]);
      }
  }

  // string literals
  if (c == '"') {
    c = Lexer::GetSymbol();
    while (c >= 32 && c <= 127 && c != '"') {
      attribute.push_back(c);
      c = Lexer::GetSymbol();
    }
    return new Token(TokenType::LiteralString, attribute);
  }

  // character literals
  if (c == '\'' && Lexer::GetSymbol(false) >= 32 && Lexer::GetSymbol(false) <= 127) {
    c = Lexer::GetSymbol(); // letter inside ''
    attribute.push_back(c);
    if (Lexer::GetSymbol() == '\'')
      return new Token(TokenType::LiteralChar, attribute);
    else
      return new Token(TokenType::Error);
  }

  // numeric literals
  if (isnumber(c)) {
    while (isnumber(c)) {
      attribute.push_back(c);
      c = Lexer::GetSymbol();
    }

    if (c == '.') {
      attribute.push_back(c);
      c = Lexer::GetSymbol();
      while (isnumber(c)) {
        attribute.push_back(c);
        c = Lexer::GetSymbol();
      }
      this->m_index--; // for next run of lexer
      return new Token(TokenType::LiteralDouble, attribute); 

    }
    this->m_index--; // do not eat symbol after numeric literal
    return new Token(TokenType::LiteralInt, attribute);
  }

  // comparison operators
  if (c == '=' || c == '>' || c == '<' || c == '!') {
    attribute.push_back(c);
    if (Lexer::GetSymbol(false) ==
        '=') { // just look what next symbol is. if next symbol is something
               // else than equals, then we don't have to decrement index
      attribute = attribute + GetSymbol(false);
      GetSymbol();
      // string_add_char(attribute, Lexer::GetSymbol(false));
      // Lexer::GetSymbol();
      switch (c) {
      case '=':
        return new Token(TokenType::OperatorComparison);
      case '>':
        return new Token(TokenType::OperatorGreaterThanEqual);
      case '<':
        return new Token(TokenType::OperatorLessThanEqual);
      case '!':
        return new Token(TokenType::OperatorNotEqual);
      }
    }

    // next symbol is not equal symbol, but something else
    switch (c) {
    case '=':
      return new Token(TokenType::OperatorAssignment);
    case '>':
      return new Token(TokenType::OperatorGreaterThan);
    case '<':
      return new Token(TokenType::OperatorLessThan);
    case '!':
      return new Token(TokenType::Error); // this is error
    }
  }

  return new Token(TokenType::Error);
}
