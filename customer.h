#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "structs.h"

/* Usage in other implementations:
input::get("PromptOutput", valueToReturn);
input::get("PromptOutput");
*/
namespace input
{
    static int get(const std::string& prompt, int& value)
    {
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    static double get(const std::string& prompt, double& value)
    {
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    static unsigned int get(const std::string& prompt, unsigned int& value)
    {
        std::cout << prompt;
        std::cin >> value;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

/* Usage in other implementations:
customer::customer_print(std::map<uint32_t, Customer>& YourMap);
customer::customer_create(std::map<uint32_t, Customer>& YourMap);
customer::customer_delete(std::map<uint32_t, Customer>& YourMap);
customer::test_customer_create(std::map<uint32_t, Customer>& YourMap);
customer::test_fill_customer_create(std::map<uint32_t, Customer>& YourMap, NmbrOfTestCustomersToAdd);
*/
namespace customer
{
    void customer_print(std::map<unsigned int, Customer>& companies);
    void customer_create(std::map<unsigned int, Customer>& companies);
    void customer_delete(std::map<unsigned int, Customer>& companies);
    void test_customer_create(std::map<unsigned int, Customer>& companies, unsigned int runs);
    void test_fill_customer_create(std::map<unsigned int, Customer>& companies, unsigned int runs);

    void customer_print(std::map<unsigned int, Customer>& companies)
    {
        std::cout << "List of companies:\n";
        for (const auto& [id, customer] : companies)
        {
            std::cout << "\nCompany ID: " << id << "\n";
            std::cout << "Name: " << customer.name << "\n";
            std::cout << "Company Address: " << customer.address << "\n";
            std::cout << "Company Users: ";
            for (const auto& user : customer.users)
            {
                std::cout << user << " ";
            }
            std::cout << std::endl;
        }
    }

    void customer_create(std::map<unsigned int, Customer>& companies)
    {
        unsigned int i = 0;
        while (companies.find(i) != companies.end())
        {
            ++i;
        }
        companies[i].name = input::get("Enter customer name: ");
        companies[i].address = input::get("Enter customer address: ");
        unsigned int users_to_add = input::get("Enter amount of users: ", users_to_add);
        companies[i].users.push_back(users_to_add);
    }

    void customer_delete(std::map<unsigned int, Customer>& companies)
    {
        unsigned int id = 0;
        id = input::get("\nInput ID of customer to be deleted: ", id);
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

    void test_fill_customer_create(std::map<unsigned int, Customer>& companies, unsigned int runs)
    {
        for (unsigned int i = 0; i < runs; ++i)
        {
            companies[i].name = "Test Company " + std::to_string(i);
            companies[i].address = "Test Lane " + std::to_string(i);
            companies[i].users = {100 + i};
        }
    }

    void test_customer_create(std::map<unsigned int, Customer>& companies, unsigned int runs)
    {
        test_fill_customer_create(companies, runs);
        customer_print(companies);
    }
};

#endif
