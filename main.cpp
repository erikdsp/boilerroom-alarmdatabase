#include "SqlDatabase.h"
#include <iostream>

int main()
{
    // ComponentType t {"Sensor"};
    SqlDatabase db("alarms.db");
    // db.add_component_type(t);
    // db.print_component_types();
    std::set<int> valid_keys{};
    db.get_valid_keys_with_print(valid_keys, "SELECT id, type_name FROM component_type;");
    for (auto key : valid_keys) {
        std::cout << key << "\n";
    }


    return 0;
}