#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

#include "antlr4-runtime.h"
#include "automata/nfa/lva.hpp"
#include "visitors.hpp"
#include "parse/error_listener.hpp"
#include "parse/grammar/autogenerated/REmatchLexer.h"
#include "parse/grammar/autogenerated/REmatchParser.h"

namespace rematch {

LogicalVA doParse(const std::string& input);
std::unique_ptr<LogicalVA> regex2LVA(std::string regex);

} // end namespace rematch

#endif