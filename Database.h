#ifndef CHAS_BOILER_ALARM_DATABASE_H
#define CHAS_BOILER_ALARM_DATABASE_H

#include <map>
#include <numeric>
#include <algorithm>
#include "nlohmann/json.hpp"
#include "User.h"
#include "structs.h"

using json = nlohmann::json;

class JsonDatabase{
    private: 
    std::string UserDatabase {"users.json"};
    std::string CustomerDatabase {"customers.json"};
    std::string ComponentDatabase {"components.json"}; 

    json load_file(std::string) const;
    void save_file(std::string, const json& out) const;

    public:

    void add_user ( User& );
    void add_component_type ( ComponentType& );
    void add_customer ( Customer& );

    const Customer& register_user_to_customer( unsigned user_id, unsigned customer_id ) const;
    
    const std::map<unsigned, User>get_users() const;
    const User& get_user(unsigned id) const;

    const std::vector<unsigned> get_component_types();
    const ComponentType& get_component_type(unsigned id);

    const User& update_user( unsigned id, User updated_user );


};

#endif