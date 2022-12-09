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


    return;
}

void printTree(size_t level, const char * indexName){
    FILE* f=NULL;
    Node node;
    int max,parent;

    f = fopen(indexName,"rb");
    if(!f) return;

    max=level-1;
    fseek(f,0,SEEK_SET);
    fread(&parent, sizeof(int), 1, f);
    fseek(f,8+(sizeof(Node)*parent),SEEK_SET);
    fread(&node, sizeof(Node), 1, f);
    fprintf(stdout,"%s (%d): %d",node.book_id,parent,node.offset);
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
     return true;
}

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    return true;
}

bool addTableEntry(Book * book, const char * dataName, const char * indexName) {
    return true;
}