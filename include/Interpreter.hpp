/**
 *@file Interpreter.hpp
 * @author Your Name Here (your email)
 * @brief Lexical analyzer for slang programs
 * @version 0.1
 * @copyright Copyright (c) 2023
 */


#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
// #include "ThreeAddressCode.hpp"
#include <iostream>
constexpr int numberOfRegisters = 32;

class Interpreter {
  // private:
    // bool compare;
    // int ireg[numberOfRegisters];    // integer registers
    // double dreg[numberOfRegisters]; // double registers
    // 
    // std::vector<int> imemory;
    // std::vector<double> dmemory;

    // std::vector<struct ThreeAddressCode> &code;

  public:
    // void setCode(const std::vector<struct ThreeAddressCode> &code) { this->code = code; }
    void inter()  { std::cout << "Hello wordl"; }
};

#endif
