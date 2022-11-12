#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "customers.h"



static int ShowCustomerSubMenu();
static int PrintFindCustomer();
static int PrintListProduct();
static int PrintBalance();



static int ShowCustomerSubMenu(){
   int nSelected = 0;
   char buf[16];

   do {
       printf("\n\n\n");
       printf("--C U S T O M E R S  M E N U--\n\n");
       printf(" (1) Find\n"
              " (2) List products\n"
              " (3) Balance\n"
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




void CustomersMenu() {
  int nChoice = 0;
  int flag=EXIT_SUCCESS;

  do {
      nChoice = ShowCustomerSubMenu();
      switch (nChoice) {
          case 1: {
              flag=PrintFindCustomer();
          }
              break;

          case 2: {
              flag=PrintListProduct();
          }
              break;

          case 3: {
              flag=PrintBalance();
          }
              break;

          case 4: {

          }
              break;
      }
  } while (nChoice != 4||flag!=EXIT_SUCCESS);
}




static int PrintFindCustomer(){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength] = "\0"; /*cadena que queremos buscar*/
  char y[BufferLength] = "\0"; /*customerName*/
  char z[BufferLength] = "\0"; /*contactFirstName*/
  char w[BufferLength] = "\0"; /*contactLastName*/
  int v = 0; /*customerNumber*/


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select c.customername, c.contactfirstname, c.contactlastname, c.customernumber from customers c where c.contactfirstname like ? or c.contactlastname like ? order by c.customernumber asc ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter customer name > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    char aux[BufferLength] = "\0";
    /*elimina el salto de línea generado por fgets*/
    x[strlen(x)-1]='\0';
    strcpy(aux,"%");
    strcat(aux,x);
    strcat(aux,"%");
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &aux, 0, NULL);
    (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &aux, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) z, BufferLength, NULL);
    (void)SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) w, BufferLength, NULL);
    (void)SQLBindCol(stmt, 4, SQL_C_SLONG, &v, 0, NULL);
    printf("\n");
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%d %s %s %s\n",v,y,z,w);
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



static int PrintListProduct(){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength]="\0"; /*customernumber*/
  long int customernumber=0; /*customernumber*/
  char *end;
  char y[BufferLength]="\0"; /*productname*/
  int quantity=0; /*quantityordered*/

  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select p.productname, sum(od.quantityordered) as cantidad from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on o.ordernumber=od.ordernumber join products p on p.productcode=od.productcode where c.customernumber=? group by p.productcode order by p.productcode asc ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter customer number > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    x[strlen(x)-1]='\0';
    /*transforma a long int*/
    customernumber=strtol(x,&end,10);

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength, NULL);
    (void)SQLBindCol(stmt, 2, SQL_C_SLONG, &quantity, 0, NULL);
    printf("\n");
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("%s %d\n",y,quantity);
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



static int PrintBalance(){
  #define BufferLength 512
  SQLHENV env = NULL;
  SQLHDBC dbc = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  char x[BufferLength] = "\0"; /*customernumber*/
  long int customernumber = 0; /*customernumber*/
  char *end;
  SQLREAL balance=0; 


  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) return EXIT_FAILURE;

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt,(SQLCHAR*) "select((select sum(pa.amount) from customers c join payments pa on pa.customernumber=c.customernumber where c.customernumber=?) - (select sum(od.quantityordered*od.priceeach) from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on od.ordernumber=o.ordernumber join products p on od.productcode=p.productcode where c.customernumber=?)) as balance ;", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return ret;
  }

  printf("Enter customer number > ");
  (void)fflush(stdout);

  if(fgets(x,BufferLength,stdin)!=NULL){
    /*elimina el salto de línea*/
    x[strlen(x)-1]='\0';
    /*transforma a long int*/
    customernumber=strtol(x,&end,10);

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
    (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
    (void)SQLExecute(stmt);

    (void)SQLBindCol(stmt, 1, SQL_C_FLOAT, &balance, 0, NULL);
    printf("\n");
    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf("Balance = %.2f\n",balance);
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
