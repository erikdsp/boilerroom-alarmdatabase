#include "SubMenus.h"



int submenu_types() {
    std::string raw_input{};
    while(1){
    std::cout << "Select\n"
                << "1) Customer\n"
                << "2) User\n"
                << "3) Component Type\n"
                << "-> ";
        std::getline(std::cin, raw_input);
        char c = raw_input.at(0);
        switch(c) {
            case '1':
                return CUSTOMER;
            case '2':
                return USER;
            case '3':
                return COMPONENT_TYPE;
            default:
            std::cout << "Invalid input\n";
        }
        return -1;  // error
    }

}

void main_menu(const char* filename)
{
    SqlDatabase database(filename);

    std::string raw_input{};
    while(1)
    {
        std::cout << "Press a to add, p to print, u to update, r to remove, t to test alarm, q to quit -> ";        
        std::getline(std::cin, raw_input);
        char c = raw_input.at(0);
        switch(c)
        {
            case 'a':
            {                        
                add_menu(database);
                break;
                }
            case 'p':
                print_menu(database);
                break;
            case 'u':
                std::cout << "Update menu awaiting implementation\n";
                break;
            case 'r':
                std::cout << "Remove menu awaiting implementation\n";
                break;
            case 't':
                test_menu(database);
                break;
            case 'q':
                return;
                // return 0;
            default:
            ;
        }
    }
    // return 0;
}

void add_menu(SqlDatabase& database){
    std::string raw_input{};
    int menu_type { submenu_types() };
    
    if (menu_type == CUSTOMER) {
        Customer temp_customer;   
        std::cout << "Create customer. (awaiting implementation)\n";
        std::cout << "Add customer. (awaiting implementation)\n";
        // database.add_customer();
    
    } else if (menu_type == USER) {
        User temp_user;
        std::cout << "Create user. (awaiting implementation)\n";
        {
            bool submenu{true};
            while (submenu) {
            std::cout << "Press + to add component, 0 when you are done -> ";  
            std::getline(std::cin, raw_input);
            char c2 = raw_input.at(0);
                switch (c2) {
                    case '+':
                        database.create_component();
                        break;
                    case '0':
                        submenu = false;
                        break;
                    default:
                }
            }

        }
        std::cout << "Add user. (awaiting implementation)\n";
        // database.add_user();
    
    } else if (menu_type == COMPONENT_TYPE) {
        // ComponentType temp_comp_type;
        ComponentType test = database.create_component_type();
        std::cout << "Add component type. (awaiting implementation)\n";
        // database.add_component_type(temp_comp_type = create_component_type());             
    
    } else {
        std::cout << "Not a valid menu option\n";
    }
}



void print_menu(SqlDatabase& database){
    std::string raw_input{};
    int menu_type { submenu_types() };
    
    if (menu_type == CUSTOMER) {
        std::cout << "Print customers. (awaiting implementation)\n";
        std::cout << "Select customer to print detailed information or press 0) to exit -> ";
        int customer_id { get_number() };
        std::cout << "Print customer no " << customer_id << ". (awaiting implementation)\n";
    
    } else if (menu_type == USER) {
        User temp_user;
        std::cout << "Get users. (awaiting implementation)\n";
        std::cout << "Select user (1-5) -> ";
        int user_id { get_number(1, 5) };
        std::cout << "Print user no " << user_id << ". (awaiting implementation)\n";
    
    } else if (menu_type == COMPONENT_TYPE) {
        std::cout << "Get component types. (awaiting implementation)\n";
        std::cout << "Print component types. (awaiting implementation)\n";
        std::cout << "Test printing: " << database.get_last_inserted_rowid() << "\n";
    
    } else {
        std::cout << "Not a valid menu option\n";
    }
}


void test_menu(SqlDatabase& database){
        std::string raw_input{};
        
        User temp_user;
        std::cout << "Get users. (awaiting implementation)\n";
        std::cout << "Select user (1-5) -> ";
        int user_id { get_number(1, 5) };
        std::cout << "Print user no " << user_id << ". (awaiting implementation)\n";
        std::cout << "Test alarm started. \n";
        while (1) {
            std::cout << "Pass phrase: " << temp_user.passphrase << "\n"
                      << "Press y to confirm -> ";
            raw_input = get_string();
            char c = raw_input.at(0);
            if (c == 'y') {
                std::cout << "Pass phrase confirmed\n";
                break;
            }
        }
}