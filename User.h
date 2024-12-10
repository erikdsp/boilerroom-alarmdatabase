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
 
