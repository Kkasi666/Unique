# Token
```
ADD -> '+'
SUB -> '-'
MUL -> '*'
DIV -> '/'
ASS -> '='
SQM -> '\''
DQM -> '\"'
NUM -> [0-9]+
IDN -> ([a-z] | [A-Z])*
CMT -> ("//")(!('\n')) -> skip
SPA -> ' ' | '\t' | '\n'  -> skip
PTHL -> '('
PTHR -> ')'
BRKL -> '['
BRKR -> ']'
BRCL -> '{'
BRCR -> '}'
KEYWORD ->  "print" |
			"fun" | "main" | "ret"
```
# grammar

char -> SQM ALL(only a char) SQM  
string -> DQM ALL DQM  
__negative -> SUB NUM__  
__factor -> (PTHL expr PTHR) | NUM | IDN | negative__  
__term -> factor ((ADD|SUB) factor)*__  
__expr -> term ((MUL|DIV) term)*__  
__assign -> IDN ASS expr__  
print -> KEYWORD<0> PTHL (IDN | string | char) PTHR  
program -> KEYWORD<1> KEYWORD<2> PTHL PTHR BRCL (assign | print)+ KEYWORD<3> NUM BRCR  

__tip:__ The __BOLD__ grammar is completed.