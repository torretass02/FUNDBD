#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


static int ShowMainMenu();


int ShowMainMenu() {
    int nSelected = 0;
    char buf[16];

    do {
        printf("\n\n");
        printf("--M E N Ú  P R I N C I P A L--\n\n");

        printf(" (1) Use\n"
               " (2) Insert\n"
               " (3) Print\n"
               " (4) Exit \n\nInserte una opción > ");
        if (!fgets(buf, 16, stdin))
            nSelected=0;
        else
            nSelected=atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("Prueba otra vez ...\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}




int main() {
  Book book;
  int nChoice = 0;
  char aux[50];
  char* end;
  char dataName[50],indexName[50];
  char key[4]="   ",title[50];
  long int depth,flag_use=0,flag_insert=0;

  do {
      nChoice = ShowMainMenu();
      switch (nChoice) {
          case 1: {
            if(flag_use==1) {
              printf("Error: ya has creado una tabla %s ...\n",dataName);
              break;
            }
                printf("Inserte el nombre de la tabla: ");
                if(fgets(dataName,50,stdin)!=NULL){
                  dataName[strlen(dataName)-1]='\0';
                  createTable(dataName);
                  replaceExtensionByIdx(dataName,indexName);
                  createIndex(indexName);
                  flag_use=1;
                }
            }
              break;

          case 2: {
            if(flag_use==0) {
              printf("Error: debes seleccionar antes la opción (1) Use ...\n");
              break;
            }
                printf("Inserte clave: ");
                if(fgets(key,50,stdin)!=NULL){
                  key[strlen(key)-1]='\0';
                  if(strlen(key)!=4){
                    printf("\nError, PK_SIZE!=4 ...\n");
                    break;
                  }
                  printf("Inserte título: ");
                  if(fgets(title,50,stdin)!=NULL){
                    title[strlen(title)-1]='\0';
                    strcpy(book.book_id,key);
                    book.title_len=strlen(title);
                    book.title=(char*)malloc(book.title_len+1);
                    strcpy(book.title,title);
                    if(addTableEntry(&book,dataName,indexName)==false){
                      printf("\n¡Error al insertar!\n");
                    }
                    free(book.title);
                  }
                  flag_insert=1;
                }

            }
              break;

          case 3: {
            if(flag_use==0) {
              printf("Error: debes seleccionar antes la opción (1) Use ...\n");
              break;
            }
            if(flag_insert==0){
              printf("Error: debes insertar al menos un registro ...\n");
              break;
            }
                printf("Inserte la profundidad del árbol: ");
                if(fgets(aux,50,stdin)!=NULL){
                  aux[strlen(aux)-1]='\0';
                  printf("\n");
                  depth=strtol(aux,&end,10);
                  printTree((long int)depth,indexName);
                }
            }
            break;

          case 4: {
                printf("¡¡Hasta la próxima!!\n\n");
            }
            break;
        }
    } while (nChoice != 4);

  return 0;
}
