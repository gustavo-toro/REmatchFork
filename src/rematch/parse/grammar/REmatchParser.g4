parser grammar REmatchParser;

options {
  tokenVocab = REmatchLexer;
}

altern: concat ('|' concat)*;

concat: (iter)+;

iter: group rep;

rep: '?' | '*' | '+' | span;

span:
  '{' UINT '}'
  | '{' ',' UINT '}'
  | '{' UINT ',' '}'
  | '{' UINT ',' UINT '}';

group: parenthesis | assign | atom;

parenthesis: '(' altern ')';

assign: '!' VARNAME '{' altern '}';

atom: charset | SPECIAL | symb;

charset: '[' '^'? (charclass_symb ('-' charclass_symb)?)+ ']';

symb: UNESC_CHAR | '\\' (SYMBS | '-') | ~SYMBS;

charclass_symb:
  UNESC_CHAR
  | (SYMBS | '^')
  | ~('\\' | '[' | ']');