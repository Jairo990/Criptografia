 #include <stdio.h>

#include <stdlib.h>


typedef struct bmp {

    char bm[2]; 

    int tamano; 

    int reservado; 

    int offset; 

    int tamanoMetadatos;

    int ancho; 

    int alto;  

    short int numeroPlanos; 

    short int profundidadColor;

    int tipoCompresion;

    int tamanoEstructura;

    int pxmh; 

    int pxmv; 

    int coloresUsados;

    int coloresImportantes; 

    unsigned char **pixelR;     

    unsigned char **pixelG;     

    unsigned char **pixelB;     

} BMP;
 

int main(){

FILE* archivo = fopen("imagen.bmp", "rb");

if(!archivo){

printf("Error al abrir el archivo\n");

return 1;

}

BMP imagen;

int desplazamiento;

unsigned char R, G, B;


fseek(archivo, 0, SEEK_SET);


fread(&imagen.bm, sizeof(char), 2, archivo);

    fread(&imagen.tamano, sizeof(int), 1, archivo);

    fread(&imagen.reservado, sizeof(int), 1, archivo);

    fread(&imagen.offset, sizeof(int), 1, archivo);

    fread(&imagen.tamanoMetadatos, sizeof(int), 1, archivo);

    fread(&imagen.ancho, sizeof(int), 1, archivo); 

    fread(&imagen.alto, sizeof(int), 1, archivo);  

    fread(&imagen.numeroPlanos, sizeof(short int), 1, archivo);

    fread(&imagen.profundidadColor, sizeof(short int), 1, archivo);

    fread(&imagen.tipoCompresion, sizeof(int), 1, archivo);

    fread(&imagen.tamanoEstructura, sizeof(int), 1, archivo);

    fread(&imagen.pxmh, sizeof(int), 1, archivo);

    fread(&imagen.pxmv, sizeof(int), 1, archivo);

    fread(&imagen.coloresUsados, sizeof(int), 1, archivo);

    fread(&imagen.coloresImportantes, sizeof(int), 1, archivo);


if(imagen.bm[0] != 'B' || imagen.bm[1] != 'M'){

printf("El archivo no es un BMP\n");

fclose(archivo);

return 1;

}


if(imagen.profundidadColor != 24){

printf("El archivo no es un BMP de 24 bits\n");

fclose(archivo);

return 1;

}


printf("Introduce el desplazamiento de color: ");

    scanf("%d", &desplazamiento);


int padding = (4 - (imagen.ancho*3) % 4);


imagen.pixelR = malloc(imagen.alto * sizeof(char*));

imagen.pixelG = malloc(imagen.alto * sizeof(char*));

imagen.pixelB = malloc(imagen.alto * sizeof(char*));

for (int i=0; i < imagen.alto; i++) {

imagen.pixelR[i] = malloc(imagen.ancho * sizeof(char));

imagen.pixelG[i] = malloc(imagen.ancho * sizeof(char));

imagen.pixelB[i] = malloc(imagen.ancho * sizeof(char));

}


fseek(archivo, imagen.offset, SEEK_SET);


//leer los pixeles (r, g, b) y almacenarlos en las matrices correspondientes


for(int i = 0; i < imagen.alto; i++){

for(int j = 0; j< imagen.ancho; j++){

fread(&imagen.pixelB[i][j], sizeof(unsigned char), 1, archivo);

fread(&imagen.pixelG[i][j], sizeof(unsigned char), 1, archivo);

fread(&imagen.pixelR[i][j], sizeof(unsigned char), 1, archivo);

int b = (imagen.pixelB[i][j] + desplazamiento);

int g = (imagen.pixelG[i][j] + desplazamiento);

int r = (imagen.pixelR[i][j] + desplazamiento); 


imagen.pixelB[i][j] = ((b % 256) + 256) % 256; // Para manejar desplazamientos negativos

imagen.pixelG[i][j] = ((g % 256) + 256) % 256; // Para manejar desplazamientos negativos

imagen.pixelR[i][j] = ((r % 256) + 256) % 256; // Para manejar desplazamientos negativos

}

fseek(archivo, padding, SEEK_CUR);

}


FILE *output = fopen("imagen_cifrada.bmp", "wb");

if (!output) {

printf("Error al crear el archivo de salida\n");

fclose(output);

return 1;

}


fseek(archivo, 0, SEEK_SET);

    unsigned char* cabecera = malloc(imagen.offset);

    fread(cabecera, sizeof(unsigned char), imagen.offset, archivo);

    fwrite(cabecera, sizeof(unsigned char), imagen.offset, output);

    free(cabecera);


unsigned char padByte = 0;


for(int i=0; i< imagen.alto; i++){

for(int j=0; j< imagen.ancho; j++){

fwrite(&imagen.pixelB[i][j], sizeof(unsigned char), 1, output);

fwrite(&imagen.pixelG[i][j], sizeof(unsigned char), 1, output);

fwrite(&imagen.pixelR[i][j], sizeof(unsigned char), 1, output);

}

for(int k=0; k<padding; k++){

fwrite(&padByte, sizeof(unsigned char), 1, output);

}

}


for (int i = 0; i < imagen.alto; i++) {

        free(imagen.pixelR[i]);

        free(imagen.pixelG[i]);

        free(imagen.pixelB[i]);

    }

    free(imagen.pixelR);

    free(imagen.pixelG);

    free(imagen.pixelB);


fclose(archivo);

fclose(output);


printf("Imagen procesada y guardada como 'imagen_modificada.bmp'.\n");

return 0;

} 