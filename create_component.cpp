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



// function to get a number using getline
int get_number()
{
    while (1)
    {
        std::string raw_in{ get_string() };

        if (is_int(raw_in)) return stoi(raw_in);
        else std::cout << "Invalid input. Please enter a number -> ";
    }
    return -1;  // error
}

// function to get a number using getline
unsigned get_unsigned_number()
{
    while (1)
    {
        std::string raw_in{ get_string() };

        if (is_unsigned_int(raw_in)) return static_cast<unsigned>(stoi(raw_in));
        else std::cout << "Invalid input. Please enter an unsigned number -> ";
    }
    return -1;  // error
}

// function to get at string using getline
std::string get_string()
{
    std::string temp;
    std::getline(std::cin, temp);
    return std::move(temp);
}

bool is_int(const std::string &str) {
    std::regex e(R"(^[-+]?\d+$)"); // Regular expression pattern for integers
    return std::regex_match(str, e); // Match the entire string against the regex
}

bool is_unsigned_int(const std::string &str) {
    std::regex e(R"(^\d+$)"); // Regular expression pattern for unsigned integers
    return std::regex_match(str, e); // Match the entire string against the regex
}