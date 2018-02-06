/*
Program Translation 4503
Assignment 2 Parser
Chelsea McFarland
3/3/16
Reference:
Holub, A. I. (1990). Compiler design in C. 
	Englewood Cliffs, New Jersey: Prentice-Hall. 

The program is compiled along with the lex.c, hash.c, 
and input.c files. As of right now, it has a very limited 
functionality. The parsing function works well, but the 
parse table needs to be refined to work properly. Addtionally,
this portion of the program does not do anything aside from 
add symbols to the symbol table.
*/
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "input.h"
#include "hash.h"
#include "parser.h"

int symbol_stack[100];
int reduction_stack[100];
int size = 0;
char *identifier;
int value;
int type;
hashtable_t symbol;

int main(){
	symbol = table_create();

	int lookahead;
	
	push(symbol_stack, 0);
	lookahead = lex();

	while(1){
		int do_this;
	
		do_this = next(action, peek(symbol_stack), lookahead);

		if(do_this == 1000){
			printf("error\n");
			break;
		}

		else if(do_this > 0){
			lookahead = lex();

			push(symbol_stack, do_this);
		}

		else{
			generate(-do_this);
			if(-do_this == 1){
				break;
			}
			if(do_this == -100){
				break;
			}
			else{
				int production_number;
				int next_state;
				int rhs_length;

				production_number = -do_this;
				rhs_length = reduce[production_number];

				while(--rhs_length >= 0)
					pop(symbol_stack);

				next_state = next(goto_table, peek(symbol_stack), 
					lhs[production_number]);

				push(symbol_stack, next_state);
			}
		}
	}

	return 0;
}

//function used to determine which action to do based on the 
//production number
void generate(int reduction){
	//Program -> MainFunction LB VarDeclaration 
	//AssignStmt StateInitialization WhileStmt RB 
	if(reduction == 1){
	}
	
	//MainFunction -> VOID MAIN LP RP
	else if(reduction == 2){
	}

	//VarDeclaration -> Type Id SEMICOLON
	else if(reduction == 3){
		if(search_hash(symbol, identifier) == 0)
			insert(symbol, identifier, -1000, type);
		else
			printf("Variable already declared\n");
	}

	//AssignStmt -> Id EQUALS DIGIT SEMICOLON
	else if(reduction == 4){
		if(search_hash(symbol, identifier) == -1000){
			add_value(symbol, identifier, value);
		}
		else
			printf("Variable uninitialized\n");
	}

	//StateInitialization -> INT Id EQUALS DIGIT SEMICOLON
	else if(reduction == 5){
		if(search_hash(symbol, identifier) == 0)
			insert(symbol, identifier, value, type);
		else
			printf("Variable already initialized\n");
	}

	//WhileStmt -> WHILE LP DIGIT RP LB RB
	else if(reduction == 6){
		print_hash(symbol, identifier);
	}
	else if(reduction == 7){
		type = INT;
	}
	else if(reduction == 8){
	}
}

//stack functions
int peek(int stack[]){
	if(size == 0){
		fprintf(stderr, "Error: stack empty\n");
		return -1;
	}
	return stack[size-1];
}

void push(int stack[], int d){
	if(size < 100)
		stack[size++] = d;
	else
		fprintf(stderr, "Error: stack full\n");
}

int pop(int stack[]){
	if(size == 0)
		fprintf(stderr, "Error: stack empty\n");
	else
		size--;
}
