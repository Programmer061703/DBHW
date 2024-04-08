#ifndef CHECK_H
#define CHECK_H


#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>
#include <memory> 


class Check{
public:
    Check(sql::Connection* con);
    bool restaurantExists(const std::string& restaurantName);
    bool cityExists(const std::string& city);
    bool checkOrderExists(int orderNo);
    bool checkDishExists(const std::string& dishName);



private:
    sql::Connection* con;


};


#endif
