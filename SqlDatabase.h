#ifndef CHAS_BOILER_ALARM_SQL_DATABASE_H
#define CHAS_BOILER_ALARM_SQL_DATABASE_H

#include "User.h"
#include "structs.h"
#include "input.h"
#include <map>
#include <numeric>
#include <iostream>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>
#include <set>


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

    ComponentType create_component_type();
    Component create_component();
    void add_component_type ( const ComponentType& ct);
    void add_component( const Component& c );
    void add_user( const User& u );
    void add_customer( const Customer& cu );
    int select_key( const std::string& sql );
    int get_last_inserted_rowid();
    void print(const std::string& sql);
    std::string get_string_from_database(const std::string& sql);
    // @param keys for keys from query, @param sql - syntax example: SELECT id, <parameter> FROM <table>
    void get_valid_keys_with_print(std::set<int>& keys, const std::string& sql);

};

#endif