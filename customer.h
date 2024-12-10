#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "structs.h"

/* NAMESPACE::INPUT
USAGE GUIDE:
Usage illustration on how to use namespace::input can be seen below.
This should make it easier to implement error-checking or bounds-checking
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

    static unsigned int get(unsigned int& value, const std::string& prompt)
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
All functions included and visible at declaration
What is "runs"? A: Number of test customers you want to simulate
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

    void customer_create(std::map<unsigned int, Customer>& companies)
    {
        unsigned int i = 0;
        while (companies.find(i) != companies.end())
        {
            ++i;
        }
        companies[i].name = input::get("\nEnter customer name: ");
        companies[i].address = input::get("\nEnter customer address: ");
        unsigned int users_to_add = input::get(users_to_add, "\nEnter amount of users for this customer: ");
        companies[i].users.push_back(users_to_add);
    }

    void customer_delete(std::map<unsigned int, Customer>& companies)
    {
        unsigned int id = 0;
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
