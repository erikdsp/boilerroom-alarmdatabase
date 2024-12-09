#ifndef DATABASE_MAIN_MENU_H
#define DATABASE_MAIN_MENU_H
#include "User.h"
#include "structs.h"
#include "create_component.h"

enum menu_type {
    CUSTOMER = 1,
    USER,
    COMPONENT,
    COMPONENT_TYPE
};

int submenu_types();
void main_menu();


#endif