#ifndef CUSTOMERS_H
#define CUSTOMERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"


static void ShowCostumersMenu();
static int ShowCostumersSubMenu();
static int PrintFindCostumers();
static int PrintListProducts();
static int PrintBalance();

#endif