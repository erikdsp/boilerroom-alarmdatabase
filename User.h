#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

class User {
public:
    std::string pin;
    int rfid;
    std::string passphrase;
    static User create_user();
};
 
User User::create_user(){

    std::srand(time(NULL));
    User temp_user;

    // Randomizes an rfid (starting from 1000000), room for improvement here.
    temp_user.rfid = 1000000 + std::rand() % (10000000);
    
    // Loop until correct size (4) of type string is entered.
    do{
        std::cout << "\nPlease enter desired pin: ";
        std::getline(std::cin,temp_user.pin);
            if(temp_user.pin.size() != 4)
            {
                std::cout << "Invalid PIN\nExpected format: [XXXX]";
            }
            else
                std::cout << "-Valid PIN-";
    } while(temp_user.pin.size() != 4);

    std::cout << "\nRFID: " << temp_user.rfid; 
    std::cout << "\nPlease enter desired passphrase: ";
    std::getline(std::cin, temp_user.passphrase);

    return temp_user;
}