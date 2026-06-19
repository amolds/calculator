# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Wno-unused-function
LEX = flex
YACC = bison

OBJS = calc.tab.o lex.yy.o symtab.o builtins.o commands.o repl.o functab.o ast.o

all: calc

calc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o calc -lfl -lm

calc.tab.c calc.tab.h: calc.y
	$(YACC) -d calc.y

lex.yy.c lex.yy.h: calc.l calc.tab.h
	$(LEX) --header-file=lex.yy.h calc.l

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

commands.o: commands.c commands.h symtab.h
	$(CC) $(CFLAGS) -c commands.c

repl.o: repl.c symtab.h
	$(CC) $(CFLAGS) -c repl.c

functab.o: functab.c functab.h paramlist.h
	$(CC) $(CFLAGS) -c functab.c

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

calc.tab.o: calc.tab.c symtab.h builtins.h commands.h functab.h paramlist.h arglist.h
	$(CC) $(CFLAGS) -c calc.tab.c

lex.yy.o: lex.yy.c calc.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f *.o calc.tab.* lex.yy.* calc
