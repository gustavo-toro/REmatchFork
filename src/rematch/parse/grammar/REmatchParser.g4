parser grammar REmatchParser;

options {
  tokenVocab = REmatchLexer;
}

root: alternation EOF;

alternation: expr ('|' expr)*;

expr: element+;

element: group quantifier?;

group: parentheses | assignation | atom;

parentheses: '(' alternation ')';

assignation: '!' VARNAME '{' alternation '}';

atom: characterClass | sharedAtom | literal;

characterClass: '[' '^'? ccAtom+ ']';
ccAtom: ccRange | sharedAtom | literal;
ccRange: ccLiteral '-' ccLiteral;
ccLiteral: ccEscapes | ccOther;
ccEscapes: '\\' ('^' | '-' | ']' | '\\');
ccOther: ~('^' | '-' | ']' | '\\');

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

sharedAtom:
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