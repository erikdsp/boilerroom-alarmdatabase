#ifndef CHAS_BOILER_ALARM_SQL_DATABASE_H
#define CHAS_BOILER_ALARM_SQL_DATABASE_H

#include <map>
#include <numeric>
#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include "nlohmann/json.hpp"
#include "User.h"
#include "structs.h"


class SqlDatabase{
    private: 
    sqlite3* database;
    void initialize_empty_database();
    void execute_sql(const std::string& sql, const std::string& success_message = "");
    void execute_sql_with_callback(const std::string& sql, const std::string& success_message = "");
    static int print_callback(void *data, int argc, char **arg_value, char **az_col_name);

    public:
    SqlDatabase(const char* db_name);
    ~SqlDatabase();

    // void add_user ( User& );
    void add_component_type ( ComponentType& ct);
    void print_component_types();
    // void add_customer ( Customer& );

    // const Customer register_user_to_customer( unsigned user_id, unsigned customer_id ) const;
    
    // const std::map<unsigned, User>get_users() const;
    // const User get_user(unsigned id) const;

    // const std::vector<unsigned> get_component_types();
    // const ComponentType get_component_type(unsigned id);

    // const User update_user( unsigned id, User updated_user );


};

#endif