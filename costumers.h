#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

void ShowCostumersMenu();
int ShowCostumersSubMenu();
int PrintFindCostumers();
int PrintListProducts();
int PrintBalance();

#endif