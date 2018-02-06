/*
Program Translation 4503
Assignment 1 Lexical Analyzer
Chelsea McFarland
2/16/16
Reference:
Holub, A. I. (1990). Compiler design in C. 
	Englewood Cliffs, New Jersey: Prentice-Hall. 
*/
#include "lex.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char	*text = "";
int		length = 0;
int		lineno = 0;
char 	lexeme[15];

char	*identifier;
int 	value;

const char 	*reserved_words[] = {"return", "include", "using", "namespace",
									"while", "void", "main", "break", "for",
									"if", "default", "id", "int"};
const int  tokens[] = {RETURN, INCLUDE, USING, NAMESPACE, WHILE, VOID,
						MAIN, BREAK, FOR, IF, DEFAULT, ID, INT};

lex(){
	FILE *fp;
	long int size;
	fp = fopen("input.txt", "r");
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp) + 1;
	fseek(fp, 0L, SEEK_SET);
	
	char *input_buffer = calloc(size, sizeof(char));
	fread(input_buffer, sizeof(char), size/sizeof(char), fp);
	input_buffer[size - 1] = -1;
	fclose(fp);
	char *current;				//points to current char
	current = text + length; 	//tells current where to point
	while(1){
		while(!*current){					//while current points to nothing
			//Get new lines, skipping blank space
			current = input_buffer;
			if( *current == -1){
				//if the end of the file is reached, return end of input
				*current = '\0';
				printf("end");
				return EOI;
			}
			
			while(isspace(*current))
				current++;		//continue to add until a char is reached
		}

		for( ; *current ; ++current){
			//get the next token
			text = current;
			length = 1;

			switch( *current ){
				case ';':	return SEMICOLON;
				case '=': 	return EQUALS;
				case ':': 	return COLON;
				case '(':	return LP;
				case ')':	return RP;
				case '#':	return POUND;
				case '{':	return LB;
				case '}':	return RB;
				case '<':	return LT;
				case '>':	return RT;
				case '\'': 	return APOST;
				case '*':	return AST;
				case '"': 	return QM;
				case ',':	return COMMA;
				case EOF: 	return EOI;

				case '\n':
				case '\r':
				case '\t':
				case ' ': break;

				default:
					if( !isalnum(*current))
						return 0;
					else if(isdigit(*current)){
						value = atoi(current);
						return DIGIT;
					}
					else{
						while(isalpha(*current)){
							++current;
						}
						
						int j;
						for(j = 0; j < 15; j += 1){
							lexeme[j] = '\0';
						}
						length = current - text;
						current = current - length;
						int k;
						for(k = 0; k < length; k++){
							lexeme[k] = *current;
							current += 1;
						}

						for(j = 0; j < 13; j += 1){
							if(strcmp(lexeme, reserved_words[j]) == 0){
								return tokens[j];
							}
						}
						identifier = strdup(lexeme);
						return ID;
					}
					break;
			}
		}
	}
}


