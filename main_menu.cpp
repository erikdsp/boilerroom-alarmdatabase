#include "main_menu.h"



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

void main_menu()
{
    JsonDatabase database;

    std::string raw_input{};
    while(1)
    {
        std::cout << "Press a to add, p to print, u to update, r to remove, q to quit -> ";        
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
                // readContacts(db);
                break;
            case 'u':
                // updateContact(db);
                break;
            case 'r':
                // removeContact(db);
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

void add_menu(JsonDatabase& database){
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
                        create_component();
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
        ComponentType temp_comp_type;
        create_component_type();
        std::cout << "Add component type. (awaiting implementation)\n";
        // database.add_component_type(temp_comp_type = create_component_type());             
    } else {
        std::cout << "Not a valid menu option\n";
    }
}
