#include <fstream>
#include <cctype>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <numeric>

class User {
public:
    std::string pin;
    std::string rfid;
    std::string passphrase;
    static User create_user();
};
 
User User::create_user(){

    std::srand(time(NULL));
    User temp_user;
    int temp_random_number{};

    // Randomizes an rfid (starting from 1000000), room for improvement here.
    temp_random_number = 100000000000 + std::rand() % (RAND_MAX);
    temp_user.rfid = std::to_string(temp_random_number); 
        
    // Loop until correct size (4) of type string is entered.
    do{
        std::cout << "\nPlease enter desired pin: ";
        std::getline(std::cin, temp_user.pin);
            if(temp_user.pin.size() != 4)
            {
                std::cout << "Invalid PIN\nExpected format: [XXXX]";
            }
            else
                std::cout << "-Valid PIN-";
    } while(temp_user.pin.size() != 4);
    
    std::cout << "\nRFID: " << temp_user.rfid; 
    std::cout << "\nEnter desired passphrase: ";
    std::getline(std::cin, temp_user.passphrase);

    return temp_user;
}