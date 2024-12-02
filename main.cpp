#include "nlohmann/json.hpp"
#include <fstream>
#include <cctype>
#include <iostream>
using json = nlohmann::ordered_json;

struct Contact {
    int id;
    std::string first_name;
    std::string last_name;
    int birth_year;
    std::string email;
    std::string phone;
};


int main() 
{

    return 0;
}




