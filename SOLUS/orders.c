#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "orders.h"



static int ShowOrderSubMenu();
static int PrintOpen();
static int PrintRange();
static int PrintDetails();



static int ShowOrderSubMenu() {
  int nSelected = 0;
  char buf[16];

  do {
      printf("\n\n\n");
      printf("--O R D E R S  M E N U--\n\n");
      printf(" (1) Open\n"
             " (2) Range\n"
             " (3) Detail\n"
             " (4) Back\n\n");

      printf("Enter a number that corresponds to your choice > ");
      if (!fgets(buf, 16, stdin))
          nSelected =0;
      else
          nSelected = atoi(buf);
      printf("\n");

      if ((nSelected < 1) || (nSelected > 4)) {
          printf("Try again...\n");
      }
  } while ((nSelected < 1) || (nSelected > 4));

  return nSelected;
}




void OrdersMenu() {
  int nChoice = 0;
  int flag=EXIT_SUCCESS;

  do {
      nChoice = ShowOrderSubMenu();
      switch (nChoice) {
          case 1: {
              flag=PrintOpen();
          }
              break;

          case 2: {
              flag=PrintRange();
          }
              break;

          case 3: {
              flag=PrintDetails();
          }
              break;

          case 4: {

          }
              break;
      }
  } while (nChoice != 4||flag!=EXIT_SUCCESS);
}


static int PrintOpen(void){
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  SQLINTEGER x = 0;/*ordernumber*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select o.ordernumber from orders o where o.shippeddate is null order by o.ordernumber asc ;",SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  (void)SQLExecute(stmt);

  (void)SQLBindCol(stmt, 1, SQL_C_SLONG, &x, 0, NULL);

  /* Loop through the rows in the result-set */
  while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("%d\n", x);
  }

  (void)SQLCloseCursor(stmt);
  printf("\n");

  ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  if (!SQL_SUCCEEDED(ret2)) {
      odbc_extract_error("", stmt, SQL_HANDLE_STMT);
      return ret;
  }

  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  return EXIT_SUCCESS;
}


static int PrintRange(void){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char fecha[512]; /*fecha*/
  char* token1;
  char* token2;
  SQLINTEGER x = 0; /*ordernumber*/
  char y[BufferLength] = "\0"; /*orderdate*/
  char z[BufferLength] = "\0"; /*shippeddate*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select o.ordernumber,o.orderdate,o.shippeddate from orders o where o.orderdate>=? and o.orderdate<=? order by o.ordernumber asc ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
  (void)fflush(stdout);

  if(fgets(fecha,BufferLength,stdin)!=NULL){
    /*elimina el salto de línea*/
    fecha[strlen(fecha)-1]='\0';
    /*partir la fecha introducida en token1 (1ºfecha) y token2 (2ºfecha)*/
    token1=strtok(fecha," ");
    token2=strtok(NULL," ");
    token2=strtok(NULL,"\0");

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, token1, 0, NULL);
    (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, token2, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_SLONG, &x, 0, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) y, BufferLength, NULL);
    (void)SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) z, BufferLength, NULL);
    printf("\n");
      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%d %s %s\n", x,y,z);
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


static int PrintDetails(void){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength] = "\0"; /*ordernumber*/
  char *end;
  long int ordernumber = 0; /*ordernumber a buscar*/
  char date[BufferLength] = "\0"; /*fecha en la que se envió*/
  char status[BufferLength] = "\0"; /*estado del pedido*/
  SQLREAL total = 0; /*coste total del pedido (float)*/
  char productcode[BufferLength] = "\0"; /*productcode*/
  SQLINTEGER quantity = 0; /*unidades solicitadas*/
  SQLREAL price = 0; /*precio por unidad (float)*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;


  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select o.orderdate, o.status from orders o where o.ordernumber=? ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter ordernumber > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    /*elimina el salto de línea*/
    x[strlen(x)-1]='\0';
    /*transforma a long int*/
    ordernumber=strtol(x,&end,10);

    /*primera consulta-> obtener fecha y estado del pedido*/
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) date, BufferLength, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) status, BufferLength, NULL);
    printf("\n");
    /*imprime los resultados de la consulta*/
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("%s %s\n",date,status);
    }

    (void)SQLCloseCursor(stmt);
    printf("\n");

    /*segunda consulta -> obtener el coste total del pedido*/
    ret = SQLPrepare(stmt,(SQLCHAR*) "select sum(od.priceeach*od.quantityordered) from orders o join orderdetails od on o.ordernumber=od.ordernumber where o.ordernumber=? ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_FLOAT, &total, 0, NULL);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("%.2f\n",total); /*dos decimales*/
    }

    (void)SQLCloseCursor(stmt);
    printf("\n");

    /*tercera consulta -> productcode-quantityordered-priceeach del pedido*/
    ret = SQLPrepare(stmt,(SQLCHAR*) "select od.productcode, od.quantityordered, od.priceeach from orders o join orderdetails od on o.ordernumber=od.ordernumber where o.ordernumber=? order by od.orderlinenumber ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) productcode, BufferLength, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_SLONG, &quantity, 0, NULL);
    (void)SQLBindCol(stmt, 3, SQL_C_FLOAT, &price, 0, NULL);
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
      printf("%s %d %.2f\n",productcode,quantity,price);
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
