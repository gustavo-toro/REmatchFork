#include "ast.hpp"

// These are the definitions for the stream operator on ast objects. It's
// required by Boost Spirit's debugging.

namespace ast {

std::ostream& operator<<(std::ostream& os, const anychar& a) {
    os << '.';
    return os;
}

std::ostream& operator<<(std::ostream& os, const anydigit& a) {
    os << "\\d";
    return os;
}

std::ostream& operator<<(std::ostream& os, const nondigit& a) {
    os << "\\D";
    return os;
}

std::ostream& operator<<(std::ostream& os, const anyword& a) {
    os << "\\w";
    return os;
}

std::ostream& operator<<(std::ostream& os, const nonword& a) {
    os << "\\W";
    return os;
}

std::ostream& operator<<(std::ostream& os, const anywhitespace& a) {
    os << "\\s";
    return os;
}

std::ostream& operator<<(std::ostream& os, const nonwhitespace& a) {
    os << "\\s";
    return os;
}

std::ostream& operator<<(std::ostream& os, const parenthesis& p) {
    os << "()";
    return os;
}

} // end namespace ast