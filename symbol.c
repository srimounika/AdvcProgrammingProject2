/************************************
 * @subject 	: Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project 	: 2
 * @fileName	: symbol.c
 * @purpose     : To match the keywords and insert new token identified
 ************************************/

#include "global.h"

#define STRMAX 999
#define SYMMAX 999




/************************************
 * prototypes
 ************************************/
char           *getLexeme(int);
int             lookup(char[]);
void            init(char *);
int             insert(char[], int);
char           *traverse();



/************************************
 * @purpose          : to create a entry holding a token and a lexical pointer
 ************************************/
struct entry {
    char           *lexptr;
    int             token;
};


//declarations
struct entry    symtable[SYMMAX];
char            lexemes[STRMAX];
int             lastchar = -1;
int             lastentry = 0;




/*************************************
 * @purpose          : To create the keyword entries
 *************************************/
struct entry    keywords[] = {
    "void", VOID,
    "main", MAIN,
    "READ", READ,
    "WRITE", WRITE,
    "if", IF,
    "else", ELSE,
    "int", INT,
    "while", WHILE,
    ">", GREATERTHAN,
    "<", LESSTHAN,
    "<>", NOTEQUALTO,
    "<=", LESSTHANEQUAL,
    ">=", GREATERTHANEQUAL,
    "==", EQUALTO,
    "=", ASSIGNMENT,
    "div", DIV,
    "mod", MOD,
    0, 0
};


/*
 ************************************
 * @purpose             : To initialise the symbol table with the keywords and to open the file inputed
 * @parameters          : a character pointer @fname holds the filename of the input file
 * @return              : Rerurns void .
 * ************************************/
void init(char *fname)
{
    struct entry   *p;
    for (p = keywords; p->token; p++)
        insert(p->lexptr, p->token);
    openFile(fname);
}



/************************************
 * @purpose     : To check against the symbol table for the current token
 * @parameters  : a string @s holds the token
 * @return      : an integer @p holds the token value
 ************************************/
int lookup(char s[])
{
    int             p;
    for (p = lastentry; p > 0; p--)
        if (!strcmp(symtable[p].lexptr, s))
            return p;
    
    return NOT_FOUND;
}




/************************************
 * @purpose     : To insert a new token , into the symbol table
 * @parameters  : a string @s holds the token
 *                an integer @tok token which holds the token value
 * @returns     : an integer which is the token id in the symbol table
 ************************************/
int insert(char s[], int tok)
{
    int             len;
    len = strlen(s);
    if (lastentry + 1 >= SYMMAX)
        error("symbol table full");
    if (lastchar + len + 1 >= STRMAX)
        error("lexeme array full");
    lastentry = lastentry + 1;
    symtable[lastentry].token = tok;
    symtable[lastentry].lexptr = &lexemes[lastchar + 1];
    lastchar = lastchar + len + 1;
    strcpy(symtable[lastentry].lexptr, s);
    return lastentry;
}





/************************************
 * @purpose     : to get the lexical pointer for a given token position in the symbol table
 * @parameters  : an integer @pos which holds the position of the token
 * @returns     : a string pointer which gives the lexeme pointer
 ************************************/
char *getLexeme(int pos)
{
    return symtable[pos].lexptr;
}





/************************************
 * @purpose     : to send the token value for the given position of it in symbol table
 * @parameters  : an integer @pos which holds the position of the token in the symbol table
 * @return      : an integer which holds the token value in the symbol table
 ************************************/
int getTokenType(int pos)
{
    return symtable[pos].token;
}
