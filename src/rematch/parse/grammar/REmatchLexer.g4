lexer grammar REmatchLexer;

// Composed tokens
VARNAME: EXCLAMATION_MARK [A-Za-z0-9\-_]+;
ESCAPE_CHARS: BACKSLASH [aAbBdDfnrsStvwWzZ];
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
SPACE: ' ';
UNDERSCORE: '_';
HAT: '^';
HYPHEN: '-';
QUESTION_MARK: '?';
ASTERISK: '*';
PLUS: '+';
VERBAR: '|';
BACKSLASH: '\\';

UNRECOGNIZED: .;

fragment PAR: L_PAR | R_PAR;
fragment BRACK: L_BRACK | R_BRACK;
fragment CURLY: L_CURLY | R_CURLY;