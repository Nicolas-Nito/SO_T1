#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Posición de las rutas en el string de la busqueda de archivos (1,2,3)
#define UPPER_ROUTE 10
#define MIDDLE_ROUTE 12
#define LOWER_ROUTE 14

// Tamaño máximo de las frases
#define BUFFER_SIZE 256

#define true  1
#define false 0

/****
Busca las "frases" escondidas en la carpeta laberinto, guardándolas en el
array de phrases
****/
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

/****
Realiza un sort a las frases encontradas para ordenarlas del 1 al 3
y mostrarlas en pantalla.
****/
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
