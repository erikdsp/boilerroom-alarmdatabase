#include "SqlDatabase.h"
#include "SubMenus.h"
#include <iostream>

int main()
{
    SqlDatabase database("alarms.db");
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
                return 0;
            default:
            ;
        }
    }



    return 0;
}