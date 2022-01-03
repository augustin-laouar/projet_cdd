#include "huffman.h"
char ** LireTable(char *f,char ** res)
{
  //char ** res =malloc(sizeof(char)*128);
  char *aux2= malloc(sizeof(char)*BUFSIZ);

  FILE * entree;
  entree=fopen(f,"r");
  int i=0;
  char* l= malloc(sizeof(char)*1);
  char c;
  char* v= malloc(sizeof(char)*1);
  strcpy(v,"\0");
  unsigned char c1;

  //initialisation du tableau a vide
  for(int d=0;d<128;d++)
  {
    res[d]=NULL;
  }

  while((c=fgetc(entree))!=EOF)
  {
    c1=c;
    while((c!='|') && (c!=EOF))
    {
      c=fgetc(entree);
      if(c!='|'){
        v[0]=c;
        //strcpy(v,&c);
        //strcat(v,"\0");
        strcat(aux2,v);
      }
      else{
        break;
      }
    }
      strcat(aux2,"\0");
      res[c1]= malloc(sizeof(char)*strlen(aux2));
      strcpy(res[c1],aux2);
      strcpy(aux2,"\0");
  }

  fclose(entree);
  return res;
}



char * supprimerDebut(char* s, int i){
  if(i>strlen(s)){
    return "\0";
  }
  //char * r = malloc(sizeof(char)*(strlen(s)-i));
  char * r = malloc(sizeof(char)*BUFSIZ);
  for(int j = 0;j<strlen(s)-i;j++){
    r[j] = s[i+j];
  }
  return r;
}
char * trouverCode(char * s, char ** table,char * c){
  for(int j = 0;j<128;j++){
    if(table[j]!= NULL){
      if(strcmp(s,table[j])==0){
        *c = j;
        return table[j];
      }
    }
  }
  return NULL; // si pas trouvé
}
void decompressionHuffman(char * entre, char * sortie,char* fichierTable){
  FILE * in = fopen(entre,"rb");
  if(in==NULL)
  {
    printf("impossible d ouvrir le fichier");
    exit(1);
  }
  FILE * out;
  out =fopen(sortie,"w");
  if(out==NULL)
  {
    printf("impossible d ouvrir le fichier");
    exit(1);
  }
//  char ** tab2 = malloc(sizeof(char*)*128);
//  tab2 = LireTable("test.txt",tab2);
  char ** table = malloc(sizeof(char*)*128);
  table = LireTable(fichierTable,table);
  char * code = malloc(sizeof(char)*BUFSIZ);
  //char * testeur = malloc(sizeof(char)*BUFSIZ);
  unsigned char c;
  unsigned char aux = 0b10000000;
  unsigned char res;
  char * caractere = malloc(sizeof(char));
  char * codeTrouve = malloc(sizeof(char)*BUFSIZ);
  bool echappement = false;
  while(!feof(in) && echappement == false){
    c = fgetc(in);
    for(int i = 0; i<8 ; i++){
      aux = aux>>(i);
      res = c & aux;
      if(res > 0){
        strcat(code,"1");
      }
      else{
        strcat(code,"0");
      }
      aux = 0b10000000;
    }    //recherche du code associé
    for(int i = 1; i<= strlen(code);i++){ // si ne fonctionne pas avec reset i a 1, utiliser while
      char * testeur = malloc(sizeof(char)*BUFSIZ);
      strncpy(testeur,code,i);
      codeTrouve = trouverCode(testeur,table,caractere);
      if(codeTrouve != NULL) {
        if(strcmp(codeTrouve,table[0])==0){ // arrive sur \0
          fputc(caractere[0],out);
          echappement = true;
          break;
        }
        fputc(caractere[0],out);
        code = supprimerDebut(code,strlen(codeTrouve));
        free(testeur);
        i = 0;
      }
    }
  }//
  fclose(in);
  fclose(out);

}
