
// Generated from REmatchLexer.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  REmatchLexer : public antlr4::Lexer {
public:
  enum {
    DECIMAL_DIGIT = 1, NOT_DECIMAL_DIGIT = 2, HORIZONTAL_WHITESPACE = 3, 
    NOT_HORIZONTAL_WHITESPACE = 4, NEW_LINE = 5, NOT_NEW_LINE = 6, WHITESPACE = 7, 
    NOT_WHITESPACE = 8, VERTICAL_WHITESPACE = 9, NOT_VERTICAL_WHITESPACE = 10, 
    WORD_CHAR = 11, NOT_WORD_CHAR = 12, PIPE = 13, EXCLAMAITON = 14, L_CURLY = 15, 
    R_CURLY = 16, L_PAR = 17, R_PAR = 18, COMMA = 19, QUESTION = 20, PLUS = 21, 
    STAR = 22, HAT = 23, HYPHEN = 24, L_BRACK = 25, R_BRACK = 26, BACKSLASH = 27, 
    DIGIT = 28, ALPHANUMERIC = 29, DOT = 30, UNRECOGNIZED = 31
  };

  explicit REmatchLexer(antlr4::CharStream *input);

  ~REmatchLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

