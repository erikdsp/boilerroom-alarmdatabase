#include "nlohmann/json.hpp"
#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>

using json = nlohmann::ordered_json;

struct Customer {
    std::string name;
    std::string address;
    std::vector<unsigned> users;
    std::vector<Component> components;
};

struct User {
    std::string pin;
    std::string rfid;
    std::string passphrase;
};

struct Component {
    unsigned int type;
    std::string location;
    std::string serialnumber;
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

    return 0;
}




