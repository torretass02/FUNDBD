#ifndef ORDERS_H
#define ORDERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

void ShowOrdersMenu();
int ShowOrdersSubMenu();
int PrintOpen();
int PrintRange();
int PrintDetail();

#endif