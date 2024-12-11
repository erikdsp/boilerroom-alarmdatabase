#include "create_component.h"




ComponentType create_component_type() {
    ComponentType temp;
    std::cout << "Please enter name of component type -> ";
    temp.type_name = get_string();
    return std::move(temp);
}


Customer create_customer() {
    Customer temp;
    std::cout << "Please enter name -> ";
    temp.name = get_string();
    std::cout << "Please enter address -> ";
    temp.address = get_string();
    return std::move(temp);
}


