#include "parser.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

#include "automata/wnfa/wnfa.hpp"
#include "parse/automata/wva/grammar.hpp"
#include "parse/automata/wva/visitor.hpp"

namespace rematch {

ranked::WeightedVA<>* parse_wva_file(std::string filename) {
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;

    std::ifstream file(filename);

    std::string str;
    auto visitor = wVAvisitor();
    wva_parser<iterator_type> grammar;
    while (std::getline(file, str)) {
        ast::wva::any emp;
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