#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int no_deleted_registers = NO_DELETED_REGISTERS;



void replaceExtensionByIdx(const char *fileName, char * indexName){
  char cad[5]=".idx";

  if(!fileName||!indexName) return;

  strcpy(indexName,fileName);
  indexName=strtok(indexName,".");
  strcat(indexName,cad);

  return;
}



bool createTable(const char * tableName) {
  FILE* f=NULL;

  if(!tableName) return false;

  f=fopen(tableName,"wb");
  if(!f) return false;

  fwrite(&no_deleted_registers,sizeof(int),1,f);
  fclose(f);

  return true;
}



bool createIndex(const char *indexName){
  FILE* f=NULL;

  if(!indexName) return false;

  f=fopen(indexName,"wb");
  if(!f) return false;

  fwrite(&no_deleted_registers,sizeof(int),1,f);
  fwrite(&no_deleted_registers,sizeof(int),1,f);
  fclose(f);

  return true;
}



void printnode(int _level, int level, FILE * indexFileHandler, int node_id, char side){
    char cad[50]="\0";
    Node node;
    int aux, i;
    char r = 'r';
    char l = 'l';
  /*si hemos llegado al nivel máximo indicado->return*/
    if(!indexFileHandler||node_id==-1||_level==level) return;

    aux=8+(sizeof(Node)*node_id);
    fseek(indexFileHandler,aux,SEEK_SET);
    fread(&node, sizeof(Node), 1, indexFileHandler);

    if(side==l){
        aux=8+(sizeof(Node)*node.left);
        fseek(indexFileHandler,aux,SEEK_SET);
        fread(&node, sizeof(Node), 1, indexFileHandler);
        for(i=0;i<=_level;i++){
        cad[i]=' ';
        }

        fprintf(stdout,"%sl %s (%d): %d",cad,node.book_id,node_id,node.offset);
        fprintf(stdout,"\n");

    }

    if(side==r){
        aux=8+(sizeof(Node)*node.right);
        fseek(indexFileHandler,aux,SEEK_SET);
        fread(&node, sizeof(Node), 1, indexFileHandler);
        for(i=0;i<=_level;i++){
        cad[i]=' ';
        }
        /*type=id, obtenido del anterior node.right*/
        fprintf(stdout,"%sr %s (%d): %d",cad,node.book_id,node_id,node.offset);
        fprintf(stdout,"\n");
    }

    _level++;

    printnode(_level,level,indexFileHandler,node.left,l);
    printnode(_level,level,indexFileHandler,node.right,r);

    return;
}

void printTree(size_t level, const char * indexName){
    Node node;
    FILE* f=NULL;
    int max,p;
    char r = 'r';
    char l = 'l';

    if(!indexName||level<=0) return;
    f = fopen(indexName,"rb");
    if(!f) return;

    max=level-1;
    fseek(f,0,SEEK_SET);
    fread(&p, sizeof(int), 1, f);
    fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*p),SEEK_SET);
    fread(&node, sizeof(Node), 1, f);
    fprintf(stdout,"%s (%d): %d",node.book_id,p,node.offset);
    fprintf(stdout,"\n");

    if(max==0){
        fclose(f);
        return;
    }

    printnode(0,max,f,node.left,l);
    printnode(0,max,f,node.right,r);

    fclose(f);
    return;
}




