// Check.cpp

#include "check.h"
#include <iostream>

Check::Check(sql::Connection* conn) : con(conn) {}

bool Check::restaurantExists(const std::string& restaurantName) {
    std::string query = "SELECT EXISTS(SELECT 1 FROM Restaurant WHERE restaurantName = '" + restaurantName + "') AS `exists`";
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(stmt->executeQuery(query));
        if (resultSet->next()) {
            return resultSet->getInt("exists") == 1;
        }
    } catch (sql::SQLException &e) {
        std::cout << "SQL Exception in restaurantExists: " << e.what() << std::endl;
    }
    return false;
}

bool Check::cityExists(const std::string& city) {
    std::string query = "SELECT EXISTS(SELECT 1 FROM Restaurant WHERE city = '" + city + "') AS `exists`";
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(stmt->executeQuery(query));
        if (resultSet->next()) {
            return resultSet->getInt("exists") == 1;
        }
    } catch (sql::SQLException &e) {
        std::cout << "SQL Exception in cityExists: " << e.what() << std::endl;
    }
    return false;
}

bool Check::checkOrderExists(int orderNo) {
    bool exists = false;
    string query = "SELECT EXISTS(SELECT 1 FROM FoodOrder WHERE orderNo = " 
                    + to_string(orderNo) + ") AS `exists`";
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(stmt->executeQuery(query));
        if (resultSet->next()) {
            exists = resultSet->getInt("exists") == 1;
        }
    } catch (sql::SQLException &e) {
        cout << "SQL Exception: " << e.what() << endl;
    }
    return exists;
}

bool Check::checkDishExists(const string& dishName) {
    bool exists = false;
    string query = "SELECT EXISTS(SELECT 1 FROM Dish WHERE dishName = '" 
                    + dishName + "') AS `exists`";
    try {
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> resultSet(stmt->executeQuery(query));
        if (resultSet->next()) {
            exists = resultSet->getInt("exists") == 1;
        }
    } catch (sql::SQLException &e) {
        cout << "SQL Exception: " << e.what() << endl;
    }
    return exists;
}
