#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{    
string name = "";

   // get the parameter; argv[0] is the command
   name = name + argv[1];   

   // echo the name to the web page
   cout << "Hello " <<  name << "<br> <br>";
}
