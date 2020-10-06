#include <string>
#include <cassert>
#include "parser.hpp"
#include "visitors.hpp"
#include "grammar.hpp"

bool doParse(const std::string& input, ast::altern &data)
/* Parses input and stores the AST in data */
{
   using strit =  std::string::const_iterator;

    static const parser<strit> p; // Parser

    try
    {
        strit f(begin(input)), l(end(input));
        bool ok = qi::parse(f,l,p, data);
        if (!ok)
            std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

        if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
        return ok;
    } catch(const qi::expectation_failure<strit>& e)
    {
        std::string frag(e.first, e.last);
        std::cerr << e.what() << " at '" << frag << "'\n";
        return false;
    } catch(std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
};


LogicalVA& regex2LVA(std::string regex) {
	ast::altern tree;

 	doParse(regex, tree);

	std::unique_ptr<VariableFactory> v = visitors::regex2vars()(tree);
	FilterFactory& f = visitors::regex2filters()(tree);

	return visitors::regex2LVA(v,f)(tree);
}
