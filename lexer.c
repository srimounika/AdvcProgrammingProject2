/**********************
 * @subject     : Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project     : 2
 * @fileName    : lexer.c
 * @purpose     : To identify the tokens from the input file
 **********************/




#include "global.h"
#include<stdlib.h>




/***********************
 *prototypes
 ***********************/
int             openFile(char *);
int             lexan();



FILE           *fp;

/************************
 * @purpose         : to open the given input file
 * @parameters      : char pointer pointing to the file name string
 * @return          : An integer which says the file opened or not
 ************************/
int openFile(char *name)
{
    fp = fopen(name, "r");
    if (fp == NULL) {
        printf("file did not open\n");
        exit(-1);
    }
}





//declarations
char            lexbuf[BSIZE];
int             lineno = 1;
int             tokenval = NONE;





/************************
 * @purpose         : to generate tokens
 * @parameters      : No parameters
 * @return          : An integer which is the value of token type
 ************************/
int lexan()
{
    int             t;
    while (1) {
        t = getc(fp);
        if (t == ' ' || t == '\t');
        else if (t == '\n')
            lineno++;
        else if (isdigit(t)) {
            ungetc(t, fp);
            fscanf(fp, "%d", &tokenval);
            return NUM;
        } else if (isalpha(t)) {
            int             p,
            b = 0;
            while (isalnum(t) || t == '_') {
                if (lexbuf[b - 1] == '_' && t == '_') {
                    error("Indentifier has consecutive underscores");
                }
                lexbuf[b] = t;
                t = getc(fp);
                b++;
                if (b >= BSIZE)
                    error("compiler error");
            }
            if (lexbuf[b - 1] == '_') {
                error("Identifier ending with underscore");
            }
            lexbuf[b] = EOS;
            if (t != EOF)
                ungetc(t, fp);
            p = lookup(lexbuf);
            if (indec) {
                if (p == NOT_FOUND)
                    p = insert(lexbuf, ID);
                else
                    error("Re-declaration of an identifier");
            } else {
                if (p == NOT_FOUND)
                    error("ID not declared");
                else if (getTokenType(p) == ID) {
                    strcpy(tempbuf, lexbuf);
                }
            }
            tokenval = p;
            return getTokenType(p);
        } else if (t == '/' && ((t = getc(fp)) == '*')) {
            while ((t = getc(fp)) != '*') {
                ;
            }
            if ((t = getc(fp)) != '/') {
                error("Improper comment termination");
            }
        } else if (t == '>') {
            if ((t = getc(fp)) == '=')
                return GREATERTHANEQUAL;
            else {
                ungetc(t, fp);
                return GREATERTHAN;
            }
        } else if (t == '<') {
            if ((t = getc(fp)) == '=')
                return LESSTHANEQUAL;
            else if ((t == '>')) {
                return NOTEQUALTO;
            } else {
                ungetc(t, fp);
                return LESSTHAN;
            }
        } else if (t == '=') {
            if ((t = getc(fp)) == '=') {
                return EQUALTO;
            } else {
                ungetc(t, fp);
                return ASSIGNMENT;
            }
        } else if (t == EOF)
            return DONE;
        else {
            tokenval = NONE;
            return t;
        }
    }
}
