all: 
	g++ -Wall testdb.cpp DB.cpp -o testdb

clean:
	-rm testdb
	
