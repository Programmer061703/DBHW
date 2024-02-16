all: 
	g++ -Wall main.cpp database.cpp -o main

clean:
	-rm main
