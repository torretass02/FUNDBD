#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char * indexName) {
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
    int i;

    if(!indexFileHandler||_level==level||node_id==-1) return;

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

    f = fopen(indexName,"rb");
    if(!f) return;

    max=level-1;
    fseek(f,0,SEEK_SET);
    fread(&p, sizeof(int), 1, f);
    fseek(f,8+(sizeof(Node)*p),SEEK_SET);
    fread(&node, sizeof(Node), 1, f);
    fprintf(stdout,"%s (%d): %d",node.book_id,p,node.offset);
    fprintf(stdout,"\n");

    if(max==0){
        fclose(f);
        return;
    }

    printnode(max,max,f,node.left,0);
    printnode(max,max,f,node.right,1);

    fclose(f);
    return;
}

bool findKey(const char * book_id, const char *indexName, int * nodeIDOrDataOffset){
    FILE* f=NULL;
    Node node;
    int p,cmp,aux;

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
        fseek(f,8+(sizeof(Node)*p),SEEK_SET);
        fread(&node, sizeof(Node), 1, f);
        cmp=strcmp(book_id,node.book_id);
        if(cmp==0){
            *nodeIDOrDataOffset=node.offset;
            fclose(f);
            return true;
        }
        else if(cmp<0) p=node.left;
        else if(cmp>0) p=node.right;
    }

    *nodeIDOrDataOffset=aux;
    fclose(f);

    return false;
}

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    return true;
}

bool addTableEntry(Book * book, const char * dataName, const char * indexName) {
    return true;
}