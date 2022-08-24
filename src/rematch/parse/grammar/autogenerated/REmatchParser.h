
// Generated from REmatchParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  REmatchParser : public antlr4::Parser {
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

  enum {
    RuleRoot = 0, RuleAlternation = 1, RuleExpr = 2, RuleElement = 3, RuleGroup = 4, 
    RuleParentheses = 5, RuleAssignation = 6, RuleAtom = 7, RuleCharacterClass = 8, 
    RuleCcAtom = 9, RuleCcRange = 10, RuleCcLiteral = 11, RuleCcEscapes = 12, 
    RuleCcOther = 13, RuleLiteral = 14, RuleEscapes = 15, RuleOther = 16, 
    RuleSharedAtom = 17, RuleQuantifier = 18, RuleQuantity = 19, RuleQuantExact = 20, 
    RuleQuantRange = 21, RuleQuantMin = 22, RuleQuantMax = 23, RuleNumber = 24
  };

  explicit REmatchParser(antlr4::TokenStream *input);

  REmatchParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~REmatchParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RootContext;
  class AlternationContext;
  class ExprContext;
  class ElementContext;
  class GroupContext;
  class ParenthesesContext;
  class AssignationContext;
  class AtomContext;
  class CharacterClassContext;
  class CcAtomContext;
  class CcRangeContext;
  class CcLiteralContext;
  class CcEscapesContext;
  class CcOtherContext;
  class LiteralContext;
  class EscapesContext;
  class OtherContext;
  class SharedAtomContext;
  class QuantifierContext;
  class QuantityContext;
  class QuantExactContext;
  class QuantRangeContext;
  class QuantMinContext;
  class QuantMaxContext;
  class NumberContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AlternationContext *alternation();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RootContext* root();

  class  AlternationContext : public antlr4::ParserRuleContext {
  public:
    AlternationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AlternationContext* alternation();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupContext *group();
    QuantifierContext *quantifier();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  GroupContext : public antlr4::ParserRuleContext {
  public:
    GroupContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParenthesesContext *parentheses();
    AssignationContext *assignation();
    AtomContext *atom();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupContext* group();

  class  ParenthesesContext : public antlr4::ParserRuleContext {
  public:
    ParenthesesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAR();
    AlternationContext *alternation();
    antlr4::tree::TerminalNode *R_PAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParenthesesContext* parentheses();

  class  AssignationContext : public antlr4::ParserRuleContext {
  public:
    AssignationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXCLAMAITON();
    antlr4::tree::TerminalNode *VARNAME();
    antlr4::tree::TerminalNode *L_CURLY();
    AlternationContext *alternation();
    antlr4::tree::TerminalNode *R_CURLY();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignationContext* assignation();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CharacterClassContext *characterClass();
    SharedAtomContext *sharedAtom();
    LiteralContext *literal();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AtomContext* atom();

  class  CharacterClassContext : public antlr4::ParserRuleContext {
  public:
    CharacterClassContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACK();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *HAT();
    std::vector<CcAtomContext *> ccAtom();
    CcAtomContext* ccAtom(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CharacterClassContext* characterClass();

  class  CcAtomContext : public antlr4::ParserRuleContext {
  public:
    CcAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CcRangeContext *ccRange();
    SharedAtomContext *sharedAtom();
    LiteralContext *literal();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CcAtomContext* ccAtom();

  class  CcRangeContext : public antlr4::ParserRuleContext {
  public:
    CcRangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<CcLiteralContext *> ccLiteral();
    CcLiteralContext* ccLiteral(size_t i);
    antlr4::tree::TerminalNode *HYPHEN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CcRangeContext* ccRange();

  class  CcLiteralContext : public antlr4::ParserRuleContext {
  public:
    CcLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CcEscapesContext *ccEscapes();
    CcOtherContext *ccOther();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CcLiteralContext* ccLiteral();

  class  CcEscapesContext : public antlr4::ParserRuleContext {
  public:
    CcEscapesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);
    antlr4::tree::TerminalNode *HAT();
    antlr4::tree::TerminalNode *HYPHEN();
    antlr4::tree::TerminalNode *R_BRACK();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CcEscapesContext* ccEscapes();

  class  CcOtherContext : public antlr4::ParserRuleContext {
  public:
    CcOtherContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HAT();
    antlr4::tree::TerminalNode *HYPHEN();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *BACKSLASH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CcOtherContext* ccOther();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EscapesContext *escapes();
    OtherContext *other();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  EscapesContext : public antlr4::ParserRuleContext {
  public:
    EscapesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);
    antlr4::tree::TerminalNode *L_BRACK();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *L_PAR();
    antlr4::tree::TerminalNode *R_PAR();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *PIPE();
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EscapesContext* escapes();

  class  OtherContext : public antlr4::ParserRuleContext {
  public:
    OtherContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACK();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *L_PAR();
    antlr4::tree::TerminalNode *R_PAR();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *PIPE();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *BACKSLASH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OtherContext* other();

  class  SharedAtomContext : public antlr4::ParserRuleContext {
  public:
    SharedAtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_DIGIT();
    antlr4::tree::TerminalNode *NOT_DECIMAL_DIGIT();
    antlr4::tree::TerminalNode *HORIZONTAL_WHITESPACE();
    antlr4::tree::TerminalNode *NOT_HORIZONTAL_WHITESPACE();
    antlr4::tree::TerminalNode *NEW_LINE();
    antlr4::tree::TerminalNode *NOT_NEW_LINE();
    antlr4::tree::TerminalNode *WHITESPACE();
    antlr4::tree::TerminalNode *NOT_WHITESPACE();
    antlr4::tree::TerminalNode *VERTICAL_WHITESPACE();
    antlr4::tree::TerminalNode *NOT_VERTICAL_WHITESPACE();
    antlr4::tree::TerminalNode *WORD_CHAR();
    antlr4::tree::TerminalNode *NOT_WORD_CHAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SharedAtomContext* sharedAtom();

  class  QuantifierContext : public antlr4::ParserRuleContext {
  public:
    QuantifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *QUESTION();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *L_CURLY();
    QuantityContext *quantity();
    antlr4::tree::TerminalNode *R_CURLY();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantifierContext* quantifier();

  class  QuantityContext : public antlr4::ParserRuleContext {
  public:
    QuantityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QuantExactContext *quantExact();
    QuantRangeContext *quantRange();
    QuantMinContext *quantMin();
    QuantMaxContext *quantMax();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantityContext* quantity();

  class  QuantExactContext : public antlr4::ParserRuleContext {
  public:
    QuantExactContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantExactContext* quantExact();

  class  QuantRangeContext : public antlr4::ParserRuleContext {
  public:
    QuantRangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NumberContext *> number();
    NumberContext* number(size_t i);
    antlr4::tree::TerminalNode *COMMA();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantRangeContext* quantRange();

  class  QuantMinContext : public antlr4::ParserRuleContext {
  public:
    QuantMinContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    antlr4::tree::TerminalNode *COMMA();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantMinContext* quantMin();

  class  QuantMaxContext : public antlr4::ParserRuleContext {
  public:
    QuantMaxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMMA();
    NumberContext *number();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QuantMaxContext* quantMax();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> DIGIT();
    antlr4::tree::TerminalNode* DIGIT(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NumberContext* number();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

