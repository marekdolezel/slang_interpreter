/**
 *@file Lexer.hpp
 * @author Your Name Here (your email)
 * @brief Lexical analyzer for slang programs
 * @version 0.1
 * @copyright Copyright (c) 2023
 */


#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"


#include <optional>
#include <string>
#include <unordered_set>

class Lexer {
private:
  std::unordered_set<std::string> keywords;
  // Other lexer state variables...

public:
  Lexer(const std::unordered_set<std::string>& keywords) : keywords(keywords) {}

  Token GetToken() {
    // Implementation of GetToken
    // Return Token of type Error if a lexical error occurs
  }

  // Other methods...
};


#endif
