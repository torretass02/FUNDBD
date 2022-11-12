#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"
#include "orders.h"
#include "customers.h"



static int ShowMainMenu();




int ShowMainMenu() {
    int nSelected = 0;
    char buf[16];

    do {
        printf("\n\n");
        printf("--M A I N  M E N U--\n\n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Exit \n\nEnter a number that corresponds to your choice > ");
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



int main() {
  int nChoice = 0;

  do {
      nChoice = ShowMainMenu();
      switch (nChoice) {
          case 1: {
                (void)ProductsMenu();
            }
              break;

          case 2: {
                (void)OrdersMenu();
            }
              break;

          case 3: {
                (void)CustomersMenu();
          }
            break;
          case 4: {
                printf("Bye Bye!!\n\n");
            }
            break;
        }
    } while (nChoice != 4);

  return 0;
}
