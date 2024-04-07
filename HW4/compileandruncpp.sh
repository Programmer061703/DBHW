#!/bin/bash
set -e -v

# echo "Creating and filling tables from HW3 solution..."
# ./hw3_soln.sh

echo "Compiling..."
 g++ -Wall -I /usr/include/cppconn odbc_example.cpp -L /usr/lib -l mysqlcppconn -o hw4.exe

echo "Running..."
./hw4.exe
