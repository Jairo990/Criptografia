#include <stdio.h>
#include <ctype.h>

int main(){
	FILE* fp =  fopen("song.txt", "r");
	FILE* enc = fopen("encrypted.txt", "a");
	if (!fp){
		printf("\nError al abrir el archivo de la cancion\n");
		return 1;
	}
	if(!enc){
		printf("\nError al abrir el archivo cifrado");
		return 1;
	}

	int shift;
	printf("\nIngrese el desplazamiento (entero) >> ");
	scanf("%d", &shift);
	int c;
	while((c = fgetc(fp))!=EOF){
		//printf("%c", c);
		char encrypted_char = c;
		if(isupper(c)){
			encrypted_char = c - 'A';
			encrypted_char += shift;
			encrypted_char = ((encrypted_char % 26) + 26) % 26; // Para manejar desplazamientos negativos
			encrypted_char += 'A';
		}

		if(islower(c)){
			encrypted_char = c - 'a';
			encrypted_char += shift;
			encrypted_char = ((encrypted_char % 26) + 26) % 26; // Para manejar desplazamientos negativos
			encrypted_char += 'a';
		}
		
		//fwrite(encrypted_char, size_of(char), 1, enc);
		fputc(encrypted_char, enc);

	}
	printf("\nArchivo encriptado... (Revisa encrypted.txt)");
	fclose(fp);
	fclose(enc);
	return 0;
}