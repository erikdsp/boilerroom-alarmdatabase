#include "nlohmann/json.hpp"
#include "Database.h"
#include "main_menu.h"
#include "User.h"
#include "structs.h"
#include "create_component.h"
#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>

// using json = nlohmann::ordered_json;



int main() 
{
    std::map<unsigned, Customer> companies;
    std::map<unsigned, Component> components;
    std::map<unsigned, User> users;  
    std::map<unsigned, ComponentType> component_types;
    
    main_menu();    


    return 0;
}



