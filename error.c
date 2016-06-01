/*******************************
 * @subject     : Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project     : 2
 * @fileName    : error.c
 * @purpose     : To display error messages
 *******************************/




#include "global.h"



/*******************************
 * protypes
 *******************************/
void            error(char *);



/*********************************
 *@purpose	: to display error messages
 *@parameters	: character pointer m which has the user mentioned error message
 *@return	: returns void
 ********************************/
void
error(char *m)
{
    fprintf(stderr, "line %d: %s\n", lineno, m);
    remove(fileName);
    exit(1);
}
