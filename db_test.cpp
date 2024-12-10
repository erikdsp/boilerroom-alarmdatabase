#define CATCH_CONFIG_MAIN

#include "../include/catch.hpp"
#include "Database.h"

TEST_CASE("Create user"){
    {
        std::ofstream f("users.json");
        f << "[{\"id\":1,\"data\":{\"pin\":\"9876\",\"rfid\":\"omg\",\"passphrase\":\"o helga natt\"}}]";
        f.close();
        } // setup test
    JsonDatabase db;
    REQUIRE(db.get_users().size() == 1);
    User new_user {"1234", "rfid:1234","o helga katt"};
    REQUIRE_NOTHROW(db.add_user(new_user));
    std::map<unsigned, User> users;
    REQUIRE_NOTHROW(users = db.get_users());
    REQUIRE(users.at(2).pin == "1234");
}

TEST_CASE("Update user"){
    {
        std::ofstream f("users.json");
        f << "[{\"id\":1,\"data\":{\"pin\":\"9876\",\"rfid\":\"omg\",\"passphrase\":\"o helga natt\"}}]";
        f.close();
    } // setup test
    JsonDatabase db;
    REQUIRE_NOTHROW(db.get_user(1).pin == "9876");

}