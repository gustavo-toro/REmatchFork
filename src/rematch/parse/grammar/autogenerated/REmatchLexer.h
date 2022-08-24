
// Generated from REmatchLexer.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  REmatchLexer : public antlr4::Lexer {
public:
  enum {
    DECIMAL_DIGIT = 1, NOT_DECIMAL_DIGIT = 2, HORIZONTAL_WHITESPACE = 3, 
    NOT_HORIZONTAL_WHITESPACE = 4, NEW_LINE = 5, NOT_NEW_LINE = 6, WHITESPACE = 7, 
    NOT_WHITESPACE = 8, VERTICAL_WHITESPACE = 9, NOT_VERTICAL_WHITESPACE = 10, 
    WORD_CHAR = 11, NOT_WORD_CHAR = 12, VARNAME = 13, PIPE = 14, EXCLAMAITON = 15, 
    L_CURLY = 16, R_CURLY = 17, L_PAR = 18, R_PAR = 19, COMMA = 20, QUESTION = 21, 
    PLUS = 22, STAR = 23, HAT = 24, HYPHEN = 25, L_BRACK = 26, R_BRACK = 27, 
    BACKSLASH = 28, ALPHA = 29, DIGIT = 30, DOT = 31, UNRECOGNIZED = 32
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

