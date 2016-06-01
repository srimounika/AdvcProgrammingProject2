/*******************************
 * @subject     : Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project     : 2
 * @fileName    : global.h
 * @purpose     : create global varibles and define constants and include header files
 *******************************/



#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>




// macros to define token values

#define BSIZE 128

#define NONE -1
#define EOS '\0'
#define DONE 260
#define NOT_FOUND 0
#define NoOfKeywords 18

#define NUM 256
#define ID 259


#define DIV 257
#define MOD 258

#define VOID 1
#define MAIN 2
#define READ 3
#define WRITE 4
#define IF 5
#define ELSE 6
#define INT 7
#define WHILE 8
#define GREATERTHAN 9
#define LESSTHAN 10
#define NOTEQUALTO 11
#define LESSTHANEQUAL 12
#define GREATERTHANEQUAL 13
#define EQUALTO 14
#define ASSIGNMENT 15


// global variables
int             indec;
int             tokenval;
int             lineno;
char            tempbuf[BSIZE];
char           *fileName;
