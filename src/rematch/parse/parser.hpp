#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

#include "automata/nfa/lva.hpp"

namespace rematch {

LogicalVA doParse(const std::string& input);
std::unique_ptr<LogicalVA> regex2LVA(std::string regex);

} // end namespace rematch

#endif