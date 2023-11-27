#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Lexer.hpp"
#include "Token.hpp"

struct ExpectedToken {
  TokenType type;
  std::string attribute;
};

class Testing {
  private:
    Lexer *lexer;
    struct Stats {
      int m_total;
      int m_passed;
      int m_failed;
      Stats(): m_total(0), m_passed(0), m_failed(0) {} 
    } m_stats;
    int m_testNumber;
    std::string m_testMessage;
    std::vector<int> m_failedTestsNumbers;
  public: 
    Testing(): m_testNumber(1) { }
    void testFailed() { m_stats.m_failed++; m_stats.m_total++; }
    void testPassed() { m_stats.m_passed++; m_stats.m_total++; }
    void printStats() {

      if (m_stats.m_total == m_stats.m_passed)
        std::cout << "All tests passed out of " << m_stats.m_total << std::endl;

      std::cout << "Total Tests: " << m_stats.m_total << std::endl;
      std::cout << "Passed Tests: " << m_stats.m_passed << std::endl;
      std::cout << "Failed Tests: " << m_stats.m_failed << " ( failed tests: ";

      for (const auto &element : m_failedTestsNumbers) {
          std::cout << element << ", ";
      }
      std::cout << " )" << std::endl;
    }
    void setup(std::string program) { lexer = new Lexer(program);  }
    void teardown() { delete lexer; m_testMessage = ""; }
    bool test(std::string description, TokenType types[], const char* attributes[], int size);
    void runTest(std::string description, std::string program, TokenType types[], const char* attributes[], int size) {
      std::cout << "Test " << m_testNumber << " " + description + " "; 
      setup(program);
      bool testResult = test(description, types, attributes, size);
      if (testResult == true) {
        std::cout << "OK" << std::endl;
        testPassed();
      }
      else {
        std::cout << "FAIL" << std::endl;
        testFailed();
        m_failedTestsNumbers.push_back(m_testNumber);
      }
      std::cout << m_testMessage;
      teardown();
      std::cout << std::endl << std::endl;

      m_testNumber++;
    }
};

std::string LoadFile(std::string filename) {
  std::ifstream fileStream(filename);
  std::stringstream buffer;

  // file.open(fileName);

  if (!fileStream.is_open()) {
    printf("Failed to open file: %s\n", filename.c_str());
    return "";
  }

  buffer << fileStream.rdbuf(); // Read file content into stringstream
  std::cout << "File Contents: " << buffer.str() << std::endl;
  return buffer.str();         // Return the stringstream content as string
}

void FileDriverMode(std::string filename) {
  std::string program = LoadFile(filename);
  Lexer lexer(program);
  Token* token;
  
  while ((token = lexer.getToken())->getType() != TokenType::EndOfFile) { // TODO have condition with getType() == TokenType::EndOfFile
    
    token->printToken();
    delete token;
  }
}

bool Testing::test(std::string description, TokenType types[], const char* attributes[], int size)
{
  Token *token = nullptr;
  bool testPassed = true;

  for (int i = 0; i < size; ++i) {

    token = lexer->getToken();

    m_testMessage += "\t" + std::to_string(i+1) + ". ";

    if (token->getType() != types[i]) {
      testPassed = false;

      m_testMessage += "\tExpected: <" + Token::tokenTypeToString(types[i]) + ", '" + attributes[i] + "'> ";
      m_testMessage += " Got: <" + token->tokenTypeToString(token->getType()) + ", '" + token->getAttribute() + "'>\n";
    }
    else {
      if (token->getAttribute() == attributes[i]) 
        m_testMessage +=  "\tGot: <" + Token::tokenTypeToString(types[i]) + ", '" + attributes[i] + "'>\n";

    }
    delete token;
  }
  return testPassed;
}

