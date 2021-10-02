#include "buscador.h"

int main(int argc, char *argv[]){
    char phrases[3][BUFFER_SIZE];
    searchAllPhrases(phrases);
    sortAndPrint(phrases);

    return 1;
}