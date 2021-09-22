#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/*crear_laberinto():
    funcion que crea los 3 pisos de carpetas*/

void crear_laberinto(){ 
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

const char* pos(){
    char x[3][6];
    strcpy(x[0], "/1");
    strcpy(x[1], "/2");
    strcpy(x[2], "/3");
    
    char *ubicacion =malloc (sizeof (char) * 30);
    strcat(ubicacion,"laberinto");
    strcat(ubicacion,x[rand()%3]);
    strcat(ubicacion,x[rand()%3]);
    strcat(ubicacion,x[rand()%3]);
    strcat(ubicacion,"/frase.txt");
    return ubicacion;
}

void ocultar(){
    
    const char* lugar = pos();
    printf("\n%s \n",lugar);

    FILE *a=fopen(lugar,"w");
    fprintf(a, "%s", "1, Los hurones del");
    fclose(a);

    const char* lugar2 = pos();
    printf("\n%s \n",lugar2);

    FILE *b=fopen(lugar2,"w");
    fprintf(b, "%s", "2, profesor de sistemas operativos son");
    fclose(b);
}

int main(int argc, char *argv[]){
    crear_laberinto();
    ocultar();
}