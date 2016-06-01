
/**********************
 * @subject     : Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project     : 2
 * @fileName    : emitter.c
 * @purpose     : To emit the tokens parsed
 **********************/




#include "global.h"




/**********************
 * prototypes
 **********************/
void            emit(int t, int tval);






/**********************
 * @purpose	: to display the parse tree order
 * @parameters	: an integer value t which says the token identified
 * @returns	: return void
 **********************/
void emit(int t, int tval)
{
    switch (t) {
        case '+':
        case '-':
        case '*':
        case '/':
            printf("%c\n", t);
            break;
        case DIV:
            printf("DIV\n");
            break;
        case MOD:
            printf("MOD\n");
            break;
        case NUM:
            printf("%d\n", tval);
            break;
        case ID:
            printf("%s\n", getLexeme(tval));
            break;
        case INT:
            printf("%s\n", getLexeme(tval));
            break;
        case IF:
            printf("%s\n", getLexeme(tval));
            break;
        case WHILE:
            printf("%s\n", getLexeme(tval));
            break;
        default:
            error("token %d, tokenval %d\n", t, tval);
    }
}