bool findKey(const char * book_id, const char *indexName, int * nodeIDOrDataOffset) {
  FILE* f=NULL;
  Node node;
  int parent,cmp,id;

  if(!book_id||!indexName||!nodeIDOrDataOffset) return false;

  f=fopen(indexName,"rb");
  if(!f) return false;

  fseek(f,0,SEEK_SET);
  fread(&parent,sizeof(int),1,f);

  /*si raíz es -1, devuelve false*/
  if(parent==-1) {
    fclose(f);
    return false;
  }

  while(!feof(f)&&parent!=-1){
    /*guardamos id del último registro visitado*/
    id=parent;
    fseek(f,8+(sizeof(Node)*parent),SEEK_SET);
    fread(&node, sizeof(Node), 1, f);
    cmp=strcmp(book_id,node.book_id);
    if(cmp==0){
      *nodeIDOrDataOffset=node.offset;
      fclose(f);
      return true;
    }
    else if(cmp<0) parent=node.left;
    else if(cmp>0) parent=node.right;
  }

  *nodeIDOrDataOffset=id;
  fclose(f);
  return false;
 }




 bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
   FILE* f=NULL;
   Node node;
   int aux,parent,deleted,offset;
   int flag=0,cero=0;

   if(!book_id||bookOffset<0||!indexName) return false;

   /*lectura y escritura*/
   f=fopen(indexName,"r+b");
   if(!f) return false;
   /*id nodo padre*/
   fseek(f,0,SEEK_SET);
   fread(&parent,sizeof(int),1,f);
   /*registro borrado*/
   fseek(f,4,SEEK_SET);
   fread(&deleted,sizeof(int),1,f);
   /*si no hay registros, insertamos el primero(nodo raíz)*/
   if(parent==-1){
     fseek(f,0,SEEK_SET);
     fwrite(&cero,sizeof(int),1,f);
     fseek(f,8,SEEK_SET);
     fwrite(book_id,PK_SIZE,1,f);
     fwrite(&cero,sizeof(int),1,f);
     fwrite(&no_deleted_registers,sizeof(int),1,f);
     fwrite(&no_deleted_registers,sizeof(int),1,f);
     fwrite(&parent,sizeof(int),1,f);
     offset=4;
     fwrite(&offset,sizeof(int),1,f);
     fclose(f);
     return true;
   }
   /*si el registro está en el fichero, no insertamos nada*/
   if(findKey(book_id,indexName,&offset)==true){
     fclose(f);
     return false;
   }
   /*id del último nodo, guardada en variable offset*/
   aux=0;
   while(!feof(f)){
     fseek(f,8+aux,SEEK_SET);
     fread(&node,sizeof(Node),1,f);
     aux+=sizeof(Node);
   }
   offset=(aux/sizeof(Node))-1;

   addIndexEntryRec(f,book_id,bookOffset,node,parent,offset,deleted);

   /*actualizamos registro borrado*/
   aux=0;
   while(!feof(f)&&flag==0){
     fseek(f,8+aux,SEEK_SET);
     fread(&node,sizeof(Node),1,f);
     if(node.book_id[0]==' '){
       fseek(f,4,SEEK_SET);
       aux=aux/sizeof(Node);
       fwrite(&aux,sizeof(int),1,f);
       flag=1;
     }
     aux+=sizeof(Node);
   }
   /*si no hay registro borrado->no_deleted_registers*/
   if(flag==0){
     fseek(f,4,SEEK_SET);
     fwrite(&no_deleted_registers,sizeof(int),1,f);
   }

   fclose(f);
   return true;
 }



 bool addIndexEntryRec(FILE* f, char * book_id, int bookOffset, Node node,int type,int id,int deleted){
   int aux,parent,cmp;
   int cero=0;

   if(!f||!book_id) return false;

   parent=type;
   aux=8+(sizeof(Node)*type);
   fseek(f,aux,SEEK_SET);
   fread(&node, sizeof(Node), 1, f);
   cmp=strcmp(book_id,node.book_id);

   if(cmp<0){
     if(node.left==-1){
       /*actualiza conexión con un nuevo node.left para el registro insertado*/
       aux=8+(sizeof(Node)*parent);
       fseek(f,aux+8,SEEK_SET);
       /*node.left será igual a deleted si hay registro borrado*/
       if(deleted!=-1){
        fwrite(&deleted,sizeof(int),1,f);
        }else{ /*node.left será igual al último registro*/
          fwrite(&id,sizeof(int),1,f);
        }
       /*inserta nuevo registro*/
       /*si hay registro borrado, inserta en pos de registro borrado*/
       if(deleted!=-1){
         aux=8+(sizeof(Node)*deleted);
         fseek(f,aux,SEEK_SET);
         fwrite(book_id,PK_SIZE,1,f);
         fwrite(&cero,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&parent,sizeof(int),1,f);
         fwrite(&bookOffset,sizeof(int),1,f);
         return true;
       }else{ /*si no hay registro borrado, inserta registro al final del fichero*/
         fseek(f,0,SEEK_END);
         fwrite(book_id,PK_SIZE,1,f);
         fwrite(&cero,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&parent,sizeof(int),1,f);
         fwrite(&bookOffset,sizeof(int),1,f);
         return true;
       }
     }else{
      addIndexEntryRec(f,book_id,bookOffset,node,node.left,id,deleted);
    }
   }

   if(cmp>0){
     if(node.right==-1){
       /*actualiza conexión con un nuevo node.right para el registro insertado*/
       aux=8+(sizeof(Node)*parent);
       fseek(f,aux+12,SEEK_SET);
       /*node.right será igual a deleted si hay registro borrado*/
       if(deleted!=-1){
        fwrite(&deleted,sizeof(int),1,f);
        }else{ /*node.right será igual al último registro*/
          fwrite(&id,sizeof(int),1,f);
        }
       /*inserta nuevo registro*/
       /*si hay registro borrado, inserta en pos de registro borrado*/
       if(deleted!=-1){
         aux=8+(sizeof(Node)*deleted);
         fseek(f,aux,SEEK_SET);
         fwrite(book_id,PK_SIZE,1,f);
         fwrite(&cero,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&parent,sizeof(int),1,f);
         fwrite(&bookOffset,sizeof(int),1,f);
         return true;
       }else{ /*si no hay registro borrado, inserta registro al final del fichero*/
         fseek(f,0,SEEK_END);
         fwrite(book_id,PK_SIZE,1,f);
         fwrite(&cero,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&no_deleted_registers,sizeof(int),1,f);
         fwrite(&parent,sizeof(int),1,f);
         fwrite(&bookOffset,sizeof(int),1,f);
         return true;
       }
     }else{
      addIndexEntryRec(f,book_id,bookOffset,node,node.right,id,deleted);
    }
   }

   return true;
 }



