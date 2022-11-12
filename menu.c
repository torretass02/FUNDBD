#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


/* #include "menu_template.h" */
/* #ifndef A2BIS_MENU_TEMPLATE_H */
/* #define A2BIS_MENU_TEMPLATE_H */

static int ShowMainMenu();
static void ShowProductsMenu();
static int ShowProductsSubMenu();
static void ShowOrdersMenu();
static int ShowOrdersSubMenu();
static void ShowCostumersMenu();
static int ShowCostumersSubMenu();
static int PrintOpen();
static int PrintRange();
static int PrintDetail();
static int PrintStock();
static int PrintFind();
static void PrintBack();
static int PrintFindCostumers();
static int PrintListProducts();
static int PrintBalance();

/* #endif //A2BIS_MENU_TEMPLATE_H */

/**
 * @brief Entry point, shows and process main menu.
 *
 * This function implements a loop that prints the main
 * menu, analyze the user selection and calls the
 * corresponding submenu
 *
 * @return 0 if no error
 * @author Hugo Torres & Luis Rodríguez
 */
int main(void) {
    int nChoice = 0;

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu();
            }
                break;

            case 2: {
                ShowOrdersMenu();
            }
                break;

            case 3: {
                ShowCostumersMenu();
            }
                break;
         
            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    return 0;
}


/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author Hugo Torres & Luis Rodríguez
 */
int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do {

        printf("#### MAIN MENU ####\n"
               " (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Quit\n\n"
               "Enter a number that corresponds to your choice > ");
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
                PrintBack();
            }
                break;
        }
    } while (nChoice != 3 && r == EXIT_SUCCESS);

}

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
 * @brief Shows and processes the Orders menu.
 *
 * This function implements a loop that prints the Orders
 * menu, analyze the user selection and prints
 * the selected Orders tail
 *
 * @return selected option
 * @author Hugo Torres & Luis Rodríguez
 */
void ShowOrdersMenu() {
    int nChoice = 0;
    int r = 0;

    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {
            case 1: {
                r = PrintOpen();
            }
                break;

            case 2: {
                r = PrintRange();
            }
                break;

            case 3: {
                r = PrintDetail();
            }
                break;

            case 4: {
                PrintBack();
            }
                break;
        }
    } while (nChoice !=4 && r == EXIT_SUCCESS);

}

/**
 * @brief prints the Orders menu and allows to select an option.
 *
 * @return selected option
 * @author Hugo Torres & Luis Rodríguez
 */
 int ShowOrdersSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {
        printf("#### ORDERS MENU ####\n"
               " (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
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

int ShowCostumersSubMenu() {
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

int PrintOpen() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    SQLINTEGER x = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select ordernumber from orders where shippeddate is null order by ordernumber asc ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    (void) fflush(stdout);
    
    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, &x, 0, NULL);

    (void) SQLExecute(stmt);

    (void) SQLBindCol(stmt, 1, SQL_C_SLONG, &x, 0, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
        printf("%d\n", x);
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

int PrintRange() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    SQLINTEGER y = 0;
    char z[BufferLength] = "\0";
    char p[BufferLength] = "\0";
    char* fecha1;
    char* fecha2;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select o.ordernumber,o.orderdate,o.shippeddate from orders o where o.orderdate>=? and o.orderdate<=? order by o.ordernumber asc ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)){
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';
        printf("\n");

        fecha1=strtok(x," ");
        fecha2=strtok(NULL," ");
        fecha2=strtok(NULL,"\0");

        printf("\n");

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, fecha1, 0, NULL);
        (void)SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, fecha2, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, &y, 0, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) z, BufferLength , NULL); /*asocia columna1 del contenedor stmt a la variable y*/
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR*) p, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%d %s %s\n", y, z, p);
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

int PrintDetail() {
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL; /*CONTENEDOR*/
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char x[BufferLength] = "\0";
    char y[BufferLength] = "\0";
    char z[BufferLength] = "\0";
    SQLINTEGER t = 0;
    SQLREAL p = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt); /*MALLOC*/

    ret = SQLPrepare(stmt, (SQLCHAR*) "select o.orderdate, o.status from orders o where o.ordernumber=? ;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter ordernumber > ");

    (void) fflush(stdout);

    if(fgets(x, (int) sizeof(x), stdin) != NULL){
        x[strlen(x)-1] = '\0';
        printf("\n");
        
        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL); /*asocia columna1 del contenedor stmt a la variable y*/
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR*) z, BufferLength , NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%s %s\n", y, z);
        }

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
            return ret;
        }

        ret = SQLPrepare(stmt, (SQLCHAR*) "select sum(od.priceeach*od.quantityordered) from orders o join orderdetails od on o.ordernumber=od.ordernumber where o.ordernumber=? ;", SQL_NTS);

        (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

        (void) SQLExecute(stmt);    

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, &t, 0, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
            printf("%d\n", t);
        }

        ret2 = SQLCloseCursor(stmt);/*OJO - LIMPIA EL CONTENEDOR STMT######################*/
        if (!SQL_SUCCEEDED(ret2)) {
            odbc_extract_error("", stmt, SQL_HANDLE_STMT);
            return ret;
        }
    }

    ret = SQLPrepare(stmt, (SQLCHAR*) "select od.productcode, od.quantityordered, od.priceeach from orders o join orderdetails od on o.ordernumber=od.ordernumber where o.ordernumber=? order by od.orderlinenumber ;", SQL_NTS);

    (void)SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, x, 0, NULL);

    (void) SQLExecute(stmt);    
    
    (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR*) y, BufferLength , NULL);
    (void) SQLBindCol(stmt, 2, SQL_C_SLONG, &t, 0, NULL);
    (void) SQLBindCol(stmt, 3, SQL_C_FLOAT, &p, 0, NULL);

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {/*imprimo el valor que tenga en ese momento la variable y*/
        printf("%s %d %.2f\n", y, t, p);
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

int PrintFindCostumers() {
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

int PrintListProducts() {
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

int PrintBalance() {
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

void PrintBack() {
    printf("<<<<<<< Volviendo atrás <<<<<<<\n\n");
}