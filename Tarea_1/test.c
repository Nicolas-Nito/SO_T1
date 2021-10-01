#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>


//#define DEBUG

// Posición de las rutas en el string de la busqueda de archivos (1,2,3)
#define UPPER_ROUTE 10
#define MIDDLE_ROUTE 12
#define LOWER_ROUTE 14

// Tamaño máximo de las frases
#define BUFFER_SIZE 256

#define true  1
#define false 0

/*crear_laberinto():
    funcion que crea los 3 pisos de carpetas*/
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

void hideAllTxts(){
    const char* phrase1 = "1, Los hurones del ";
    const char* phrase2 = "2, profesor de sistemas operativos son ";
    const char* phrase3 = "3, muy bonitos ";
    
    hideTxt(phrase1);
    hideTxt(phrase2);
    hideTxt(phrase3);

}

void searchAllPhrases(char phrases[][BUFFER_SIZE]){
    char location[] = "laberinto/0/0/0/frase.txt";
    int nFilesFound = 0;
    for(int upper = 1 ; upper < 4 ; upper++){
        location[UPPER_ROUTE] = (char)upper + '0';
        for(int middle = 1 ; middle < 4 ; middle++){
            location[MIDDLE_ROUTE] = (char)middle + '0';
            for(int lower = 1 ; lower < 4 ; lower++){
                location[LOWER_ROUTE] = (char)lower + '0';
                
                #if defined (DEBUG)
                printf("Ruta : %s \n", location);
                #endif

                char buffer[BUFFER_SIZE];
                FILE *file = fopen(location, "r");
                //printf("INICIO1.5\n");
                if(file == NULL){
                // No FILE
                    continue;  
                }else{
                // FILE exists
                    fgets(buffer, BUFFER_SIZE, file);
                    fclose(file);
                    strcpy(phrases[nFilesFound], buffer);
                    
                    #if defined (DEBUG)
                    printf("Frase copiada: %s\n", phrases[nFilesFound]);
                    #endif

                    nFilesFound++;      
                }
                // Return condition
                if(nFilesFound == 3) return;    
            }
        }
    }
    return;
}

void sortAndPrint(char phrases[][BUFFER_SIZE]){
    char auxPhrases[BUFFER_SIZE*3];
    for(int i = 1 ; i < 4 ; i++){
        for(int j = 0 ; j < 3 ; j++){
            if (phrases[j][0] == (char)i + '0'){
                char *token = strtok(phrases[j], ",");
                while(token != NULL){
                    token = strtok(NULL, " ");
                    if(token == NULL) break;
                    strcat(auxPhrases, token);
                    strcat(auxPhrases, " ");
                }
                break;
            }
        }
    }

    printf("%s \n", auxPhrases);
}

int main(int argc, char *argv[]){
    createMaze();
    hideAllTxts();
    char phrases[3][BUFFER_SIZE];
    searchAllPhrases(phrases);
    sortAndPrint(phrases);

    return 1;
}