
g++ -c odbc_db.cpp

g++ -Wall -I/usr/include/cppconn -o add_game.exe add_game.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
