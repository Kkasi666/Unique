# 

G(S):
1. factor -> PTHL expr PTHR | NUM
2. term -> factor ((ADD|SUB) factor)*
3. expr -> term ((MUL|DIV) term)*
4. statExpr -> expr
