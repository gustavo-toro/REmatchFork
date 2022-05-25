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

span: '{' (UINT | ',' UINT | ',' UINT | UINT ',' UINT) '}';

group: parenthesis | assign | atom;

parenthesis: '(' altern ')';

assign: VARNAME '{' altern '}';

atom: set | character;

set: '[' '^'? set_items ']';

set_items: set_item set_items?;

set_item: set_char | range;

set_char:
  '\\' (HAT | HYPHEN | R_BRACK)
  | ~(HAT | HYPHEN | R_BRACK);

range: set_char '-' set_char;

character:
  ESCAPE_CHARS
  | '\\' (
    EXCLAMATION_MARK
    | DOT
    | HAT
    | ASTERISK
    | PLUS
    | HYPHEN
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
  | '.'
  | ~(
    EXCLAMATION_MARK
    | DOT
    | HAT
    | ASTERISK
    | PLUS
    | HYPHEN
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