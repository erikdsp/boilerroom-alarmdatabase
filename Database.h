#ifndef CHAS_BOILER_ALARM_DATABASE_H
#define CHAS_BOILER_ALARM_DATABASE_H

#include <map>
#include <numeric>
#include "nlohmann/json.hpp"
#include "User.h"
#include "structs.h"

using json = nlohmann::json;
/*
UserDatabase udb;
CustomerDatabase cdb;
ComponentDatabase compdb;

Database db; <-- insert name, pin, loc into users;

register_user();
enter username: dfgjdfjklsd
User{dfgjdfjklsd} >> db;


*/





class JsonDatabase{
    private: 
    std::string UserDatabase {"users.json"};
    std::string CustomerDatabase {"customers.json"};
    std::string ComponentDatabase {"components.json"}; 

    json& load_file(std::string);
    void save_file(std::string, const json& out);

    public:
    JsonDatabase();

    void add_user ( User& );
    void add_component_type ( ComponentType& );
    void add_customer ( Customer& );

    const std::map<unsigned, User>get_users() const;
    const User& get_user(unsigned id) const;

    const std::vector<unsigned> get_component_types();
    const ComponentType& get_component_type(unsigned id);

    const User& update_user( unsigned id, User updated_user );
};

JsonDatabase::JsonDatabase(){
    
};

json& JsonDatabase::load_file(std::string file_name){
    json records;

    std::ifstream in_file;
    in_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try{
        in_file.open(UserDatabase);
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    in_file >> records;

    in_file.close();

    return records;
}

void save_file( std::string file_name, const json& out ){
        std::ofstream out_file;
    out_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try{
        out_file.open(file_name);
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    out >> out_file;

    out_file.close();

}

void JsonDatabase::add_user( User& new_user ){  
    json records {load_file(UserDatabase)};
    int id {1};
    id = std::max(id, records.back()["id"]+1);

    records.push_back({
        "id", id,
        "data", 
            "pin", new_user.pin,
            "rfid", new_user.rfid,
            "passphrase", new_user.passphrase
    });

    save_file(UserDatabase, records);
}

void JsonDatabase::add_component_type( ComponentType& new_component_type ){
    json records {load_file(ComponentDatabase)};
    int id {1};
    id = std::max(id, records.back()["id"]+1);

    records.push_back({
        "id", id,
        "type_name", new_component_type.type_name
    });

    save_file(ComponentDatabase, records);
}

void JsonDatabase::add_customer( Customer& new_customer ){  
    json records {load_file(CustomerDatabase)};
    int id {1};
    id = std::max(id, records.back()["id"]+1);


    records.push_back({
        "id", id,
        "data", 
            "name", new_customer.name,
            "address", new_customer.address,
            "users", new_customer.users,
            "components", new_customer.components
    });

    save_file(CustomerDatabase, records);
}

const std::vector<unsigned> JsonDatabase::get_component_types(){
    json records = load_file(ComponentDatabase);
    std::vector<unsigned> ids {};

    for (const auto & r : records){
        ids.push_back(r["id"].get<unsigned>());
    }
    std::sort(ids.begin(), ids.end());

    return ids;
}

#endif