CC = gcc
CFLAGS = -Wall -Wextra -O2 -Wno-unused-function
LEX = flex
YACC = bison

OBJS = calc.tab.o lex.yy.o symtab.o builtins.o commands.o repl.o

all: calc

calc: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o calc -lfl -lm

calc.tab.c calc.tab.h: calc.y
	$(YACC) -d calc.y

lex.yy.c lex.yy.h: calc.l
	$(LEX) --header-file=lex.yy.h calc.l

symtab.o: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

builtins.o: builtins.c builtins.h
	$(CC) $(CFLAGS) -c builtins.c

commands.o: commands.c commands.h symtab.h
	$(CC) $(CFLAGS) -c commands.c

repl.o: repl.c symtab.h
	$(CC) $(CFLAGS) -c repl.c

calc.tab.o: calc.tab.c symtab.h builtins.h commands.h
	$(CC) $(CFLAGS) -c calc.tab.c

lex.yy.o: lex.yy.c calc.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -f *.o calc.tab.* lex.yy.* calc
