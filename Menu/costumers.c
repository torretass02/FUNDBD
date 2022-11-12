#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "costumers.h"

static int ShowCostumersSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf("#### COSTUMERS MENU ####\n"
               " (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

void ShowCostumersMenu() {
    int nChoice = 0;
    int r = 0;

    do {
        nChoice = ShowCostumersSubMenu();
        switch (nChoice) {
            case 1: {
                r = PrintFindCostumers();
            }
                break;

            case 2: {
                r = PrintListProducts();
            }
                break;

            case 3: {
                r = PrintBalance();
            }
                break;

            case 4: {
                PrintBack();
            }
                break;
        }
    } while (nChoice != 4 && r == EXIT_SUCCESS);

}

static int PrintFindCostumers() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char z[BufferLength] = "\0";
    char n[BufferLength] = "\0";
    char a[BufferLength] = "\0";
    SQLINTEGER f = 0;
    char k[BufferLength] = "\0";


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/
    ret = SQLPrepare(stmt, (SQLCHAR*) "select c.customername, c.contactfirstname, c.contactlastname, c.customernumber from customers c where c.contactfirstname like ? or c.contactlastname like ? order by c.customernumber asc ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer name > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';
        strcpy(k,"%");
        strcat(k,x);
        strcat(k,"%");
        printf("\n");
        
        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, k, 0, NULL);
        (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, k, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) z, BufferLength , NULL); /*asocia columna1 del contenedor stmt a la variable y*/
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) n, BufferLength , NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) a, BufferLength , NULL);
        (void) SQLBindCol(stmt, 4, SQL_C_SLONG, &f, 0, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%d %s %s %s\n", f, z, n, a);
        }

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
        }
    }

    ret = fflush(stdout);
    
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int PrintListProducts() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char y[BufferLength] = "\0";
    SQLINTEGER z = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select p.productname, sum(od.quantityordered) from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on o.ordernumber=od.ordernumber join products p on p.productcode=od.productcode where c.customernumber=? group by p.productcode order by p.productcode asc ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';
        printf("\n");

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL); /*asocia columna1 del contenedor stmt a la variable y*/
        (void) SQLBindCol(stmt, 2, SQL_C_SLONG, &z, 0, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%s %d\n", y, z);
        }

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
        }
    }

    ret = fflush(stdout);
    
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static int PrintBalance() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    SQLREAL y = 0;
    SQLREAL z = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select sum(pa.amount) from customers c join payments pa on pa.customernumber=c.customernumber where c.customernumber=? ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';

        printf("\n");

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_FLOAT, &y, 0, NULL);

        /* Loop through the rows in the result-set */

        SQL_SUCCEEDED(ret = SQLFetch(stmt));

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
        }
    }    

    ret = SQLPrepare(stmt, (SQLCHAR*) "select sum(od.quantityordered*od.priceeach) from customers c join orders o on c.customernumber=o.customernumber join orderdetails od on od.ordernumber=o.ordernumber join products p on od.productcode=p.productcode where c.customernumber=?;", SQL_NTS);

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

    (void) SQLExecute(stmt);

    (void) SQLBindCol(stmt, 1, SQL_C_FLOAT, &z, 0, NULL);

    /* Loop through the rows in the result-set */

    while(SQL_SUCCEEDED(ret = SQLFetch(stmt))){
        float p = y - z;
        printf("Balance = %.2f\n", p);
    }
    
    ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
       return ret;
    }

    ret = fflush(stdout);
    
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}