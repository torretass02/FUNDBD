#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int menu(){
    int n = 0;
    char buf[16];

    do {

        printf(" 1- Use\n"
               " 2- Insert\n"
               " 3- Print\n"
               " 4- Exit \n\nInserte una opción > ");
        if (!fgets(buf, 16, stdin))
            n=0;
        else
            n=atoi(buf);
        printf("\n");

        if ((n < 1) || (n > 4)) {
            printf("Vuelva a intentarlo:\n");
        }
    } while ((n < 1) || (n > 4));

    return n;
}

int main(){
    int n = 0;
    char dataName[50], indexName[50];
    int use = 0;
    int insert = 0;

    do{
        n = menu();
        switch(n){
            case 1:{
                if(use==1) {
                    printf("Error, ya hay una tabla %s ...\n",dataName);
                    break;
                }

                printf("Escriba el nombre de la tabla: ");

                if(fgets(dataName,50,stdin)!=NULL){
                    dataName[strlen(dataName)-1]='\0';
                    createTable(dataName);
                    replaceExtensionByIdx(dataName,indexName);
                    createIndex(indexName);
                    use = 1;
                }
            }
                break;

            case 2:{
                if(flag_use==0) {
                    printf("Error, primero seleccione la opción use\n");
                    break;
                }
                
                printf("Escriba la clave: ");

                if(fgets(key,50,stdin)!=NULL){
                    key[strlen(key)-1]='\0';

                    if(strlen(key)!=4){
                        printf("Error\n");
                        break;
                    }

                    printf("Escriba el título: ");

                    if(fgets(title,50,stdin)!=NULL){
                        title[strlen(title)-1]='\0';
                        strcpy(book.book_id,key);
                        book.title_len=strlen(title);
                        book.title=(char*)malloc(book.title_len+1);
                        strcpy(book.title,title);

                        if(addTableEntry(&book,dataName,indexName)==false){
                            printf("Error\n");
                        }

                        free(book.title);
                    }
                    insert = 1;
                }
            }
                break;
            case 3:{
                if(use==0) {
                    printf("Error, primero seleccione la opción use\n");
                    break;
                }

                if(flag_insert==0){
                    printf("Error, primero seleccione la opción insert\n");
                    break;
                }

                printf("Esriba la profundidad del árbol: ");

                if(fgets(aux,50,stdin)!=NULL){
                    aux[strlen(aux)-1]='\0';
                    printf("\n");
                    depth=strtol(aux,&end,10);
                    printTree((long int)depth,indexName);
                }
            }
            break;

            case 4:{
                printf("Bye Bye!\n");
            }
                break;
        }
    }
}
