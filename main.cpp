#include "SqlDatabase.h"
#include <iostream>

int main()
{
    ComponentType t {"Sensor"};
    SqlDatabase db("alarms.db");
    // db.add_component_type(t);
    // std::cout << db.get_last_inserted_rowid() << "\n";
    // db.print_component_types();
    // db.select_key("SELECT id, name FROM customer;");
    // db.create_component();
    User test_user { User::create_user() };
    db.add_user(test_user);
    // std::cout << hej.pin << " " << hej.rfid << " " << hej.passphrase << "\n";
    // std::set<int> valid_keys{};
    // db.get_valid_keys_with_print(valid_keys, "SELECT id, type_name FROM component_type;");
    // for (auto key : valid_keys) {
    //     std::cout << key << "\n";
    // }


    return 0;
}