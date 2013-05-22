
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

  //  ais.push_back(AIInterface("../ai/test/test.exe"));
  AIInterface ai("../ai/test/test.exe");
  
  ai.Start();
  
  sleep(1);
  LOG_DEBUG("Sending state");


  string map[15] ={
    "#########\n",
    "####.####\n",
    "#...+...#\n",
    "#...+...#\n",
    "#...+...#\n",
    "#.#.#.#.#\n",
    "#++###++#\n",
    "#.#####.#\n",
    "#++###++#\n",
    "#.#.#.#.#\n",
    "#...+...#\n",
    "#...+...#\n",
    "#...+...#\n",
    "####.####\n",
    "#########\n"};

  string players[5] = {
    "4\n",
    "0 1 3\n",
    "1 1 11\n",
    "2 7 3\n",
    "3 7 11\n"};

  string bombs[1] ={
    "0\n"};

  string actions[4] = {
    "0 pass\n",
    "1 pass\n",
    "2 pass\n",
    "3 pass\n"};


  int playerId = 2;
  int numberOfPlayers = 4;
  int maxRounds = 200;
  int width = 9;
  int height = 15;

  ai << playerId;
  ai << numberOfPlayers;
  ai << maxRounds;
  ai << width;
  ai << height;


  int a=0;
  int b=0;
  for(b=0; b<300; b++) {
    for (a = 0; a < height; a++) {
      ai << map[a];
    }
    for (a = 0; a < numberOfPlayers + 1; a++) {
      ai << players[a];
    }
    for (a = 0; a < 1; a++) {
      ai << bombs[a];
    }
    for (a = 0; a < numberOfPlayers; a++) {
      ai << actions[a];
    }
  
    string ret;
    ai >> ret;
    LOG_DEBUG("Recieved \"%s\"",ret.c_str());
    usleep(10000);
  }
  ai << "out";
  
  //  ais[0]

  //  cout << ais[0] << endl << a << endl;


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
