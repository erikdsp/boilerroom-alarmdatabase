#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "structs.h"

/* NAMESPACE::INPUT
USAGE GUIDE:
Usage illustration on how to use namespace::input can be seen below.
Q: Why?
A: This should be much easier to implement error-checking or bounds-checking in the future.
*/
namespace input
{
    static int get(int& value, const std::string& prompt)
    {
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore();
        return value;
    }

    static double get(double& value, const std::string& prompt)
    {
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore();
        return value;
    }

    static uint32_t get(uint32_t& value, const std::string& prompt)
    {
        std::cout << prompt;
        std::cin >> value;
        return value;
    }

    static std::string get(const std::string& prompt)
    {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        return value;
    }
};

/* NAMESPACE::CUSTOMER
USAGE GUIDE:
All functions included and visible at declaration.
Q: What is "runs"? 
A: Number of test customers you want to simulate.
Q: Namespace? 
A: Avoids potential naming conflicts as well as provides a "rudimentary" interface for all included functionality.
*/
namespace customer
{
    void customer_print(std::map<uint32_t, Customer>& companies);
    void customer_create(std::map<uint32_t, Customer>& companies);
    void customer_delete(std::map<uint32_t, Customer>& companies);
    void test_customer_create(std::map<uint32_t, Customer>& companies, uint32_t runs);
    void test_fill_customer_create(std::map<uint32_t, Customer>& companies, uint32_t runs);

    void customer_print(std::map<uint32_t, Customer>& companies)
    {
        std::cout << "List of companies:\n";
        for (const auto& [id, customer] : companies)
        {
            std::cout << "Company ID: " << id << "\n";
            std::cout << "Name: " << customer.name << "\n";
            std::cout << "Company Address: " << customer.address << "\n";
            std::cout << "Company Users: ";
            for (const auto& user : customer.users)
            {
                std::cout << user << " ";
            }
        }
    }

    void customer_create(std::map<uint32_t, Customer>& companies)
    {
        uint32_t i = 0;
        while (companies.find(i) != companies.end())
        {
            ++i;
        }
        companies[i].name = input::get("\nEnter customer name: ");
        companies[i].address = input::get("\nEnter customer address: ");
        uint32_t users_to_add = input::get(users_to_add, "\nEnter amount of users for this customer: ");
        companies[i].users.push_back(users_to_add);
    }

    void customer_delete(std::map<uint32_t, Customer>& companies)
    {
        uint32_t id = 0;
        id = input::get(id, "\nInput ID of customer to be deleted: ");
        if (companies.find(id) != companies.end())
        {
            companies.erase(id);
            std::cout << "Customer with ID: " << id << " was removed.\n";
        }
        else
        {
            std::cout << "No customer with the ID: " << id << " was found.\n";
            return;
        }
    }

    void test_fill_customer_create(std::map<uint32_t, Customer>& companies, uint32_t runs)
    {
        for (uint32_t i = 0; i < runs; ++i)
        {
            companies[i].name = "Test Company " + std::to_string(i);
            companies[i].address = "Test Lane " + std::to_string(i);
            companies[i].users = {100 + i};
        }
    }

    void test_customer_create(std::map<uint32_t, Customer>& companies, uint32_t runs)
    {
        test_fill_customer_create(companies, runs);
        customer_print(companies);
    }
};

#endif
