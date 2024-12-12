#ifndef CHAS_BOILER_ALARM_INPUT_H
#define CHAS_BOILER_ALARM_INPUT_H

#include <string>
#include <iostream>
#include <regex>


/**
 * All input functions use std::getline
 */
int get_number();
int get_number(int min, int max);
unsigned get_unsigned_number();
std::string get_string();
bool is_int(const std::string &str);
bool is_unsigned_int(const std::string &str);

#endif