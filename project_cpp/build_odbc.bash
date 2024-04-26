
g++ -c odbc_db.cpp

g++ -Wall -I/usr/include/cppconn -o add_game.exe add_game.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o add_player.exe add_player.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_players.exe view_players.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_position_players.exe view_position_players.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_result.exe view_result.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_teams.exe view_teams.cpp odbc_db.o -L/usr/lib -lmysqlcppconn