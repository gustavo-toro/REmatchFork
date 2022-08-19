
// Generated from REmatchParser.g4 by ANTLR 4.10.1

#pragma once


#include "antlr4-runtime.h"
#include "REmatchParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by REmatchParser.
 */
class  REmatchParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by REmatchParser.
   */
    virtual std::any visitRoot(REmatchParser::RootContext *context) = 0;

    virtual std::any visitAlternation(REmatchParser::AlternationContext *context) = 0;

    virtual std::any visitExpr(REmatchParser::ExprContext *context) = 0;

    virtual std::any visitElement(REmatchParser::ElementContext *context) = 0;

    virtual std::any visitGroup(REmatchParser::GroupContext *context) = 0;

    virtual std::any visitParentheses(REmatchParser::ParenthesesContext *context) = 0;

    virtual std::any visitAssignation(REmatchParser::AssignationContext *context) = 0;

    virtual std::any visitVariable(REmatchParser::VariableContext *context) = 0;

    virtual std::any visitAtom(REmatchParser::AtomContext *context) = 0;

    virtual std::any visitCharacter_class(REmatchParser::Character_classContext *context) = 0;

    virtual std::any visitCc_atom(REmatchParser::Cc_atomContext *context) = 0;

    virtual std::any visitCc_range(REmatchParser::Cc_rangeContext *context) = 0;

    virtual std::any visitCc_literal(REmatchParser::Cc_literalContext *context) = 0;

    virtual std::any visitCc_escapes(REmatchParser::Cc_escapesContext *context) = 0;

    virtual std::any visitCc_other(REmatchParser::Cc_otherContext *context) = 0;

    virtual std::any visitLiteral(REmatchParser::LiteralContext *context) = 0;

    virtual std::any visitEscapes(REmatchParser::EscapesContext *context) = 0;

    virtual std::any visitOther(REmatchParser::OtherContext *context) = 0;

    virtual std::any visitShared_atom(REmatchParser::Shared_atomContext *context) = 0;

    virtual std::any visitQuantifier(REmatchParser::QuantifierContext *context) = 0;

    virtual std::any visitQuantity(REmatchParser::QuantityContext *context) = 0;

    virtual std::any visitQuantExact(REmatchParser::QuantExactContext *context) = 0;

    virtual std::any visitQuantRange(REmatchParser::QuantRangeContext *context) = 0;

    virtual std::any visitQuantMin(REmatchParser::QuantMinContext *context) = 0;

    virtual std::any visitQuantMax(REmatchParser::QuantMaxContext *context) = 0;

    virtual std::any visitNumber(REmatchParser::NumberContext *context) = 0;


};

