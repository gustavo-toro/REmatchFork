
// Generated from REmatchParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "REmatchParserVisitor.h"


/**
 * This class provides an empty implementation of REmatchParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  REmatchParserBaseVisitor : public REmatchParserVisitor {
public:

  virtual std::any visitRoot(REmatchParser::RootContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAlternation(REmatchParser::AlternationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(REmatchParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(REmatchParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroup(REmatchParser::GroupContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesis(REmatchParser::ParenthesisContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignation(REmatchParser::AssignationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable(REmatchParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAtom(REmatchParser::AtomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCharacter_class(REmatchParser::Character_classContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCc_atom(REmatchParser::Cc_atomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCc_range(REmatchParser::Cc_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCc_literal(REmatchParser::Cc_literalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCc_escapes(REmatchParser::Cc_escapesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCc_other(REmatchParser::Cc_otherContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(REmatchParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEscapes(REmatchParser::EscapesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOther(REmatchParser::OtherContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShared_atom(REmatchParser::Shared_atomContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantifier(REmatchParser::QuantifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantity(REmatchParser::QuantityContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantExact(REmatchParser::QuantExactContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantRange(REmatchParser::QuantRangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantMin(REmatchParser::QuantMinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQuantMax(REmatchParser::QuantMaxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(REmatchParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }


};

