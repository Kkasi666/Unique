# News (重要通知)
## Negative Numbers are Temporarily Cancelled!! (目前暂时取消负数！！！)
## The Following Grammar is NOT Complete!!!(以下语法并没有全部完成！！！)

# grammar
```
PTHL -> '('
PTHR -> ')'
ADD -> '+'
SUB -> '-'
MUL -> '*'
DIV -> '/'
ASS -> '='
CHAR -> '\'' [ascii] '\''
STRING -> '\"' [ascii]+ '\"'
NUM -> [0-9]+
WORD -> ([a-z] | [A-Z])*
CMT -> ("//")(!('\n') -> skip
SPA -> ' ' | '\t' | '\n'  -> skip
BRKL -> '['
BRKR -> ']'
BRCL -> '{'
BRCR -> '}'
KEYWORD -> "var" | "byte" | "bool" | "char" | "int" | "float" | "fun" | "main" |"print" | "ret"

factor -> (PTHL expr PTHR) | NUM | IDN
term -> factor ((ADD|SUB) factor)*
expr -> term ((MUL|DIV) term)*
assign -> KEYWORD<0> IDN (ASS expr) KEYWORD<1-5>
print -> KEYWORD<8> PTHL (IDN | STRING) PTHR
program -> KEYWORD<6> KEYWORD<7> PTHL PTHR KEYWORD<5> BRCL (assign | print)+ KEYWORD<9> NUM BRCR
```
