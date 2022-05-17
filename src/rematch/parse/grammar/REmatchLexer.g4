lexer grammar REmatchLexer;

// Composed tokens
UINT: [1-9] [0-9]*;
VARNAME: [A-Za-z0-9\-_]+;
SPECIAL: '.' | '\\' [dDwWsS];
UNESC_CHAR: '\\' ([afnrtv] | '\\');
SYMBS: [.+*?|!] | PAR | BRACK | CURLY;

// Single tokens
L_PAR: '(';
R_PAR: ')';
L_BRACK: '[';
R_BRACK: ']';
L_CURLY: '{';
R_CURLY: '}';

NEG: '^';
ALT: '|';
OPT: '?';
EXC: '!';
ESC: '\\';
STAR: '*';
PLUS: '+';
COMMA: ',';
HYPHEN: '-';
UNDERSCORE: '_';

UNRECOGNIZED: .;

// Helpers
fragment PAR: L_PAR | R_PAR;
fragment BRACK: L_BRACK | R_BRACK;
fragment CURLY: L_CURLY | R_CURLY;