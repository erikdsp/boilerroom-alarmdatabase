#include "nlohmann/json.hpp"
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

struct User {
    std::string pin;
    std::string rfid;
    std::string passphrase;
};

struct ProductType {
    std::string type_name;
};

User create_user();

int main() 
{
    std::map<unsigned, Customer> companies;
    std::map<unsigned, Component> components;
    std::map<unsigned, User> users;  
    std::map<unsigned, ProductType> product_type;
    
    // Tests for create_user()
    // users.insert({{1}, create_user()});
    // std::cout << users.at(1).pin;

    return 0;
}

User create_user()
{
    User temp_user;
    
    std::cout << "\nPlease enter desired pin:";
    std::getline(std::cin, temp_user.pin);
    std::cout << "\nPlease enter desired rfid:";
    std::getline(std::cin, temp_user.rfid);
    std::cout << "\nPlease enter desired passphrase:";
    std::getline(std::cin, temp_user.passphrase);

    return temp_user;
}




