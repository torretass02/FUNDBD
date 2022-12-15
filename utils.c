#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char * indexName) {
    char cad[5]=".idx";

    if(!fileName||!indexName) return;

    strcpy(indexName,fileName);
    indexName=strtok(indexName,".");
    strcat(indexName,cad);
    return;
}

bool createTable(const char * tableName) {
    FILE* f = NULL;

    if(!tableName) return false;

    f=fopen(tableName,"b");
    if(!f) return false;

    fwrite(&no_deleted_registers,sizeof(int),1,f);
    fclose(f);
    return true;
}

bool createIndex(const char *indexName) {
    FILE* f = NULL;

    if(!indexName) return false;

    f=fopen(indexName,"b");
    if(!f) return false;

    fwrite(&no_deleted_registers,sizeof(int),1,f);
    fwrite(&no_deleted_registers,sizeof(int),1,f);

    fclose(f);
    
    return true;
}

void printnode(size_t _level, size_t level, FILE * indexFileHandler, int node_id, char side){
    char esp[100]="\0";
    Node node;
    size_t i;

    if(!indexFileHandler||_level==level||node_id==-1) return;

    fseek(indexFileHandler, INDEX_HEADER_SIZE + (sizeof(Node)*node_id),SEEK_SET);
    fread(&node, sizeof(Node), 1, indexFileHandler);

    if(side==1){
        fseek(indexFileHandler, INDEX_HEADER_SIZE + (sizeof(Node)*node.right),SEEK_SET);
        fread(&node, sizeof(Node), 1, indexFileHandler);  
    
        for(i=0;i<=_level;i++){
            esp[i]=' ';
        }
        fprintf(stdout,"%sr %s (%d): %d", esp, node.book_id, node_id, node.offset);
        fprintf(stdout,"\n");
    } 

    if(side==0){
        fseek(indexFileHandler, INDEX_HEADER_SIZE +(sizeof(Node)*node.left),SEEK_SET);
        fread(&node, sizeof(Node), 1, indexFileHandler); 
        
        for(i=0;i<=_level;i++){
            esp[i]=' ';
        } 
        fprintf(stdout,"%sl %s (%d): %d", esp, node.book_id, node_id, node.offset);
        fprintf(stdout,"\n");
    }

    _level = _level+1;

    printnode(_level, level, indexFileHandler, node.left, 0);
    printnode(_level, level, indexFileHandler, node.right, 1);

    return;
}

void printTree(size_t level, const char * indexName){
    Node node;
    FILE* f=NULL;
    int max,p;
    char l = 'l';
    char r = 'r';

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

    printnode(max,max,f,node.left,l);
    printnode(max,max,f,node.right,r);

    fclose(f);
    return;
}

bool findKey(const char * book_id, const char *indexName, int * nodeIDOrDataOffset){
    Node node;
    FILE* f=NULL;
    int p,equal,aux;

    if(!book_id||!indexName||!nodeIDOrDataOffset) return false;

    f=fopen(indexName,"rb");
    if(!f) return false;

    fseek(f,0,SEEK_SET);
    fread(&p,sizeof(int),1,f);

    if(p==-1) {
        fclose(f);
        return false;
    }

    while(!feof(f)&&p!=-1){
        aux=p;
        fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*p),SEEK_SET);
        fread(&node, sizeof(Node), 1, f);
        equal=strcmp(book_id,node.book_id);

        if(equal==0){
            *nodeIDOrDataOffset=node.offset;
            fclose(f);
            return true;
        }

        else if(equal<0) p=node.left;
        else if(equal>0) p=node.right;
    }

    *nodeIDOrDataOffset=aux;
    fclose(f);

    return false;
}

bool addTableEntry(Book * book, const char * dataName, const char * indexName) {
    Node node;
    FILE* f=NULL;
    int l,del;
    int offset=0;
    int aux=0;

    if(findKey(book->book_id,indexName,&offset)==true) return false;

    if(!book||!dataName||!indexName) return false;

    f=fopen(dataName,"r+b");
    if(!f) return false;

    fseek(f,0,SEEK_SET);
    fread(&del,sizeof(int),1,f);

    if(del==no_deleted_registers){
        fseek(f,0,SEEK_END);
        l=strlen(book->title);
        fwrite(&(book->book_id),PK_SIZE,1,f);
        fwrite(&l,sizeof(int),1,f);
        fwrite(book->title,l,1,f);
        fclose(f);
    }
    else{
        fseek(f,4+del,SEEK_SET);
        l=strlen(book->title);
        fwrite(&(book->book_id),PK_SIZE,1,f);
        fwrite(&l,sizeof(int),1,f);
        fwrite(book->title,l,1,f);
        fseek(f,0,SEEK_SET);
        fwrite(&no_deleted_registers,sizeof(int),1,f);
        fclose(f);
    }

    f=fopen(indexName,"rb");
    if(!f) return false;

    while(!feof(f)){
        node.offset=0;
        fseek(f,8+aux,SEEK_SET);
        fread(&node,sizeof(Node),1,f);

        if(node.offset>offset){
            offset=node.offset;
        }

        aux+=sizeof(Node);
    }

    fclose(f);
    offset+=PK_SIZE+1+l+sizeof(int);

    if(addIndexEntry(book->book_id,offset,indexName)==false) return false;

    return true;
}

