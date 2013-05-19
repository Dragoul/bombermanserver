
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "AIInterface.cc"

using namespace std;

void print_usage()
{
  cout << "usage : bombermanserver [-i] [-m map] [-c NUM] AI AI ..." << endl;
  cout << endl;
  cout << " i : run in interactive mode" << endl;
  cout << " d : print server debug info" << endl;
  cout << endl;
  cout << " m map : the map to run a match on" << endl;
  cout << " c NUM : runs a match for NUM times" << endl;
}


int main(int argc, char * argv[])
{

  if(argc < 1) {
    print_usage();
    return 1;
  }

  vector<AIInterface> ais;

  ais.push_back(AIInterface("ls -l"));


  string a;
  ais[0] >> a;

  ais[0].Start();
  cout << ais[0] << endl << a << endl;


  

  //  cout << ais[0];
  

  //  log.init(); 
  //  command.init();
  //  command.show();

  //  settings.SetInteractiveMode(0);

  //  printCommands();
  //  wait();


  //  string mapPath();
  //  state.load(mapPath);


  return 0;
}
