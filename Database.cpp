#include "Database.h"


void to_json( json& j, const Component& c ){
    j = json{
        "type", c.type,
        "location", c.location,
        "serialnumber", c.serialnumber
    };
}

void to_json( json& j, const Customer& cus ){
    j = json{
        "name", cus.name,
        "address", cus.address,
        "users", cus.users,
        "components", cus.components
    };
}

void to_json( json& j, const User& u ){
    j = json{
        "pin", u.pin,
        "rfid", u.rfid,
        "passphrase", u.passphrase
    };
}

void from_json( json& j, ComponentType& c_t ){
    // j.at("type_name").get_to(c_t.type_name);
}

void from_json( json& j, Customer& cus ){
    // j.at("name").get_to(cus.name);
    // j.at("address").get_to(cus.address);
    // j.at("users").get_to(cus.users);
    // for (const auto& comp : j.at("components")){
    //     cus.components.push_back(Component{comp});
    // }
}

void from_json( json& j, User& u ){
    // j.at("pin").get_to(u.pin);
    // j.at("rfid").get_to(u.rfid);
    // j.at("passphrase").get_to(u.passphrase);
}

json JsonDatabase::load_file(std::string file_name) const{
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

void JsonDatabase::save_file( std::string file_name, const json& out ) const{
    std::ofstream out_file;
    out_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try{
        out_file.open(file_name);
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    // out >> out_file;
    out_file << out;

    out_file.close();

}

void JsonDatabase::add_user( User& new_user ){  
    json records {load_file(UserDatabase)};
    int id {1};
    int db_id {records.back()["id"]};
    id = std::max(id, db_id+1);

    records.push_back({
        "id", id,
        "data", new_user
    });

    save_file(UserDatabase, records);
}

void JsonDatabase::add_component_type( ComponentType& new_component_type ){
    json records {load_file(ComponentDatabase)};
    int id {1};
    int db_id { records.back()["id"] };
    id = std::max(id, db_id+1);

    records.push_back({
        "id", id,
        "type_name", new_component_type.type_name
    });

    save_file(ComponentDatabase, records);
}

void JsonDatabase::add_customer( Customer& new_customer ){  
    json records {load_file(CustomerDatabase)};
    int id {1};
    int db_id {records.back()["id"]};
    id = std::max(id, db_id+1);

    std::vector<unsigned> ;

    records.push_back({
        "id", id,
        "data", 
            new_customer
    });

    save_file(CustomerDatabase, records);
}

const Customer& JsonDatabase::register_user_to_customer(unsigned user_id, unsigned customer_id ) const {
    json records = load_file(CustomerDatabase);
    records.at(customer_id)["data"]["users"].push_back(user_id);
    save_file(CustomerDatabase, records);

    records = load_file(CustomerDatabase);
    return Customer{records.at(customer_id)};
}

const std::map<unsigned, User> JsonDatabase::get_users() const{
    json records = load_file(UserDatabase);
    std::map<unsigned, User> users;

    for ( const auto & row : records ){
        users.insert({{row["id"]}, {row["data"]} });
    }

    return users;
}

const User& JsonDatabase::get_user(unsigned id) const{
    json records = load_file(UserDatabase);

    return User {records.at(id)};
}

const std::vector<unsigned> JsonDatabase::get_component_types(){
    json records = load_file(ComponentDatabase);
    std::vector<unsigned> ids {};

    // for (const auto & r : records){
    //     ids.push_back(r["id"].get<unsigned int>());
    // }
    // std::sort(ids.begin(), ids.end());

    return ids;
}

const User& JsonDatabase::update_user( unsigned id, User updated_user){
    json records = load_file(UserDatabase);
    records.at(id) = updated_user;

    save_file(UserDatabase, records);

    records = load_file(UserDatabase);

    return User {records.at(id)};
}