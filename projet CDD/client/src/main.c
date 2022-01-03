#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
    if(argc != 4){
      printf("3 arguments nécessaires. \n 1 : methode de compression. 0 pour LZW 1 pour huffman. \n 2 : nom du fichier demandé.\n 3 : nom du fichier ou stocké le résultat.\n");
      exit(0);
    }
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *requete = malloc(sizeof(char)*512);
    unsigned char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    char * fileName = argv[2];
    char * methode =argv[1];
    char * output = argv[3];
    strcpy(requete,methode);
    strcat(requete,fileName);
    send(sock , requete , strlen(requete) , 0 );
    FILE * temp = fopen("temp.txt","w");
    if(strcmp(methode,"0")==0){
      int * couple = malloc(sizeof(int)*2);
      while(read( sock , buffer, 3)!=0){
        decoder_couple(buffer,couple);
        fprintf(temp,"%d\n%d\n",couple[0],couple[1]);
      }
      fclose(temp);
      decompressionLZW("temp.txt",output,3800);
    }
    else{
      FILE * table = fopen("table.txt","w");
      read( sock , buffer, 1);
      while(buffer[0]!=255){
        fputc(buffer[0],table);
        read( sock , buffer, 1);
      }
      fclose(table);
      while(read( sock , buffer, 1)!=0){
        fputc(buffer[0],temp);
      }
      fclose(temp);
      decompressionHuffman("temp.txt",output,"table.txt");
    }
    printf("%s décompressé avec succes.\n",fileName);
    return 0;
}
