#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"

/**
 * @brief prints Products menu and allows to select an option.
 *
 * @return selected option
 * @author Hugo Torres & Luis Rodríguez
 */
int ShowProductsSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf("#### PRODUCT MENU ####\n"
               " (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}

/**
 * @brief Shows and processes the Products menu.
 *
 * This function implements a loop that prints the Products
 * menu, analyze the user selection and prints
 * the selected Products
 * @return void
 * @author Hugo Torres & Luis Rodríguez
 */
void ShowProductsMenu() {
    int nChoice = 0;
    int r = 0;

    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {

            case 1: {
                r = PrintStock();
            }
                break;

            case 2: {
                r = PrintFind();
            }
                break;

            case 3: {
                printf("<<<<<<< Volviendo atrás <<<<<<<\n\n");
            }
                break;
        }
    } while (nChoice != 3 && r == EXIT_SUCCESS);

}

int PrintStock() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    SQLINTEGER y = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select quantityinstock from products where productcode = ?;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter productcode > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, &y, 0, NULL); /*asocia columna1 del contenedor stmt a la variable y*/

        printf("\n");

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%d\n", y);
        }

        printf("\n");

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
        }
    }

    ret = fflush(stdout);
    
    /* free up statemenS10_1678t handle */
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

int PrintFind() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char y[BufferLength] = "\0";
    char z[BufferLength] = "\0";
    char k[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select p.productcode, p.productname from products p where p.productname like ? order by p.productcode asc ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter productname > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';
        strcpy(k,"%");
        strcat(k,x);
        strcat(k,"%");

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &k, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL); /*asocia columna1 del contenedor stmt a la variable y*/
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) z, BufferLength , NULL);

        printf("\n");

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%s %s\n", y, z);
        }

        printf("\n");

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
            return ret;
        }
    }

    ret = fflush(stdout);
    
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