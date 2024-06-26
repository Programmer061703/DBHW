#!/bin/bash

set -e -v

g++ -c odbc_db.cpp
g++ -c add_game.cpp

g++ -Wall -I/usr/include/cppconn -o add_game.exe add_game.o odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o add_player.exe add_player.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_players.exe view_players.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_position_players.exe view_position_players.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_teams.exe view_teams.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_team_games.exe view_team_games.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_team_date.exe view_team_date.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o add_player_stats.exe add_player_stats.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
g++ -Wall -I/usr/include/cppconn -o view_players_game.exe view_players_game.cpp odbc_db.o -L/usr/lib -lmysqlcppconn
cd ..

  chmod 755 -R project_cpp/

  cd project_cpp/

