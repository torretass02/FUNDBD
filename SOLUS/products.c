#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"



static int ShowProductSubMenu();
static int PrintStock();
static int PrintFind();



 static int ShowProductSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {
        printf("\n\n\n");
        printf("--P R O D U C T S  M E N U--\n\n");
        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            nSelected =0;
        else
          nSelected = atoi(buf);

        printf("\n");

        if ((nSelected < 1) || (nSelected > 3)) {
            printf("Try again...\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}



void ProductsMenu() {
  int nChoice = 0;
  int flag=EXIT_SUCCESS;

  do {
      nChoice = ShowProductSubMenu();
      switch (nChoice) {
          case 1: {
              flag=PrintStock();
          }
              break;

          case 2: {
              flag=PrintFind();
          }
              break;

          case 3: {

          }
              break;
      }
  } while (nChoice != 3||flag!=EXIT_SUCCESS);
}




static int PrintStock(void){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength] = "\0"; /*ID del producto a buscar*/
  SQLINTEGER y = 0;/*Cantidad en stock*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;


  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select p.quantityinstock from products p where p.productcode=? ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter productcode > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    /*elimina el salto de línea generado por fgets*/
    x[strlen(x)-1]='\0';

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_SLONG, &y, 0, NULL);
    printf("\n");
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("%d\n", y);
    }

    (void)SQLCloseCursor(stmt);
    printf("\n");
  }

  ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  if (!SQL_SUCCEEDED(ret2)) {
      odbc_extract_error("", stmt, SQL_HANDLE_STMT);
      return ret;
  }

  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}


static int PrintFind(void){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength] = "\0"; /*cadena que queremos buscar*/
  char y[BufferLength] = "\0"; /*productcode*/
  char z[BufferLength] = "\0"; /*productname*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select p.productcode, p.productname from products p where p.productname like ? order by p.productcode asc ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter productname > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    char aux[BufferLength] = "\0";
    /*elimina el salto de línea generado por fgets*/
    x[strlen(x)-1]='\0';
    strcpy(aux,"%");
    strcat(aux,x);
    strcat(aux,"%");

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &aux, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) z, BufferLength, NULL);
    printf("\n");
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%s\t%s\n", y,z);
    }

    (void)SQLCloseCursor(stmt);
    printf("\n");
  }

  ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  if (!SQL_SUCCEEDED(ret2)) {
      odbc_extract_error("", stmt, SQL_HANDLE_STMT);
      return ret;
  }

  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
