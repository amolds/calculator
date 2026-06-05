CC = gcc
CFLAGS = -Wall -Wextra -O2 -Wno-unused-function
LEX = flex
YACC = bison

all: calc

calc: calc.tab.c lex.yy.c
	$(CC) $(CFLAGS) lex.yy.c calc.tab.c -o calc -lfl

calc.tab.c calc.tab.h: calc.y
	$(YACC) -d calc.y

lex.yy.c lex.yy.h: calc.l
	$(LEX) --header-file=lex.yy.h calc.l

clean:
	rm -f calc.tab.c calc.tab.h lex.yy.c lex.yy.h calc
