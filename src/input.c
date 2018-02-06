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

//rows of the parse table
int row0[] = {1, VOID, 3};
int row1[] = {1, LB, 4};
int row2[] = {1, EOF, -100};
int row3[] = {1, MAIN, 5};
int row4[] = {1, INT, 6};
int row5[] = {1, LP, 9};
int row6[] = {1, ID, -7};
int row7[] = {1, ID, 10};
int row8[] = {1, ID, 10};
int row9[] = {1, RP, 14};
int row10[] = {2, EQUALS, -8, SEMICOLON, -8};
int row11[] = {1, SEMICOLON, 15};
int row12[] = {1, INT, 16};
int row13[] = {1, EQUALS, 18};
int row14[] = {1, LB, -2};
int row15[] = {1, ID, -3};
int row16[] = {1, ID, 10};
int row17[] = {1, WHILE, 20};
int row18[] = {1, DIGIT, 22};
int row19[] = {1, EQUALS, 23};
int row20[] = {1, LP, 24};
int row21[] = {1, RB, 25};
int row22[] = {1, SEMICOLON, 26};
int row23[] = {1, DIGIT, 27};
int row24[] = {1, DIGIT, 28};
int row25[] = {1, EOI, -1};
int row26[] = {1, INT, -4};
int row27[] = {1, SEMICOLON, 29};
int row28[] = {1, RP, 30};
int row29[] = {1, WHILE, -5};
int row30[] = {1, LB, 31};
int row31[] = {1, RB, 32};
int row32[] = {1, RB, -6};

//array which points to the rows
//indexed by row number
int *action[33] = {
	row0, row1, row2, row3, row4, row5, row6, row7, row8, row9, row10,
	row11, row12, row13, row14, row15, row16, row17, row18, row19, row20,
	row21, row22, row23, row24, row25, row26, row27, row28, row29, row30, 
	row31, row32
};

//goto portion of the parse table
int goto0[] = {2, 2, 1, 0, 2};
int goto4[] = {2, 7, 7, 3, 8};
int goto7[] = {1, 8, 11};
int goto8[] = {2, 4, 12, 8, 13};
int goto12[] = {1, 5, 17};
int goto16[] = {1, 8, 19};
int goto17[] = {1, 6, 21};

//array which points to the gotos
//indexed by row number
int *goto_table[33] = {
	goto0, NULL, NULL, NULL, goto4, NULL, NULL, goto7, goto8, NULL, NULL,
	NULL, goto12, NULL, NULL, NULL, goto16, goto17, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

//array which assigns numerical values to the non-terminals
//indexed by production number
int lhs[9] = {
	/*0*/	0,
	/*1*/	1,
	/*3*/ 	2,
	/*4*/	3,
	/*5*/	4,
	/*6*/	5,
	/*7*/	6,
	/*8*/	7,
	/*9*/	8
};

//contains the number of symbols on the right side of each production
//indexed by production number
int reduce[9] = {
	/*0*/	2,
	/*1*/	7,
	/*3*/	4,
	/*4*/	3,
	/*5*/	4,
	/*6*/	5,
	/*7*/	6,
	/*8*/	1,
	/*9*/	1
};

//function for moving through the parse table
int next(int **table, int cur_state, int symbol){
	int *p = table[cur_state];
	int i;

	if(p)
		for(i = (int) *p++; --i >= 0; p += 2){
			//printf("%i\n", p[1]);
			if(symbol == p[0]){
				return p[1];
			}
		}
	return 1000;
}
