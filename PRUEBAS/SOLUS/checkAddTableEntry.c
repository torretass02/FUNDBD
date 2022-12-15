
#include "tester.h"

void checkAddTableEntry(const char * tableName,const char * indexName)
/**
 *  check AddTableEntry
 */
{
  Book book;
  char bookid[5],title[64];
  bool result;
  int len;

  /* add a new node */
  strcpy(bookid,"MAR5");
  strcpy(title,bookid);
  strcat(title+PK_SIZE,"_four");
  len=strlen(title);
  strcpy(book.book_id,bookid);
  book.title_len=strlen(title);
  book.title=(char *) malloc(len+1);
  strcpy(book.title,title);
  result=addTableEntry(&book, tableName, indexName);
  if (result==false){
      fprintf(stderr, "Error in checkAddTableEntry\n");
      exit(EXIT_FAILURE);
  }
  printf("-----after adding MAR5-------\n");
  printTree(6, indexName);
  free(book.title);


  /* 1) add existing node should complain*/
  strcpy(bookid,"MAR5");
  strcpy(title,bookid);
  strcat(title+PK_SIZE,"_twelve");
  len=strlen(title);
  strcpy(book.book_id,bookid);
  book.title_len=strlen(title);
  book.title=(char *) malloc(len+1);
  strcpy(book.title,title);
  result=addTableEntry(&book, tableName, indexName);
  printf("-----after adding MAR5-------\n");
  if (result==true){
      fprintf(stderr, "Error in checkAddTableEntry, existing node MAR5\n");
      exit(EXIT_FAILURE);
  }
  free(book.title);


  /* add a new node */
  strcpy(bookid,"DAR7");
  strcpy(title,bookid);
  strcat(title+PK_SIZE,"_twenty");
  len=strlen(title);
  strcpy(book.book_id,bookid);
  book.title_len=strlen(title);
  book.title=(char *) malloc(len+1);
  strcpy(book.title,title);
  result=addTableEntry(&book, tableName, indexName);
  if (result==false){
      fprintf(stderr, "Error in checkAddTableEntry\n");
      exit(EXIT_FAILURE);
  }
  printf("-----after adding DAR7-------\n");
  printTree(6, indexName);
  free(book.title);


  /* add a new node*/
  strcpy(bookid,"AAR0");
  strcpy(title,bookid);
  strcat(title+PK_SIZE,"_eleven");
  len=strlen(title);
  strcpy(book.book_id,bookid);
  book.title_len=strlen(title);
  book.title=(char *) malloc(len+1);
  strcpy(book.title,title);
  result=addTableEntry(&book, tableName, indexName);
  if (result==false){
      fprintf(stderr, "Error in checkAddTableEntry\n");
      exit(EXIT_FAILURE);
  }
  printf("-----after adding AAR0-------\n");
  printTree(6, indexName);
  free(book.title);


  printf("\n* checkAddTableEntry:OK\n");
}
