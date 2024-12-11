#include "SqlDatabase.h"



SqlDatabase::SqlDatabase(const char* db_name){
    std::cout << "Constructor called\n";
    bool file_exists = std::filesystem::exists(db_name);
    int read_err = sqlite3_open(db_name, &database);
    if (read_err) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(database) << std::endl;
    } else {
        if (file_exists){
            std::cout << "Opened database successfully" << std::endl;
        }
        else {
            initialize_empty_database();            
        }
    }
}


SqlDatabase::~SqlDatabase(){
    std::cout << "Destructor called\n";
    sqlite3_close(database);
}

void SqlDatabase::initialize_empty_database(){
    // read SQL from file
    std::ifstream input;
    std::string sql{};
    std::string line;
    try {
        input.open("init_alarm_database.sql");
        while (input.peek() != EOF){
            std::getline(input, line);
            sql += line;
        }
        input.close();
    } catch (std::exception e) {
        std::cerr << e.what() << "\n";
    }

    execute_sql(sql, "Database initialized successfully");

}


void SqlDatabase::execute_sql(const std::string& sql, const std::string& success_message){
    char* errMsg = 0;
    int rc = sqlite3_exec(database, sql.c_str(), nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << success_message << std::endl;
    }
}

void SqlDatabase::execute_sql_with_callback(const std::string& sql, const std::string& success_message){
    char* errMsg = 0;
    int rc = sqlite3_exec(database, sql.c_str(), print_callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << success_message;
    }
}

void SqlDatabase::add_component_type ( ComponentType& ct){
    std::string sql = "INSERT INTO component_type (type_name) VALUES ('" + ct.type_name + "');";
    std::string message = "Component type " + ct.type_name + " added to database";
    execute_sql(sql, message);
}


int SqlDatabase::print_callback(void *data, int argc, char **arg_value, char **az_col_name){
    std::cout << "--------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < argc; i++) {
        std::cout << az_col_name[i] << ": " << (arg_value[i] ? arg_value[i] : "NULL") << "\n";
    }
    return 0;
}

void SqlDatabase::print_component_types(){
    std::string sql = "SELECT * FROM component_type;";
    execute_sql_with_callback(sql);
    std::cout << "--------------------------------------------------------------------------------------------\n";
}