#include "nlohmann/json.hpp"
#include "User.h"
#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>

using json = nlohmann::ordered_json;

struct Component {
    unsigned int type;
    std::string location;
    std::string serialnumber;
};

struct Customer {
    std::string name;
    std::string address;
    std::vector<unsigned> users;
    std::vector<Component> components;
};


struct ComponentType {
    std::string type_name;
};



int main() 
{
    std::map<unsigned, Customer> companies;
    std::map<unsigned, Component> components;
    std::map<unsigned, User> users;  
    std::map<unsigned, ComponentType> component_type;
    
    // Tests for create_user()
    // users.insert({{1}, User::create_user()});
    // std::cout << users.at(1).pin;
    return 0;
}



