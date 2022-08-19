
// Generated from REmatchParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"




class  REmatchParser : public antlr4::Parser {
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

  enum {
    RuleRoot = 0, RuleAlternation = 1, RuleExpr = 2, RuleElement = 3, RuleGroup = 4, 
    RuleParenthesis = 5, RuleAssignation = 6, RuleVariable = 7, RuleAtom = 8, 
    RuleCharacter_class = 9, RuleCc_atom = 10, RuleCc_range = 11, RuleCc_literal = 12, 
    RuleCc_escapes = 13, RuleCc_other = 14, RuleLiteral = 15, RuleEscapes = 16, 
    RuleOther = 17, RuleShared_atom = 18, RuleQuantifier = 19, RuleQuantity = 20, 
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
  class ParenthesisContext;
  class AssignationContext;
  class VariableContext;
  class AtomContext;
  class Character_classContext;
  class Cc_atomContext;
  class Cc_rangeContext;
  class Cc_literalContext;
  class Cc_escapesContext;
  class Cc_otherContext;
  class LiteralContext;
  class EscapesContext;
  class OtherContext;
  class Shared_atomContext;
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
    ParenthesisContext *parenthesis();
    AssignationContext *assignation();
    AtomContext *atom();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupContext* group();

  class  ParenthesisContext : public antlr4::ParserRuleContext {
  public:
    ParenthesisContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAR();
    AlternationContext *alternation();
    antlr4::tree::TerminalNode *R_PAR();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParenthesisContext* parenthesis();

  class  AssignationContext : public antlr4::ParserRuleContext {
  public:
    AssignationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXCLAMAITON();
    VariableContext *variable();
    antlr4::tree::TerminalNode *L_CURLY();
    AlternationContext *alternation();
    antlr4::tree::TerminalNode *R_CURLY();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignationContext* assignation();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ALPHANUMERIC();
    antlr4::tree::TerminalNode* ALPHANUMERIC(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableContext* variable();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Character_classContext *character_class();
    Shared_atomContext *shared_atom();
    LiteralContext *literal();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AtomContext* atom();

  class  Character_classContext : public antlr4::ParserRuleContext {
  public:
    Character_classContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACK();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *HAT();
    std::vector<Cc_atomContext *> cc_atom();
    Cc_atomContext* cc_atom(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Character_classContext* character_class();

  class  Cc_atomContext : public antlr4::ParserRuleContext {
  public:
    Cc_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Cc_rangeContext *cc_range();
    Shared_atomContext *shared_atom();
    LiteralContext *literal();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cc_atomContext* cc_atom();

  class  Cc_rangeContext : public antlr4::ParserRuleContext {
  public:
    Cc_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Cc_literalContext *> cc_literal();
    Cc_literalContext* cc_literal(size_t i);
    antlr4::tree::TerminalNode *HYPHEN();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cc_rangeContext* cc_range();

  class  Cc_literalContext : public antlr4::ParserRuleContext {
  public:
    Cc_literalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Cc_escapesContext *cc_escapes();
    Cc_otherContext *cc_other();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cc_literalContext* cc_literal();

  class  Cc_escapesContext : public antlr4::ParserRuleContext {
  public:
    Cc_escapesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> BACKSLASH();
    antlr4::tree::TerminalNode* BACKSLASH(size_t i);
    antlr4::tree::TerminalNode *HAT();
    antlr4::tree::TerminalNode *HYPHEN();
    antlr4::tree::TerminalNode *R_BRACK();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cc_escapesContext* cc_escapes();

  class  Cc_otherContext : public antlr4::ParserRuleContext {
  public:
    Cc_otherContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HAT();
    antlr4::tree::TerminalNode *HYPHEN();
    antlr4::tree::TerminalNode *R_BRACK();
    antlr4::tree::TerminalNode *BACKSLASH();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Cc_otherContext* cc_other();

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

  class  Shared_atomContext : public antlr4::ParserRuleContext {
  public:
    Shared_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
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

  Shared_atomContext* shared_atom();

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

