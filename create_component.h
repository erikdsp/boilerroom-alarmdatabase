#ifndef CREATE_COMPONENT_H
#define CREATE_COMPONENT_H
#include "User.h"
#include "structs.h"
#include <regex>

Component create_component();
ComponentType create_component_type();

int get_number();
unsigned get_unsigned_number();
std::string get_string();
bool is_int(const std::string &str);
bool is_unsigned_int(const std::string &str);

#endif