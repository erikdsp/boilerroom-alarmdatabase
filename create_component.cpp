#include "create_component.h"

Component create_component(){
    Component temp;
    std::cout << "Please enter the component type (unsigned number) -> ";
    temp.type = get_unsigned_number();
    std::cout << "Please enter the location -> ";
    temp.location = get_string();
    std::cout << "Please enter the serial number -> ";
    temp.serialnumber = get_string();
    return std::move(temp);
}


ComponentType create_component_type() {
    ComponentType temp;
    std::cout << "Please enter name of component type -> ";
    temp.type_name = get_string();
    return std::move(temp);
}



