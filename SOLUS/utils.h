

#ifndef CODE_V2_UTILS_H
#define CODE_V2_UTILS_H
#include <stdio.h>
#include <stdbool.h>

#define NO_DELETED_REGISTERS -1

#define INDEX_HEADER_SIZE 8
#define DATA_HEADER_SIZE  4
#define PK_SIZE  4

/* Our table is going to contain a string (title) and
   an alphanumeric primary key (book_id)
*/
typedef struct book {
    char book_id[PK_SIZE+1]; /* primary key */
    size_t title_len; /* title length */
    char *title; /* string to be saved in the database */
} Book;

/* Note that in general a struct cannot be used to
   handle tables in databases since the table structure
   is unknown on compilation time.
*/

typedef struct node {
    char book_id[PK_SIZE+1];
    int left, right, parent, offset;
}Node;




void replaceExtensionByIdx(const char * fileName, char * indexName);
bool createTable(const char * tableName);
bool createIndex(const char * indexName);
void printTree(size_t level, const char * indexName);
void printRec(FILE *f,Node node,int flag,int type,int count,int level);
bool findKey(const char * book_id, const char * indexName, int * nodeIDOrDataOffset);
bool addIndexEntry(char * book_id, int bookOffset, const char * indexName);
bool addIndexEntryRec(FILE* f, char * book_id, int bookOffset, Node node, int type,int id,int deleted);
bool addTableEntry(Book * book, const char * tableName, const char * indexName);

#endif /* CODE_V2_UTILS_H */
