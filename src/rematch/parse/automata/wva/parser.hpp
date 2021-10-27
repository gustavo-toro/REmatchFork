#ifndef PARSER_AUTOMATA_HPP
#define PARSER_AUTOMATA_HPP

#include <memory>

#include "automata/wnfa/wnfa.hpp"

namespace rematch {

ranked::WeightedVA<>* parse_wva_file(std::string filename);

} // end namespace rematch

#endif