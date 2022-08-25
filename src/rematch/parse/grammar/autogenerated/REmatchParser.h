
// Generated from REmatchParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  REmatchParser : public antlr4::Parser {
public:
  enum {
    DECIMAL_DIGIT = 1, NOT_DECIMAL_DIGIT = 2, WHITESPACE = 3, NOT_WHITESPACE = 4, 
    ALPHANUMERIC = 5, NOT_ALPHANUMERIC = 6, TAB = 7, CARRIAGE_RETURN = 8, 
    NEWLINE = 9, VERTICAL_WHITESPACE = 10, FORM_FEED = 11, VARNAME = 12, 
    PIPE = 13, EXCLAMAITON = 14, L_CURLY = 15, R_CURLY = 16, L_PAR = 17, 
    R_PAR = 18, COMMA = 19, QUESTION = 20, PLUS = 21, STAR = 22, HAT = 23, 
    HYPHEN = 24, L_BRACK = 25, R_BRACK = 26, BACKSLASH = 27, ALPHA = 28, 
    DIGIT = 29, DOT = 30, UNRECOGNIZED = 31
  };

  enum {
    RuleRoot = 0, RuleAlternation = 1, RuleExpr = 2, RuleElement = 3, RuleGroup = 4, 
    RuleParentheses = 5, RuleAssignation = 6, RuleAtom = 7, RuleCharacterClass = 8, 
    RuleCcAtom = 9, RuleCcRange = 10, RuleCcLiteral = 11, RuleCcEscapes = 12, 
    RuleCcOther = 13, RuleLiteral = 14, RuleEscapes = 15, RuleSpecial = 16, 
    RuleOther = 17, RuleSharedAtom = 18, RuleQuantifier = 19, RuleQuantity = 20, 
    RuleQuantExact = 21, RuleQuantRange = 22, RuleQuantMin = 23, RuleQuantMax = 24, 
    RuleNumber = 25
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
  class SpecialContext;
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
    SpecialContext *special();
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

  class  SpecialContext : public antlr4::ParserRuleContext {
  public:
    SpecialContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TAB();
    antlr4::tree::TerminalNode *CARRIAGE_RETURN();
    antlr4::tree::TerminalNode *NEWLINE();
    antlr4::tree::TerminalNode *VERTICAL_WHITESPACE();
    antlr4::tree::TerminalNode *FORM_FEED();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SpecialContext* special();

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
    antlr4::tree::TerminalNode *WHITESPACE();
    antlr4::tree::TerminalNode *NOT_WHITESPACE();
    antlr4::tree::TerminalNode *ALPHANUMERIC();
    antlr4::tree::TerminalNode *NOT_ALPHANUMERIC();


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

