lexer grammar REmatchLexer;

// Composed tokens
VARNAME: EXCLAMATION_MARK [A-Za-z0-9\-_]+;
ESCAPE_CHARS: BACKSLASH [fnrtv];
META_CHARS: BACKSLASH [dDsSwW];
UINT: '0' | [1-9] [0-9]*;

DOT: '.';
EXCLAMATION_MARK: '!';
L_PAR: '(';
R_PAR: ')';
L_BRACK: '[';
R_BRACK: ']';
L_CURLY: '{';
R_CURLY: '}';
COMMA: ',';
UNDERSCORE: '_';
HAT: '^';
HYPHEN: '-';
QUESTION_MARK: '?';
ASTERISK: '*';
PLUS: '+';
VERBAR: '|';
BACKSLASH: '\\';

UNRECOGNIZED: .;
