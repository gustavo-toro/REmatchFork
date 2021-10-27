#ifndef PARSER_AUTOMATA_HPP
#define PARSER_AUTOMATA_HPP

#include <memory>

#include "automata/nfa/lva.hpp"

namespace rematch {

LogicalVA* parse_automata_file(std::string filename);

} // end namespace rematch

#endif