#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef unsigned long int ulint;

char * trouverCode(char * s, char ** table,char * c);
char ** LireTable(char *f,char** res);
void ecrireTable(char **t,char *f);
void decompressionHuffman(char * entre, char * sortie,char* fichierTable);