bool addIndexEntryRec(FILE* f, Node node, char * book_id, int bookOffset, int del, int id, int type){
    int p,equal;
    int root=0;

    if(!f||!book_id) return false;

    p=type;
    fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*type),SEEK_SET);
    fread(&node, sizeof(Node), 1, f);
    equal=strcmp(book_id,node.book_id);

    if(equal<0){
        if(node.left==-1){
            fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*p)+INDEX_HEADER_SIZE,SEEK_SET);

            if(del!=-1){
                fwrite(&del,sizeof(int),1,f);
            }
            else{
                fwrite(&id,sizeof(int),1,f);
            }

            if(del!=-1){
                fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*del),SEEK_SET);
                fwrite(book_id,PK_SIZE,1,f);
                fwrite(&root,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&p,sizeof(int),1,f);
                fwrite(&bookOffset,sizeof(int),1,f);
                return true;
            }
            else{
                fseek(f,0,SEEK_END);
                fwrite(book_id,PK_SIZE,1,f);
                fwrite(&root,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&p,sizeof(int),1,f);
                fwrite(&bookOffset,sizeof(int),1,f);
                return true;
            }
        }
        else{
            addIndexEntryRec(f,node,book_id,bookOffset,del,id,node.left);
        }
   }

    if(equal>0){
        if(node.right==-1){
            fseek(f,12+INDEX_HEADER_SIZE+(sizeof(Node)*p),SEEK_SET);

            if(del!=-1){
                fwrite(&del,sizeof(int),1,f);
            }
            else{
                fwrite(&id,sizeof(int),1,f);
            }

            if(del!=-1){
                fseek(f,INDEX_HEADER_SIZE+(sizeof(Node)*del),SEEK_SET);
                fwrite(book_id,PK_SIZE,1,f);
                fwrite(&root,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&p,sizeof(int),1,f);
                fwrite(&bookOffset,sizeof(int),1,f);
                return true;
            }
            else{
                fseek(f,0,SEEK_END);
                fwrite(book_id,PK_SIZE,1,f);
                fwrite(&root,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&no_deleted_registers,sizeof(int),1,f);
                fwrite(&p,sizeof(int),1,f);
                fwrite(&bookOffset,sizeof(int),1,f);
                return true;
            }

        }else{
            addIndexEntryRec(f,node,book_id,bookOffset,del,id,node.right);
        }
    }

    return true;
 }

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    Node node;
    FILE* f=NULL;
    int flag=0;
    int root=0;
    int aux = 0;
    int p,del,offset;

    if(!book_id||!bookOffset||!indexName||bookOffset<0) return false;

    f=fopen(indexName,"r+b");
    if(!f) return false;

    fseek(f,0,SEEK_SET);
    fread(&p,sizeof(int),1,f);

    fseek(f,DATA_HEADER_SIZE,SEEK_SET);
    fread(&del,sizeof(int),1,f);

    if(p==-1){
        fseek(f,0,SEEK_SET);
        fwrite(&root,sizeof(int),1,f);
        fseek(f,INDEX_HEADER_SIZE,SEEK_SET);
        fwrite(book_id,PK_SIZE,1,f);
        fwrite(&root,sizeof(int),1,f);
        fwrite(&no_deleted_registers,sizeof(int),1,f);
        fwrite(&no_deleted_registers,sizeof(int),1,f);
        fwrite(&p,sizeof(int),1,f);
        offset=PK_SIZE;
        fwrite(&offset,sizeof(int),1,f);
        fclose(f);
        return true;
    }

    if(findKey(book_id,indexName,&offset)==true){
        fclose(f);
        return false;
    }

    while(!feof(f)){
        fseek(f,INDEX_HEADER_SIZE+aux,SEEK_SET);
        fread(&node,sizeof(Node),1,f);
        aux+=sizeof(Node);
    }

    offset=(aux/sizeof(Node))-1;
    addIndexEntryRec(f,node,book_id,bookOffset,del,offset,p);
    aux=0;

    while(!feof(f)&&flag==0){
        fseek(f,INDEX_HEADER_SIZE+aux,SEEK_SET);
        fread(&node,sizeof(Node),1,f);

        if(node.book_id[0]==' '){
            fseek(f,DATA_HEADER_SIZE,SEEK_SET);
            aux=aux/sizeof(Node);
            fwrite(&aux,sizeof(int),1,f);
            flag=1;
        }

        aux+=sizeof(Node);
    }

    if(flag==0){
        fseek(f,DATA_HEADER_SIZE,SEEK_SET);
        fwrite(&no_deleted_registers,sizeof(int),1,f);
    }

    fclose(f);
    return true;
}