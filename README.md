rm -f calc.tab.* lex.yy.* calc
bison -d calc.y
flex --header-file=lex.yy.h calc.l
gcc lex.yy.c calc.tab.c -o calc -lfl
