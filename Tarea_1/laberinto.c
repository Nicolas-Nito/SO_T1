#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


//#define DEBUG


/****
 * Crea la carpeta laberinto
 ****/
void createMaze(){ 
    int res;
    char plantilla[] = "laberinto";     //string base de la ubicacion del laberinto, este string nunca se modificara
    res = mkdir(plantilla,ACCESSPERMS); //creacion de la carpeta inicial (piso 0)

    char x[3][6];
    strcpy(x[0], "/1");
    strcpy(x[1], "/2");
    strcpy(x[2], "/3");
    
    char copia[16];

    
    for(int i=0; i<3; i++){
        strcpy(copia,plantilla);
        strcat(copia,x[i]);
        res = mkdir(copia,ACCESSPERMS);
    }

    for(int i=0; i<9; i++){
        strcpy(copia,plantilla);
        res= i/3%3;
        strcat(copia,x[res]);
        res= i%3;
        strcat(copia,x[res]);
        //printf("%s \n",copia);
        res = mkdir(copia,ACCESSPERMS);
    }
    for(int i=0; i<27; i++){
        strcpy(copia,plantilla);
        res= i/9%3;
        strcat(copia,x[res]);
        res= i/3%3;
        strcat(copia,x[res]);
        res= i%3;
        strcat(copia,x[res]);
        //printf("%s \n",copia);
        res = mkdir(copia,ACCESSPERMS);
    }
    return ;
}

/****
 * Esconde un txt con la frase "phrase" de manera aleatoria en la carpeta de laberinto
 ****/
void hideTxt(const char *phrase){
    char posibleLocations[3][3];
    strcpy(posibleLocations[0], "/1");
    strcpy(posibleLocations[1], "/2");
    strcpy(posibleLocations[2], "/3");
    
    char *location = malloc (sizeof (char) * 60);
    strcat(location,"laberinto");
    strcat(location,posibleLocations[rand()%3]);
    strcat(location,posibleLocations[rand()%3]);
    strcat(location,posibleLocations[rand()%3]);
    strcat(location,"/frase.txt");
    
    FILE *file = fopen(location, "w");
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    if(size == 0){
      // FILE is empty
        fprintf(file, "%s", phrase);
        fclose(file);
        free(location);  
    }else{
        fclose(file);
        free(location);
        hideTxt(phrase); 
    }
    return;
}

/****
 * Esconde las 3 frases definidas en la carpeta laberinto
 ****/
void hideAllTxts(){
    const char* phrase1 = "1, Los hurones del ";
    const char* phrase2 = "2, profesor de sistemas operativos son ";
    const char* phrase3 = "3, muy bonitos ";
    
    hideTxt(phrase1);
    hideTxt(phrase2);
    hideTxt(phrase3);

}

int main(int argc, char *argv[]){
    createMaze();
    hideAllTxts();
    return 1;
}