#ifndef ORDERS_H
#define ORDERS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "products.h"


static void ShowOrdersMenu();
static int ShowOrdersSubMenu();
static int PrintOpen();
static int PrintRange();
static int PrintDetail();

#endif