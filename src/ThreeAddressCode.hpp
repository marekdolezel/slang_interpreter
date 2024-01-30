/**
 *@file ThreeAddressCode.hpp
 * @author Your Name Here (your email)
 * @brief Lexical analyzer for slang programs
 * @version 0.1
 * @copyright Copyright (c) 2023
 */


#ifndef THREE_ADDRESS_CODE_HPP
#define THREE_ADDRESS_CODE_HPP

enum class OperationCode {
  // Arithmetic operations: operation r1 r2 r3, infix notation: r3 = r1 op r2 
  I_Add,
  I_Subtract,
  I_Multiply,
  I_Divide,

  Add,
  Subtract,
  Multiply,
  Divide,

  Compare,

  Jump, // jump 32; jump to instruction at address 32

  // IO Instructions
  ReadInt,
  ReadDouble,
  PrintInt,
  PrintDouble,
  PrintString,

  // memory operations
  Store, // store r1, A; stores content of register r1 to variable A
  Load,  // load A, r1 ; loads content of variable A to register r1

};

/*
 * Original Code:
 *
 *
 * for (int i = 0; i < 10; i++)
 *   c = i + 2;
 *
 * generated code:
 *
 * set i 0 
 * CMP_LESS i 10 
 * JMP_FALSE outside:
 * c = i + 2 
 * outside: 
 */

struct ThreeAddressCode {
  OperationCode opCode;

  union {
    int i;
    double d;
  } operands[3];
  
};

#endif
