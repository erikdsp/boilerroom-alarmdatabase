#include "Database.h"


void to_json( json& j, const Component& c ){
    j = json{
        {"type", c.type},
        {"location", c.location},
        {"serialnumber", c.serialnumber}
    };
}

void to_json( json& j, const Customer& cus ){
    j = json{
        {"name", cus.name},
        {"address", cus.address},
        {"users", cus.users},
        {"components", cus.components}
    };
}

void to_json( json& j, const User& u ){
    j = json{
        {"pin", u.pin},
        {"rfid", u.rfid},
        {"passphrase", u.passphrase}
    };
}

void from_json( json& j, ComponentType& c_t ){
    j.at("type_name").get_to(c_t.type_name);
}

void from_json( json& j, Customer& cus ){
    j.at("name").get_to(cus.name);
    j.at("address").get_to(cus.address);
    j.at("users").get_to(cus.users);
    for (const auto& comp : j.at("components")){
        cus.components.push_back(Component{comp});
    }
}

void from_json( json& j, User& u ){
    j.at("pin").get_to(u.pin);
    j.at("rfid").get_to(u.rfid);
    j.at("passphrase").get_to(u.passphrase);
}

void JsonDatabase::load_file(std::string file_name, json& to) const{

    std::ifstream in_file;
    in_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try{
        in_file.open(UserDatabase);
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    in_file >> to;

    in_file.close();

}

void JsonDatabase::save_file( std::string file_name, const json& out ) const{
    std::ofstream out_file;
    out_file.exceptions(std::ofstream::badbit | std::ofstream::failbit);
    try{
        out_file.open(file_name);
    } catch (const std::exception& e){
        std::cerr << e.what() << '\n';
    }

    out_file << out;

    out_file.close();
}

void JsonDatabase::add_user( User& new_user ){  
    json records;
    load_file(UserDatabase, records);
    int id {1};
    int prev{records.back().back().get<int>()};

    id = std::max(id, prev+1);

    json user_data{
        {"id", id},
        {"data", new_user}
    };
    records.push_back(user_data);

    save_file(UserDatabase, records);
}

void JsonDatabase::add_component_type( ComponentType& new_component_type ){
    json records;
    load_file(ComponentDatabase, records);
    int id {1};
    id = std::max(id, records.back()["id"].get<int>()+1);

    records.push_back({
        "id", id,
        "type_name", new_component_type.type_name
    });

    save_file(ComponentDatabase, records);
}

void JsonDatabase::add_customer( Customer& new_customer ){  
    json records;
    load_file(CustomerDatabase, records);
    int id {1};
    id = std::max(id, records.back()["id"].get<int>()+1);

    records.push_back({
        "id", id,
        "data", 
            new_customer
    });

    save_file(CustomerDatabase, records);
}

const Customer JsonDatabase::register_user_to_customer(unsigned user_id, unsigned customer_id ) const {
    json records;
    load_file(CustomerDatabase, records);
    records.at(customer_id)["data"]["users"].push_back(user_id);
    save_file(CustomerDatabase, records);

    load_file(CustomerDatabase, records);
    return Customer{records.at(customer_id)};
}

const std::map<unsigned, User> JsonDatabase::get_users() const{
    json records;
    load_file(UserDatabase, records);
    std::map<unsigned, User> users;

    for ( auto & row : records ){
        User u {row["data"]["pin"], row["data"]["rfid"], row["data"]["passphrase"]};
        unsigned user_id = {row.value("id", 0U)};
        users.emplace(user_id, u);
    }

    return users;
}

const User JsonDatabase::get_user(unsigned id) const{
    json records;
    load_file(UserDatabase, records);

    return User {records.at(id)};
}

const std::vector<unsigned> JsonDatabase::get_component_types(){
    json records;
    load_file(ComponentDatabase, records);
    std::vector<unsigned> ids {};

    for (const auto & r : records){
        ids.push_back(r["id"].get<unsigned>());
    }
    std::sort(ids.begin(), ids.end());

    return ids;
}

const User JsonDatabase::update_user( unsigned id, User updated_user){
    json records;
    load_file(UserDatabase, records);
    records.at(id) = updated_user;

    save_file(UserDatabase, records);

    load_file(UserDatabase, records);

    return User {records.at(id)};
}