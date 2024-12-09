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
    User new_user {"1234", "rfid:1234","o helga katt"};
    REQUIRE_NOTHROW(db.add_user(new_user));
    REQUIRE(db.get_users().size() == 2);
}