# grammar
```
PTHL -> '('
PTHR -> ')'
ADD -> '+'
SUB -> '-'
MUL -> '*'
DIV -> '/'
ASS -> '='
NUM -> ('-')[0-9]+
IDN -> ([a-z] | [A-Z])*
CMT -> ("\\")(!('\n') -> skip
SPA -> ' ' | '\t' | '\n'  -> skip

factor -> PTHL expr PTHR | NUM | IDN
term -> factor ((ADD|SUB) factor)*
expr -> term ((MUL|DIV) term)*
assign -> IDN ASS expr
statExpr -> assign+
```