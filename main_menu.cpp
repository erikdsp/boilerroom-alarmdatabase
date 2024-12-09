#include "main_menu.h"



int submenu_types() {
    std::string raw_input{};
    while(1){
    std::cout << "Select\n"
                << "1) component\n"
                << "2) component type\n"
                << "3) customer\n"
                << "-> ";
        std::getline(std::cin, raw_input);
        char c = raw_input.at(0);
        switch(c) {
            case '1':
                return CUSTOMER;
            case '2':
                return USER;
            case '3':
                return COMPONENT;
            case '4':
                return COMPONENT_TYPE;
            default:
            std::cout << "Invalid input\n";
        }
        return -1;  // error
    }

}

void main_menu()
{


    std::string raw_input{};
    while(1)
    {
        std::cout << "Press a to add, p to print, u to update, r to remove, q to quit -> ";        
        std::getline(std::cin, raw_input);
        char c = raw_input.at(0);
        switch(c)
        {
            case 'a':
                int menu_type { submenu_types() };
                switch(menu_type){
                    case CUSTOMER:
                        break;
                    case USER:
                        break;
                    case COMPONENT:
                        break;
                    case COMPONENT_TYPE:
                        break;
                    default:
                }
                break;
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
