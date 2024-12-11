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
        std::cout << success_message << std::endl;
    }
}


ComponentType SqlDatabase::create_component_type() {
    ComponentType temp;
    std::cout << "Please enter name of component type -> ";
    temp.type_name = get_string();
    return std::move(temp);
}

Component SqlDatabase::create_component(){
    Component temp;
    std::cout << "Available Component Types:\n";
    int component_type {select_key( "SELECT id, type_name FROM component_type;") };
    temp.type = component_type;
    std::cout << "Please enter the location -> ";
    temp.location = get_string();
    std::cout << "Please enter the serial number -> ";
    temp.serialnumber = get_string();
    return std::move(temp);
}


void SqlDatabase::add_component_type ( const ComponentType& ct){
    std::string sql = "INSERT INTO component_type (type_name) VALUES ('" + ct.type_name + "');";
    std::string message = "Component type " + ct.type_name + " added to database";
    execute_sql(sql, message);
}

 void SqlDatabase::add_component( const Component& c ){
    // select linked table in database
    std::cout << "Select a customer to add component:\n";
    int customer {select_key( "SELECT id, name FROM customer;") };

    // insert into component
    std::string sql = "INSERT INTO component (type_id, location, serialnumber) VALUES ('" 
                 + std::to_string(c.type) + "', '" + c.location + "', '" + c.serialnumber + "');";
    std::string message = "";
    execute_sql(sql, message);

    // insert into component_customer
    int component { get_last_inserted_rowid() };
    sql = "INSERT INTO component_customer (customer_id, component_id) VALUES ('"
            + std::to_string(customer) + "', '" + std::to_string(component) + "');";
    message = "Component added to database";
    execute_sql(sql, message);
 }

void SqlDatabase::add_user( const User& u ){
    // select linked table in database
    std::cout << "Select a customer to add user:\n";
    int customer {select_key( "SELECT id, name FROM customer;") };

    // insert into user
    std::string sql = "INSERT INTO user (pin, rfid, passphrase) VALUES ('" 
                 + u.pin + "', '" + u.rfid + "', '" + u.passphrase + "');";
    std::string message = "";
    execute_sql(sql, message);
    
    // insert into user_customer
    int user { get_last_inserted_rowid() };
    sql = "INSERT INTO user_customer (customer_id, user_id) VALUES ('"
            + std::to_string(customer) + "', '" + std::to_string(user) + "');";
    message = "User added to database";
    execute_sql(sql, message);
 }

void SqlDatabase::add_customer( const Customer& cu ){
    std::string sql = "INSERT INTO customer (name, address) VALUES ('" 
                 + cu.name + "', '" + cu.address + "');";
    std::string message = "Customer " + cu.name + " added to database";
    execute_sql(sql, message);
}


int SqlDatabase::select_key(const std::string& sql) {
    int input{};
    std::set<int> customer_keys;
    // example sql: SELECT id, name FROM customer;
    get_valid_keys_with_print(customer_keys, sql);
    // std::cout << "Available options:\n";
    std::cout << "Please select -> ";
    bool invalid{true};
    while (invalid) {
        input = get_number();
        if ((invalid = (customer_keys.count(input) == 0))) {
            std::cout << "Please select an option from the list or 0) to abort  -> ";
        }
    }
    return input;
}

int SqlDatabase::get_last_inserted_rowid(){
    std::string sql = "SELECT last_insert_rowid();";
    sqlite3_stmt* stmt = nullptr;
    int rowid{};
    if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(database) << "\n";
    } else {
        // read values for each row
        while (sqlite3_step(stmt) == SQLITE_ROW) {            
            rowid = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return rowid;
}

int SqlDatabase::print_callback(void *data, int argc, char **arg_value, char **az_col_name){
    std::cout << "--------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < argc; i++) {
        std::cout << az_col_name[i] << ": " << (arg_value[i] ? arg_value[i] : "NULL") << "\n";
    }
    // std::cout << "\n";
    return 0;
}

void SqlDatabase::print_component_types(){
    std::string sql = "SELECT * FROM component_type;";
    execute_sql_with_callback(sql, "");
}

void SqlDatabase::get_valid_keys_with_print(std::set<int>& keys, const std::string& sql){        
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(database) << "\n";
    } else {
        // read values for each row
        while (sqlite3_step(stmt) == SQLITE_ROW) {      
            // check that SQL query matches types INTEGER, TEXT
            if (sqlite3_column_type(stmt, 0) != SQLITE_INTEGER || sqlite3_column_type(stmt, 1) != SQLITE3_TEXT ) {
                std::cerr << "error, wrong SQL query to get_valid_keys_with_print\n";
                break;                
            }      
            int key = sqlite3_column_int(stmt, 0);
            const char* value_cstr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            // insert for caller to use
            keys.insert(key);
            // print
            std::cout << key << ") " << value_cstr << "\n";
        }
    }
    sqlite3_finalize(stmt);
}

/* 
void SqlDatabase::select_component_type() {
    std::set<int> keys;
    std::vector<std::map<int, std::string>> component_types;
    sqlite3_stmt* stmt = nullptr;
    std::string sql = "SELECT id, type_name FROM component_type;";

        if (sqlite3_prepare_v2(database, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(database) << "\n";
            sqlite3_finalize(stmt);
        } else {
            while (sqlite3_step(stmt) == SQLITE_ROW) {            
                std::map<int, std::string> row;
                int key = sqlite3_column_int(stmt, 0);
                keys.insert(key);
                const char* p_to_value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
                std::string value { (p_to_value != NULL) ? p_to_value : "null" };
                row.insert({key, value});
                component_types.push_back(row);
            }
        sqlite3_finalize(stmt);
        // std::cout << keys.count(4) << "\n";
        // std::cout << "CT1: " << component_types.size() << "\n";
    }
}
 */

// Select data within a time range
/* 
bool select_time_range(sqlite3* db, vector<map<string, int>>& time_ref, const string& start_time, const string& end_time) {
    sqlite3_stmt* stmt = nullptr;
    string sql = "SELECT * FROM EventLog WHERE event_time >= '" + start_time + "' AND event_time <= '" + end_time + "';";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            map<string, int> row;
            const char* time_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            int value = sqlite3_column_int(stmt, 2);

            row[time_text] = value;
            time_ref.push_back(row);
        }
        sqlite3_finalize(stmt);
        return true;
    }
    sqlite3_finalize(stmt);
    return false;
}
 */