parser grammar REmatchParser;

options {
  tokenVocab = REmatchLexer;
}

root: alternation EOF;

alternation: expr ('|' expr)*;

expr: element+;

element: group quantifier?;

group: parenthesis | assignation | atom;

parenthesis: '(' alternation ')';

assignation: '!' variable '{' alternation '}';

variable: ALPHANUMERIC+;

atom: character_class | shared_atom | literal;

character_class: '[' '^'? cc_atom+ ']';
cc_atom: cc_range | shared_atom | literal;
cc_range: cc_literal '-' cc_literal;
cc_literal: cc_escapes | cc_other;
cc_escapes: '\\' ('^' | '-' | ']' | '\\');
cc_other: ~('^' | '-' | ']' | '\\');

literal: escapes | other;
escapes:
  '\\' (
    '['
    | ']'
    | '('
    | ')'
    | '{'
    | '}'
    | '*'
    | '+'
    | '?'
    | '|'
    | '.'
    | '\\'
  );
other:
  ~(
    '['
    | ']'
    | '('
    | ')'
    | '{'
    | '}'
    | '*'
    | '+'
    | '?'
    | '|'
    | '.'
    | '\\'
  );

shared_atom:
  DECIMAL_DIGIT
  | NOT_DECIMAL_DIGIT
  | HORIZONTAL_WHITESPACE
  | NOT_HORIZONTAL_WHITESPACE
  | NEW_LINE
  | NOT_NEW_LINE
  | WHITESPACE
  | NOT_WHITESPACE
  | VERTICAL_WHITESPACE
  | NOT_VERTICAL_WHITESPACE
  | WORD_CHAR
  | NOT_WORD_CHAR;

quantifier: '?' | '+' | '*' | '{' quantity '}';
quantity: quantExact | quantRange | quantMin | quantMax;
quantExact: number;
quantRange: number ',' number;
quantMin: number ',';
quantMax: ',' number;

number: DIGIT+;