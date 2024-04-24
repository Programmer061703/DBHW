#!/bin/bash
set -e -v

g++ -Wall -o hello.exe hello.cpp
g++ -c odbc_insert_item.cpp
g++ -c odbc_db.cpp
g++ -Wall -I/usr/include/cppconn -o odbc_insert_item.exe odbc_insert_item.o odbc_db.o -L/usr/lib -lmysqlcppconn
