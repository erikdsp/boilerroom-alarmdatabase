#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>

class User {
public:
    std::string pin;
    std::string rfid;
    std::string passphrase;
    static User create_user();
};
/* 
User User::create_user(){

    User temp_user;
    
    std::cout << "\nPlease enter desired pin:";
    std::getline(std::cin, temp_user.pin);
    std::cout << "\nPlease enter desired rfid:";
    std::getline(std::cin, temp_user.rfid);
    std::cout << "\nPlease enter desired passphrase:";
    std::getline(std::cin, temp_user.passphrase);

    return temp_user;
}
*/