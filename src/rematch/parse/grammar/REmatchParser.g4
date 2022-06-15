// https://www2.cs.sfu.ca/~cameron/Teaching/384/99-3/regexp-plg.html
// https://stackoverflow.com/questions/399078/what-special-characters-must-be-escaped-in-regular-expressions
// https://www.ibm.com/docs/en/rational-clearquest/9.0.1?topic=tags-meta-characters-in-regular-expressions

parser grammar REmatchParser;

options {
  tokenVocab = REmatchLexer;
}

root: altern EOF;

altern: concat ('|' concat)*;

concat: iter+;

iter: group rep?;

rep: '?' | '*' | '+' | span;

span: '{' (uint? ',' uint?) '}';

uint: DIGIT+;

group: parenthesis | assign | atom;

parenthesis: '(' altern ')';

assign: VARNAME '{' altern '}';

atom: set | metaChar | character;

set: '[' '^'? setItems ']';

setItems: setItem+;

setItem: setChar | range;

setChar:
  '\\' (HAT | HYPHEN | R_BRACK)
  | ~(HAT | HYPHEN | R_BRACK);

range: setChar '-' setChar;

character:
  ESCAPE_CHARS
  | '\\' (
    EXCLAMATION_MARK
    | DOT
    | ASTERISK
    | PLUS
    | QUESTION_MARK
    | BACKSLASH
    | VERBAR
    | L_PAR
    | R_PAR
    | L_BRACK
    | R_BRACK
    | L_CURLY
    | R_CURLY
  )
  | ~(
    EXCLAMATION_MARK
    | DOT
    | ASTERISK
    | PLUS
    | QUESTION_MARK
    | BACKSLASH
    | VERBAR
    | L_PAR
    | R_PAR
    | L_BRACK
    | R_BRACK
    | L_CURLY
    | R_CURLY
  );

metaChar:
  DOT
  | ANY_DIGIT
  | NOT_ANY_DIGIT
  | ANY_WHITESPACE
  | NOT_ANY_WHITESPACE
  | ANY_ALPHA
  | NOT_ANY_ALPHA;