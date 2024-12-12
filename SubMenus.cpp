#include "SubMenus.h"

/**
 * Select functions
 */
int select_submenu() {
    std::string raw_input{};
    while(1){
    std::cout << "Select\n"
                << "1) Customer\n"
                << "2) User\n"
                << "3) Component\n"
                << "4) Component Type\n"
                << "-> ";
        std::getline(std::cin, raw_input);
        int i = raw_input.at(0) - '0';
        switch(i) {
            case CUSTOMER:
                return CUSTOMER;
            case USER:
                return USER;
            case COMPONENT:
                return COMPONENT;
            case COMPONENT_TYPE:
                return COMPONENT_TYPE;
            default:
            // std::cout << "Invalid input\n";
        }
        return -1;  // error
    }

}


int select_customer(SqlDatabase& database){
         // Print short info about all customers and select one
        std::cout << "Select a customer. 0) to exit menu:\n";
        int customer { database.select_key("SELECT id, name FROM customer;") };
        return customer;
}

int select_user(SqlDatabase& database){
        // select customer
        int customer { select_customer(database) };
        int user{};
        // 0 to exit menu
        if (customer == 0) {
            user = 0;
        } else {
            // Select a user RFID connected to the customer
            std::cout << "Select a User RFID. 0) to exit menu:\n";
            std::string sql_get_users { "SELECT id, rfid FROM user "
                                        "INNER JOIN user_customer uc ON uc.user_id = user.id "
                                        "WHERE uc.customer_id = "        };
            sql_get_users += std::to_string(customer);
            sql_get_users += ";";
            user = database.select_key(sql_get_users);
        }
        return user;
}

/**
 *  Menu to add items to database
 */
void add_menu(SqlDatabase& database){
    std::string raw_input{};
    int menu_type { select_submenu() };
    
    if (menu_type == CUSTOMER) {

        database.add_customer( database.create_customer() );    

    } else if (menu_type == USER) {
        // 0 to exit menu
        int customer { select_customer(database) };
        {
            bool submenu{ customer > 0 };
            while (submenu) {
            std::cout << "Press + to add user, 0 when you are done -> ";  
            std::getline(std::cin, raw_input);
            char c2 = raw_input.at(0);
                switch (c2) {
                    case '+':
                        database.add_user( User::create_user(), customer );
                        break;
                    case '0':
                        submenu = false;
                        break;
                    default:
                }
            }
        }

    } else if (menu_type == COMPONENT) {
        // 0 to exit menu
        int customer { select_customer(database) };
        {
            bool submenu{ customer > 0 };
            while (submenu) {
            std::cout << "Press + to add component, 0 when you are done -> ";  
            std::getline(std::cin, raw_input);
            char c2 = raw_input.at(0);
                switch (c2) {
                    case '+':
                        database.add_component( database.create_component() ,customer );
                        break;
                    case '0':
                        submenu = false;
                        break;
                    default:
                }
            }
        }

    } else if (menu_type == COMPONENT_TYPE) {

        database.add_component_type( database.create_component_type() );    

    } else {

        std::cout << "Not a valid menu option\n";
    }
}

/** 
 * Menu to print info from the database
 */
void print_menu(SqlDatabase& database){
    std::string raw_input{};
    int menu_type { select_submenu() };
    
    if (menu_type == CUSTOMER) {
        
        int customer { select_customer(database) };
        // 0 to exit menu
        if (customer == 0) return;
        // Print detailed info about selected customer
        std::string sql { "SELECT  cu.name AS Customer, cu.address AS Address, ct.type_name AS Component, "
                          "co.location AS 'Install Location', co.serialnumber AS 'Serial Number' "
                          "FROM component co "
                          "INNER JOIN component_type ct ON ct.id = co.type_id "
                          "INNER JOIN component_customer cc ON cc.component_id = co.id "
                          "INNER JOIN customer cu ON cu.id = cc.customer_id "
                          "WHERE cc.customer_id = "};
        sql += std::to_string(customer);
        sql += ";";
        database.print(sql);
    
    } else if (menu_type == USER) {

        int user { select_user(database) };
        // 0 to exit menu
        if (user == 0) return;
        // Print detailed info about selected user
        std::string sql { "SELECT c.name AS Customer, u.rfid, u.pin, u.passphrase "
                          "FROM customer AS c, user AS u " 
                          "INNER JOIN user_customer AS uc ON uc.user_id = u.id AND uc.customer_id = c.id "
                          "WHERE u.id = "};
        sql += std::to_string(user);
        sql += ";";
        database.print(sql);

    } else if (menu_type == COMPONENT) {

        database.print(
            "SELECT ct.type_name as 'Component Type', "
            "c.location as 'Install Location', c.serialnumber as 'Serial Number' "
            "FROM component c "
            "INNER JOIN component_type ct ON ct.id = c.type_id;" );

    } else if (menu_type == COMPONENT_TYPE) {

        database.print("SELECT id, type_name AS 'Component Type' FROM component_type;");

    } else {
        std::cout << "Not a valid menu option\n";
    }
}

/**
 * Function for testing an installed alarm 
 */
void test_menu(SqlDatabase& database){
        
        std::string raw_input{};
        int user { select_user(database) };
        // 0 to exit menu
        if (user == 0) return;
        // get passphrase from database
        std::string sql { "SELECT passphrase FROM user WHERE user.id = " };
        sql += std::to_string(user);
        sql += ";";
        std::string passphrase { database.get_string_from_database(sql) } ;        
        
        // start test
        while (1) {
            std::cout << "Press y to test alarm, press n to abort -> ";
            raw_input = get_string();
            char c = raw_input.at(0);
            if (c == 'y') {
                break;
            } else if (c == 'n') {
                std::cout << "Test aborted\n";
                return;
            }
        }
        std::cout << "TEST ALARM STARTED\n";

        // end test
        while (1) {
            std::cout << "Pass phrase: " << passphrase << "\n"
                      << "Press y to confirm -> ";
            raw_input = get_string();
            char c = raw_input.at(0);
            if (c == 'y') {
                std::cout << "Pass phrase confirmed\n";
                break;
            }
        }
}