int main(int argc, char *argv[]) {
  if (argc == 3 && argv[1][0] == 'd') { // ./programName d filepath
    std::cout << "FileDriverMode" << std::endl;
    FileDriverMode(argv[2]);
    
    return 0;
  }

  Testing testingObject;
  /*
   * Mini-tutorial:
   *  - each test has its own scope {}
   *  - 'token_types[]' and 'token_attributes[]' array stores expected token
   * types and attributes
   *  - test(test_name, source_buff, token_types, token_attributes, size)
   *      + test_name: is a name of test (C string type)
   *      + source_buff: is a buffer with source program
   *      + token_types: is an array of expected tokens
   *      + token_attributes: is an array of expected attributes
   *      + size: is size of 'token_types[]' and 'token_attributes[]' arrays
   */

    // Test 1:
    {
        ExpectedToken expectedTokens[] = {
          {TokenType::EndOfFile, ""}
        }
        TokenType token_types[] = {TokenType::EndOfFile};
        const char* token_attributes[] = {"", ""};
        int size = 1;
        testingObject.runTest("Empty input", "", token_types, token_attributes, size);
    }

    // Test 2:
    {
        TokenType token_types[] = {TokenType::Plus, TokenType::Minus, TokenType::Star, TokenType::Slash, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Arithmetic operators +-*/", "+   -  * / ", token_types, token_attributes, size);
    }

    // Test 3:
    {
        TokenType token_types[] = {TokenType::Minus, TokenType::Minus, TokenType::Star, TokenType::Slash, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Arithmetic operators --*/", "-   -  * / ", token_types, token_attributes, size);
    }

    // Test 4:
    {
        TokenType token_types[] = {TokenType::OperatorComparison, TokenType::OperatorGreaterThan, 
                                    TokenType::OperatorGreaterThanEqual, TokenType::OperatorLessThan, 
                                    TokenType::OperatorLessThanEqual, TokenType::OperatorNotEqual, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", "", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Comparison operators == > >= < <= !=", "== > >= < <= !=", token_types, token_attributes, size);
    }

    // Test 5:
    {
        TokenType token_types[] = {TokenType::LeftBrace, TokenType::RightBrace, TokenType::LeftParenthesis,
                                    TokenType::RightParenthesis, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Braces and Parentheses {} ()", "{} ()", token_types, token_attributes, size);
    }

    // Test 6:
    {
        TokenType token_types[] = {TokenType::KeywordBoolean, TokenType::KeywordBreak, TokenType::KeywordCharacter,
                                    TokenType::KeywordContinue, TokenType::KeywordDo, TokenType::KeywordDouble,
                                    TokenType::KeywordElse, TokenType::KeywordFalse, TokenType::KeywordFor,
                                    TokenType::KeywordIf, TokenType::KeywordInt, TokenType::KeywordReturn,
                                    TokenType::KeywordString, TokenType::KeywordTrue, TokenType::KeywordVoid,
                                    TokenType::KeywordWhile, TokenType::EndOfFile};
        const char* token_attributes[] = {
            "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", ""
        };
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("All Keywords", "bool break char continue do double else false for if int return string true void while",
             token_types, token_attributes, size);
    }

    // Test 7:
    {
        TokenType token_types[] = {TokenType::Semicolon, TokenType::Comma, TokenType::Colon, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Punctuation ; , :", "; , :", token_types, token_attributes, size);
    }

    // Test 8:
    {
        TokenType token_types[] = {TokenType::LiteralInt, TokenType::LiteralDouble, TokenType::LiteralString,
                                    TokenType::LiteralChar, TokenType::EndOfFile};
        const char* token_attributes[] = {"42", "3.14", "some string", "J", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Numeric literals 42 3.14 \"some string\" 'J'", "42 3.14 \"some string\" 'J' ", token_types, token_attributes, size);
    }

    // Test 9:
    {
        TokenType token_types[] = {TokenType::OperatorAssignment, TokenType::Identifier, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "myVar", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Assignment and Identifier = myVar", "= myVar", token_types, token_attributes, size);
    }

    // Test 10:
    {
        TokenType token_types[] = {TokenType::Error, TokenType::EndOfFile};
        const char* token_attributes[] = {"", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Error handling invalid token !", "!", token_types, token_attributes, size);
    }

    // Test 11:
    {
        TokenType token_types[] = {TokenType::Error, TokenType::Error, TokenType::Error, TokenType::Error, TokenType::EndOfFile};
        const char* token_attributes[] = {"", "", "", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Invalid tokens ? ? ? ?", "? ? ? ?", token_types, token_attributes, size);
    }

    // Test 12:
    {
        TokenType token_types[] = {TokenType::LiteralInt, TokenType::Plus, TokenType::LiteralInt, TokenType::EndOfFile};
        const char* token_attributes[] = {"123", "", "987", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Addition test (spaces) 123 + 987", "123 + 987", token_types, token_attributes, size);
    }

    // Test 13:
    {
        TokenType token_types[] = {TokenType::LiteralInt, TokenType::Plus, TokenType::LiteralInt, TokenType::EndOfFile};
        const char* token_attributes[] = {"123", "", "987", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("Addition test (no spaces) 123+987", "123+987", token_types, token_attributes, size);
    }

    // Test 14:
    {
        TokenType token_types[] = {TokenType::Identifier, TokenType::LeftParenthesis, TokenType::EndOfFile};
        const char* token_attributes[] = {"myIdentifier", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("leftParenthesis after identifier", "myIdentifier(", token_types, token_attributes, size);
    }

    // Test 15:
    {
        TokenType token_types[] = {TokenType::Identifier, TokenType::LeftParenthesis, TokenType::EndOfFile};
        const char* token_attributes[] = {"myIdentifier", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("identifier ( (with space)", "myIdentifier (", token_types, token_attributes, size);
    }

    // Test 16:
    {
        TokenType token_types[] = {TokenType::LiteralString, TokenType::LeftParenthesis, TokenType::EndOfFile};
        const char* token_attributes[] = {"mynameisearl", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("\"mynameisearl\"(", "\"mynameisearl\"(", token_types, token_attributes, size);
    }

    // Test 17:
    {
        TokenType token_types[] = {TokenType::LiteralInt, TokenType::Plus, TokenType::EndOfFile};
        const char* token_attributes[] = {"123", "", ""};
        int size = sizeof(token_types) / sizeof(TokenType);
        testingObject.runTest("symbol after integer literal", "123+", token_types, token_attributes, size);
    }

    testingObject.printStats();

  
}
