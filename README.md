# Tiny REPL Calculator

A lightweight expression‑language interpreter built using **Flex** and **Bison**.  
This project demonstrates how a scanner and parser work together to form a real, interactive REPL capable of evaluating expressions, storing variables, and responding to custom commands.

It’s intentionally small, readable, and hackable — perfect for learning or extending into your own mini‑language.

---

## Features

- **Real REPL** — evaluates one line at a time  
- **Multi‑character variables** (`foo`, `bar`, `total_sum`)  
- **Real symbol table** with dynamic storage  
- **Arithmetic with correct precedence**  
- **Unary minus** (`-x`)  
- **Parentheses** for grouping  
- **Custom REPL commands**, including:  
  - `:symbols` — list all variables and their values  
  - `:store` <file> — save all variables to a file
  - `:load` <file> — loads all variables from a file
  - `:quit` — exit the interpreter  

---

## Building & Running

Run the following commands in your project directory:

```
rm -f calc.tab.* lex.yy.* calc
bison -d calc.y
flex --header-file=lex.yy.h calc.l
gcc lex.yy.c calc.tab.c -o calc -lfl
```

Then start the REPL:

```
./calc
```

You’ll see:

```
>>>
```

---

## Usage Examples

### Basic arithmetic

```
>>> 1 + 2 * 3
=7
```

### Variables

```
>>> foo = 10
=10
>>> bar = foo * 3
=30
>>> foo + bar
=40
```

### Commands

```
>>> :symbols
Symbols:
  foo = 10
  bar = 30
```

```
>>> :quit
```

---

## Project Structure

- `calc.l` — Flex scanner (tokenizes input)  
- `calc.y` — Bison parser (evaluates expressions, manages REPL)  
- Symbol table — simple dynamic array of `(name, value)` pairs  

---

## Extending the Interpreter

This project is designed to be extended.  
Some natural next steps:ac

- Add `:help` and `:reset` commands  
- Add string variables  
- Add functions (`square(x) = x * x`)  
- Add multi‑line input  
- Add error recovery  

---

## Assemble source into .txt

cat Makefile *.c *.h *.y *.l > code.txt

---
