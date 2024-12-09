#ifndef DATABASE_STRUCTS_H
#define DATABASE_STRUCTS_H

#include <vector>
#include <string>

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

#endif