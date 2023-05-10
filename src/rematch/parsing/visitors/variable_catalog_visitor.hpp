#pragma once

#include "antlr4-runtime.h"
#include "parsing/bad_regex_exception.hpp"
#include "parsing/variable_catalog.hpp"
#include "parsing/grammar/autogenerated/REmatchParserBaseVisitor.h"

#define VARIABLE_CATALOG_VISITOR__DEBUG
#ifdef VARIABLE_CATALOG_VISITOR__DEBUG
#define VARIABLE_CATALOG_VISITOR__INFO(arg) std::cout << arg
#else
#define VARIABLE_CATALOG_VISITOR__INFO(arg)
#endif

namespace rematch {
namespace visitors {

class VariableCatalogVisitor : public REmatchParserBaseVisitor {
public:
  std::shared_ptr<VariableCatalog> vfact_ptr;

  std::any visitRoot(REmatchParser::RootContext *ctx) override {
    std::any vfact = visit(ctx->alternation());
    VariableCatalog& vfact_cast = std::any_cast<VariableCatalog &>(vfact);
    vfact_ptr = std::make_shared<VariableCatalog>(vfact_cast);

    return 0;
  }
private:
  std::any visitAlternation(REmatchParser::AlternationContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitAlternation" << std::endl;);
    std::any vfact = visit(ctx->expr().front());
    VariableCatalog &vfact_cast = std::any_cast<VariableCatalog &>(vfact);

    size_t children_size = ctx->expr().size();
    if (children_size > 1) {
      for (size_t i = 1; i < children_size; i++) {
        std::any rhs = visit(ctx->expr(i));
        VariableCatalog &rhs_cast = std::any_cast<VariableCatalog &>(rhs);
        vfact_cast.merge(rhs_cast);
      }
    }

    return vfact;
  }

  std::any visitExpr(REmatchParser::ExprContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitExpr" << std::endl;);
    std::any vfact = visit(ctx->element().front());
    VariableCatalog &vfact_cast = std::any_cast<VariableCatalog &>(vfact);

    size_t children_size = ctx->element().size();
    if (children_size > 1) {
      for (size_t i = 1; i < children_size; i++) {
        std::any rhs = visit(ctx->element()[i]);
        VariableCatalog &rhs_cast = std::any_cast<VariableCatalog &>(rhs);
        vfact_cast.merge(rhs_cast);
      }
    }

    return vfact;
  }

  std::any visitElement(REmatchParser::ElementContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitElement" << std::endl;);
    return visit(ctx->group());
  }

  std::any visitGroup(REmatchParser::GroupContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitGroup" << std::endl;);
    std::any vfact;

    if (ctx->parentheses()) {
      vfact = visit(ctx->parentheses());
    } else if (ctx->assignation()) {
      vfact = visit(ctx->assignation());
    } else {
      vfact = visit(ctx->atom());
    }

    return vfact;
  }

  std::any visitParentheses(REmatchParser::ParenthesesContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitParentheses" << std::endl;);
    return visit(ctx->alternation());
  }

  std::any visitAssignation(REmatchParser::AssignationContext *ctx) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitAssignation" << std::endl;);
    std::any vfact = visit(ctx->alternation());
    VariableCatalog &vfact_cast = std::any_cast<VariableCatalog &>(vfact);

    std::string var = ctx->varname()->getText();
    if (vfact_cast.contains(var)) {
      throw BadRegexException("Nested the same variables inside asignations");
    }
    vfact_cast.add(var);

    return vfact;
  }

  std::any visitAtom(REmatchParser::AtomContext*) override {
    VARIABLE_CATALOG_VISITOR__INFO("visitAtom" << std::endl;);
    return std::make_any<VariableCatalog>();
  }
};
} // namespace visitors
} // namespace rematch
