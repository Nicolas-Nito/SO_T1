#include "buscador.h"
#include "laberinto.h"

int main(int argc, char *argv[]){
    createMaze();
    hideAllTxts();
    char phrases[3][BUFFER_SIZE];
    searchAllPhrases(phrases);
    sortAndPrint(phrases);

    return 1;
}