/************************************
 * @subject 	: Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project 	: 2
 * @fileName	: codegen.c
 * @purpose     : To generate the intermediate code i.e object file for a parsed input file
 ************************************/


#include"global.h"



// variable declarations
int             reg = 0;
int             label = 0;
FILE           *fptr;


/************************************
 * prototypes
 ************************************/
void            constant(int);
void            identifier(char[]);
void            oper(int);
void            assigncode(char[]);
int             conditioncode(int);
int             newLabel();
void            declarecode(int);
void            readcode(char[]);
void            writecode(char[]);
void            exitcode();
void            whilereturn(int, int);
int             whilecode();
int             elsecode(int);
void            elseendcode(int);







/************************************
 * @purpose     : To generate code for declarations statements
 * @parameters  : an integer @count which holds the number of identifiers declared
 * @returns     : Returns void
 ************************************/
void declarecode(int count)
{
    fptr = fopen(fileName, "w");
    int             t = NoOfKeywords;
    fprintf(fptr, ".data\n");
    while (count) {
        fprintf(fptr, ".word %s\n", getLexeme(t++));
        count--;
    }
    fprintf(fptr, ".text\nmain:\n");
    fclose(fptr);
}





/************************************
 * @purpose     : To generate the code for read operations
 * @parameters  : an character array @id holding the memory address to load the value into register
 * @returns     : Returns void
 ************************************/
void readcode(char id[])
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\ta1 := &input\n\tcall readint\n");
    fprintf(fptr, "\t%s := rv\n", id);
    fclose(fptr);
}




/************************************
 * @purpose     : To generate the code for the write operation
 * @parameters  : an charater array @id which has the value of to which memory location the value must be written form register
 * @returns     : Returns void
 ************************************/
void writecode(char id[])
{
    fptr = fopen(fileName, "a");
    fprintf(fptr,
            "\ta2 :=%s\n\tcall writeint\n\ta1 := &output\n\tcall writeln\n",
            id);
    fclose(fptr);
}



/************************************
 * @purpose     : To load the constant value to the registers
 * @parameters  : an integer @value is the value present in the memory
 * @returns     : Returns void
 ************************************/
void constant(int value)
{
    fptr = fopen(fileName, "a");
    // sprintf(tmp,"%d",value);
    fprintf(fptr, "\tR%d := %d\n", reg++, value);
    fclose(fptr);
}





/************************************
 * @purpose     : To load the value form the memory address to the registers
 * @parameters  : a character array @id which is used to bring the value for the memory address to a register
 * @returns     : Returns void
 ************************************/
void identifier(char id[])
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\tR%d := %s\n", reg++, id);
    fclose(fptr);
}




/************************************
 * @purpose     : To generate code for the arithmetic operations
 * @parameters  : an integer @t which stores the operaiton needs to be performed
 * @returns     : Returns void
 ************************************/
void oper(int t)
{
    fptr = fopen(fileName, "a");
    reg--;
    fprintf(fptr, "\tR%d := R%d %c R%d\n", reg - 1, reg - 1, t, reg);
    fclose(fptr);
}




/************************************
 * @purpose     : To assign the result obtained by the registers to be stored into the memory
 * @parameters  : a character @id which has the memory address to which the register value is stored
 * @returns     : Returns void
 ************************************/
void assigncode(char id[])
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\t%s :=R%d\n", id, --reg);
    fclose(fptr);
}




/************************************
 * @purpose     : Generates the code for the condition having the comparision operator
 * @parameters  : an integer @t which gives the comparision operation needed to perform
 * @returns     : Returns an integer which has the label number to jump if the condition is false
 ************************************/
int conditioncode(int t)
{
    fptr = fopen(fileName, "a");
    int             tem;
    tem = newLabel();
    reg--;
    fprintf(fptr, "\tR%d :=R%d %s R%d\n", reg - 1, reg - 1, getLexeme(t),reg);
    fprintf(fptr, "\tIF R%d goto L%d\n", --reg, tem);
    fclose(fptr);
    return tem;
}




/************************************
 * @purpose     : To generate a new label
 * @returns     : Returns an integer which gives the new label number
 ************************************/
int newLabel()
{
    return ++label;
}




/************************************
 * @purpose     : To generate code for the while block
 * @returns     : Returns an integer which holds a label number to which the control has t return after the while block
 ************************************/
int whilecode()
{
    fptr = fopen(fileName, "a");
    int             t;
    t = newLabel();
    fprintf(fptr, "L%d:\t\t---while block\n", t);
    fclose(fptr);
    return t;
}





/************************************
 * @purpose     : To generate the code for end of the while
 * @parameters  : @t which stores the label number of while starting and @next is the while condition fail label
 * @returns     : Returns void
 ************************************/
void whilereturn(int t, int next)
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\tgoto L%d\t------while end\nL%d:\n", t, next);
    fclose(fptr);
}




/************************************
 * @purpose     : To generate code for Else block
 * @parameters  : an integer @t which remembers the lab
 * @returns     : Returns an integer which has the label number of to which the end of if must jump to
 ************************************/
int elsecode(int t)
{
    int             tmp;
    tmp = newLabel();
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\tgoto L%d\t----if block ends\n", tmp);
    fprintf(fptr, "L%d:\t\t----else block\n", t);
    fclose(fptr);
    return tmp;
}





/************************************
 * @purpose     : To generate code for the end of the else block
 * @parameters  : an integer @t which remembers the label to which If block wants to jump
 * @returns     : Returns void
 ************************************/
void elseendcode(int t)
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "L%d:\n", t);
    fclose(fptr);
}




/************************************
 * @purpose     : To generate code for the exit of the void main
 ************************************/
void exitcode()
{
    fptr = fopen(fileName, "a");
    fprintf(fptr, "\tgoto exit\n");
    fclose(fptr);
}
