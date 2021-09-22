#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    char x[3][6];
    strcpy(x[0], "/1");
    strcpy(x[1], "/2");
    strcpy(x[2], "/3");

    printf(" %d \n",rand()%50);
    printf(" %d \n",rand()%50);
    return 1;
}