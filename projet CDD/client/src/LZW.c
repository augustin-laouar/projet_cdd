#include "LZW.h"

void decoder_couple( unsigned char * triplet, int * sortie){
	int Oc1 = (int)triplet[0];
	int p1_Oc2 = (int)triplet[1] & 0b0000000000001111;
	p1_Oc2 = p1_Oc2<<(8);
	sortie[0]=Oc1 | p1_Oc2;
	int p2_Oc2 = (int)triplet[1] & 0b0000000011110000;
	p2_Oc2 = p2_Oc2>>(4);
	int Oc3 = (int)triplet[2];
	Oc3 = Oc3<<(4);
	sortie[1]=p2_Oc2 | Oc3;

}
void initDico(){
	DICO.nb_mots =0;
}
// transformer le code donné par le codeur en 3*8 bits avant de l'envoye

void emettreD(char *c, FILE* f){
	fprintf(f,"%s",c);
}
int ajouterDico(char* c,int reset){ // retourne le code ajt
	if(DICO.nb_mots == 3840){
		DICO.nb_mots = reset; // liberation de place dans le dico
	}
	if(strlen(c)==1){ // est un caractere simple
		int ascii = (int)c[0]; // recuperation du code ascii
		return ascii;
	}
	else{
		DICO.mots[DICO.nb_mots]=malloc(sizeof(char)*strlen(c));
		strcpy(DICO.mots[DICO.nb_mots],c);
		DICO.nb_mots++;
		return DICO.nb_mots+127;
	}
}

void valeur(int code, char * v){
	if(code < 128){
		char c = code;
		strcpy(v,&c);
	}
	else{
		strcpy(v,DICO.mots[code-128]);
	}
}

bool codeDansDico(int code){
	if(code<128){
		return true;
	}
	if(DICO.mots[code-128]==NULL){
		return false;
	}
	return true;
}

void decompressionLZW(char * nomEntre, char* nomSortie, int reset)
{
		FILE * entre = fopen(nomEntre,"r");
		FILE * sortie = fopen(nomSortie,"w");
		if(entre==NULL || sortie==NULL){
			printf("erreur open (decompression)\n");
			return -1;
		}
		initDico();
		char * ancien = malloc(sizeof(char)*BUFSIZ);
		int code;
		fscanf(entre,"%d",&code);
		valeur(code,ancien);
		emettreD(ancien,sortie);
		char *nouveau = malloc(sizeof(char)*BUFSIZ);
		char * aux = malloc(sizeof(char)*BUFSIZ);
		char * aux2 = malloc(sizeof(char)*BUFSIZ);
		char * val = malloc(sizeof(char)*BUFSIZ);
		while(fscanf(entre,"%d",&code)!=EOF){
			if(!codeDansDico(code)){ // si code n'est pas dans la table
						 strcpy(nouveau,ancien);
						 strcat(nouveau,&ancien[0]);

				}
				else{
					valeur(code,val);
					strcpy(nouveau,val);
				}
				emettreD(nouveau,sortie);
				strcpy(aux,ancien);
				strncpy(aux2,nouveau,1);
				strcat(aux,aux2);
				ajouterDico(aux,reset);
				strcpy(ancien,nouveau);
			}
		fclose(entre);
		fclose(sortie);
		}
