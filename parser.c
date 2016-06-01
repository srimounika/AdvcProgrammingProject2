/************************************
 * @subject 	: Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project 	: 2
 * @fileName	: parser.c
 * @purpose     : To generate a parse tree by taking tokens from the lexer, for checking the syntax of the given input file
 ************************************/

#include "global.h"


/************************************
 * prototypes
 ************************************/
void            parse();
void            programStart();
void            statements();
void            statement();
void            assignment();
void            expr();
void            term();
void            factor();
void            selector();
void            iterator();
void            declarations();
int             condition();
void            operand();
void            comparator();
void            match(int);
void            write();
void            read();




int             lookahead;	// To store the current token val







/*
 ************************************
 * @purpose             : To start getting tokens from lexer and continue untill the end of the file if there are no syntax errors
 * @parameters          : No parameters passed
 * @return              : Rerurns void .
 * ************************************/
void parse()
{
    lookahead = lexan();
    programStart();		// checks the start conditions for the input file
}





/*
 ************************************
 * @purpose             : The input program need to be started in this syntactical order
 * @parameter           : No parameters passed
 * @return              : Returns void
 * ************************************/
void programStart()
{
    match(VOID);
    match(MAIN);
    match('(');
    match(')');
    match('{');
    declarations();
    statements();
    match('}');
    exitcode();
}




/*
 ************************************
 * @purpose             : any number of statements can be present untill the close curly paranthesis are matched
 * @parameter           : No parameters passed
 * @return              : Returns void
 * ************************************/
void statements()
{
    while (lookahead != '}') {
        statement();
    }
}




/*
 ************************************
 * @purpose             : To call the respective function based on the lookahead
 * @parameter           : No parameters passed
 * @return              : Returns void to the caller function
 * ************************************/
void statement()
{
    switch (lookahead) {
        case ID:
            assignment();
            break;
        case IF:
            selector();
            break;
        case WHILE:
            iterator();
            break;
        case READ:
            read();
            break;
        case WRITE:
            write();
            break;
        case DONE:
            error("Missing close curly paranthesis");
        default:
            return;
    }
}





/*************************************
 * @purpose         : To match the assignment and expression
 * @parameters      : No parameters passed
 * @return          : Returns void
 *************************************/
void assignment()
{
    char            assignId[BSIZE];
    strcpy(assignId, tempbuf);
    match(ID);
    match(ASSIGNMENT);
    expr();
    match(';');
    assigncode(assignId);
}




/*********************************
 *@purpose          : to evaluate the expression syntax
 ********************************/
void expr()
{
    int             t;
    term();
    while (1) {
        switch (lookahead) {
            case '+':
            case '-':
                t = lookahead;
                match(lookahead);
                term();
                oper(t);		// emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}





/*******************************
 *@purpose          : to match the terms in the expression
 ******************************/
void term()
{
    int             t;
    factor();
    while (1) {
        switch (lookahead) {
            case '*': case '/': case DIV: case MOD:
                t = lookahead;
                match(lookahead);
                factor();
                oper(t);		// emit(t, NONE);
                continue;
            default:
                return;
        }
    }
}




/****************************************
 *@purpose          : to match the Idendifier or a constant or start a nested expression
 ****************************************/
void factor()
{
    switch (lookahead) {
        case '(':
            match('(');
            expr();
            match(')');
            break;
        case NUM:
            constant(tokenval);
            match(NUM);
            break;
        case ID:
            identifier(tempbuf);
            match(ID);
            break;
        default:
            error("Expression syntax error");
    }
}




/*************************************
 * @purpose 		: To match the IF selector syntax
 * @parameters		: No parameters passed
 * @return          : Returns void
 *************************************/
void selector()
{
    int             t;
    match(IF);
    t = condition();
    match('{');
    statements();
    match('}');
    match(ELSE);
    t = elsecode(t);
    match('{');
    statements();
    match('}');
    elseendcode(t);
}





/*************************************
 * @purpose 		: To match the WHILE iterator syntax
 * @parameters 		: No parameters passed
 * @return  	        : Returns void
 *************************************/
void iterator()
{
    int             t,t1;
    match(WHILE);
    t = whilecode();
    t1 = condition();
    match('{');
    statements();
    match('}');
    whilereturn(t, t1);
}




/*************************************
 * @purpose 		: To check the condition syntax
 *************************************/
int condition()
{
    int             t;
    match('(');
    expr();
    t = lookahead;
    comparator();
    expr();
    match(')');
    return conditioncode(t);
}




/*************************************
 *@purpose          : to check the comparision operation inside the condition
 *************************************/
void comparator()
{
    switch (lookahead) {
        case LESSTHAN:
            match(LESS
THAN);
            break;
        case GREATERTHAN:
            match(GREATERTHAN);
            break;
        case EQUALTO:
            match(EQUALTO);
            break;
        case LESSTHANEQUAL:
            match(LESSTHANEQUAL);
            break;
        case GREATERTHANEQUAL:
            match(GREATERTHANEQUAL);
            break;
        case NOTEQUALTO:
            match(NOTEQUALTO);
            break;
    }
}





/*************************************
 * @purpose         : To match the declarations syntax
 * @parameters		: No parameters passed
 * @return          : Returns void
 *************************************/
void declarations()
{
    static int      idcount = 0;
    while (lookahead == INT) {
        indec = 1;
        match(INT);
        match(ID);
        ++idcount;
        while (lookahead == ',') {
            match(',');
            match(ID);
            ++idcount;
        }
        indec = 0;
        match(';');
    }
    declarecode(idcount);
}


/*******************************
 * @purpose         : read the user input
 * *****************************/
void read()
{
    match(READ);
    match('(');
    match(ID);
    match(')');
    match(';');
    readcode(tempbuf);
}



/********************************
 * @purpose         : write the result variable value to the moniter screen
 ********************************/
void write()
{
    match(WRITE);
    match('(');
    match(ID);
    match(')');
    match(';');
    writecode(tempbuf);
}



/*************************************
 *@purpose          : to compare the token with the expected token in the grammar and move the lookahead to next token
 *@parameters		: takes an interger value of the current token type
 *@return           : Returns void
 ************************************/
void match(int t)
{
    if (lookahead == t) {
        lookahead = lexan();
    } else if (t == ')') {
        error("Missing close Paranthesis");
    } else if (t == '(') {
        error("Missing open paranthesis");
    } else if (t == VOID) {
        error("Expecting Void");
    } else if (t == MAIN) {
        error("Expecting MAIN");
    } else if (t == ';') {
        error("Expecting delimiter ;");
    } else
        error("syntax error");
}
