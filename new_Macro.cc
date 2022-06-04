#include <iostream>
using namespace std;
void new_Macro() // main
{

for (int i=5; i<6; i++){

//cout << i.c_str();
string command;
command = "root 'readout.cc(";
command += to_string(i);
command += ")' -q";

cout << command;
system(command.c_str());

}
}
