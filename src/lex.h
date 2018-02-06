/* 
 * File:   lex.h
 * Author: Chelsea
 *
 * Created on February 1, 2016, 9:32 PM
 */

#define LEX_H

#define RETURN		0
#define INCLUDE		1
#define USING		2
#define NAMESPACE	3
#define WHILE		4
#define VOID		5
#define MAIN		6
#define BREAK		7
#define	FOR			8
#define IF			9
#define DEFAULT		10 
#define ID			11
#define INT 		12   
#define EOI			13
#define SEMICOLON	14
#define	EQUALS		15
#define	COLON		16
#define	LP			17
#define	RP			18
#define	NUM_OR_ID	19
#define POUND		20
#define LB			21
#define RB			22
#define LT			23
#define RT			24
#define	APOST		25
#define	AST			26
#define QM			27
#define COMMA		28
#define DIGIT		29

extern char *text;		//points to the char we look at
extern int	length;		//number of chars in lexeme 
extern int 	lineno;		//line number of input
extern char *identifier;
extern int 	value;








