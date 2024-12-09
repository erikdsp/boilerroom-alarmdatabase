#ifndef DATABASE_MAIN_MENU_H
#define DATABASE_MAIN_MENU_H
#include "User.h"
#include "structs.h"
#include "create_component.h"
#include "Database.h"

enum menu_type {
    CUSTOMER = 1,
    USER,
    COMPONENT_TYPE
};

int submenu_types();
void main_menu();
void add_menu(JsonDatabase& database, ComponentType& test);
void print_menu(JsonDatabase& database, ComponentType& test);

#endif