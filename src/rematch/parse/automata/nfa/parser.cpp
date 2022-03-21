#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/core.hpp>
#include <boost/phoenix/operator.hpp>
#include <boost/phoenix/object.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "automata/nfa/lva.hpp"
#include "parser.hpp"
#include "parse/automata/nfa/grammar.hpp"
#include "parse/automata/nfa/visitor.hpp"


namespace rematch {

LogicalVA* parse_automata_file(std::string filename) {
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;

    std::ifstream file(filename);

    std::string str;
    file_to_automata visitor = file_to_automata();
    automata_parser<iterator_type> grammar;
    while (std::getline(file, str)) {
        automata::any emp;
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();

        if (std::all_of(iter, end, isspace)) { continue; }

        bool r = qi::phrase_parse(iter, end, grammar, space, emp);

        if (r && iter == end)
        {
            boost::apply_visitor(visitor, emp);
        }
        else
        {
            std::cout << "Error parsing line\n";
        }
    }

    return visitor.automata;
}

} // end namespace rematch