/**************************
 * @subject     : Advanced Programming Languages
 * @auther      : Sri Mounika Puvvada
 * @project     : 2
 * @fileName    : main.c
 * @purpose     : To call the main method and then start parsing
 ***************************/


#include <stdio.h>
#include "global.h"





/***************************
 * @purpose     : Main is the starting method for a c language program
 * @parameters	: An integer@argc which remembers the number of arguments count
 *                An character@argv[] pointer which is used to store the strings passed
 * @return      : Returns void
 ***************************/
void main(int argc, char *argv[])
{
    if (argc != 2) {                               // if the no arguments passed
        printf("wrong command: No file Name");
        exit(-1);
    }
    init(argv[1]);                                 // calls to open the file
    fileName = strcat(argv[1], ".obj");            //set result file name 
    parse();                                       // calls to start parsing
    printf("Legal File\n");
    exit(0);
}
