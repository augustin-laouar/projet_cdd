#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
typedef struct {
	char * mots[3840];
	int nb_mots;
} dico_t;

static dico_t DICO;


void coder_couple(int * couple, unsigned char * retour);
void decoder_couple( unsigned char * triplet, int * sortie);
// transformer le code donné par le codeur en 3*8 bits avant de l'envoye
void emettre( const int code , FILE* f);
int estDansDico(char *c);
int ajouterDico(char* c,int reset);
unsigned long int compressionLZW(char * entre, char* sortie,int reset);
void initDico();
void decompressionLZW(char * entre, char* sortie, int reset);
void emettreD(char *c, FILE* f);
void valeur(int code,char * v);
bool codeDansDico(int code);