bool addTableEntry(Book * book, const char * dataName, const char * indexName) {
  FILE* f=NULL;
  Node node;
  int len,deleted;
  int aux=0,offset=0;

  if(!book||!dataName||!indexName) return false;

  /*si existe la clave, no insertamos*/
  if(findKey(book->book_id,indexName,&offset)==true) return false;

  f=fopen(dataName,"r+b");
  if(!f) return false;
  /*registro borrado*/
  fseek(f,0,SEEK_SET);
  fread(&deleted,sizeof(int),1,f);
  /*si no hay registros borrados inserta al final del fichero*/
  if(deleted==no_deleted_registers){
    fseek(f,0,SEEK_END);
    len=strlen(book->title);
    fwrite(&(book->book_id),PK_SIZE,1,f);
    fwrite(&len,sizeof(int),1,f);
    fwrite(book->title,len,1,f);
    fclose(f);
  }else{
    /*insertamos registro en posición correspondiente si hay registro borrado*/
    fseek(f,4+deleted,SEEK_SET);
    len=strlen(book->title);
    fwrite(&(book->book_id),PK_SIZE,1,f);
    fwrite(&len,sizeof(int),1,f);
    fwrite(book->title,len,1,f);
    /*actualiza registros borrados*/
    fseek(f,0,SEEK_SET);
    fwrite(&no_deleted_registers,sizeof(int),1,f);
    fclose(f);
  }

  f=fopen(indexName,"rb");
  if(!f) return false;
  /*obtenemos offset del registro*/
  while(!feof(f)){
    /*evitar error: "Conditional jump or move depends on uninitialised value(s)"*/
    node.offset=0;
    fseek(f,8+aux,SEEK_SET);
    fread(&node,sizeof(Node),1,f);
    if(node.offset>offset){
      offset=node.offset;
    }
    aux+=sizeof(Node);
  }
  fclose(f);

  offset+=PK_SIZE+1+len+sizeof(int);
  /*añadimos registro al fichero indexName*/
  if(addIndexEntry(book->book_id,offset,indexName)==false) return false;

  return true;
}
