#include "SqlDatabase.h"
#include <iostream>

int main()
{
    ComponentType t {"Sensor"};
    SqlDatabase db("test2.db");
    // db.add_component_type(t);
    db.print_component_types();

    return 0;
}