#ifndef DATABASE_SUB_MENUS_H
#define DATABASE_SUB_MENUS_H
#include "User.h"
#include "structs.h"
#include "input.h"
#include "SqlDatabase.h"

enum menu_type {
    CUSTOMER = 1,
    USER,
    COMPONENT_TYPE
};

int submenu_types();
void main_menu(const char* filename);
void add_menu(SqlDatabase& database);
void print_menu(SqlDatabase& database);
void test_menu(SqlDatabase& database);

#endif