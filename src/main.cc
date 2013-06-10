
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "AIInterface.cc"
#include "player.h"
#include "board.h"

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

  vector<Player> players;
  
  players.push_back(Player(2,4));
  players.push_back(Player(6,4));

  for (int i = 0; i < 2; i++) {
    ais.push_back(AIInterface("ai/test/test.exe"));  
    stringstream s;

    s << "./ai_socket_" << i;
    ais[i].socketName = s.str();
    ais[i].Start();
  }

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

  /*  string players[5] = {
    "4\n",
    "0 1 3\n",
    "1 1 11\n",
    "2 7 3\n",
    "3 7 11\n"};*/

  string bombs[1] ={
    "0\n"};

  string actions[4] = {
    "pass",
    "pass",
    "pass",
    "pass"};


  int maxRounds = 200;
  int width = 9;
  int height = 15;

  for (int p=0; p < ais.size(); p++) {
    ais[p] << p;
    ais[p] << players.size();
    ais[p] << maxRounds;
    ais[p] << width;
    ais[p] << height;
  }

  Board mapo;

  for(int i=0; i<80; i++)
    cout << endl;

  int a=0;
  int b=0;
  for(b=0; b<300; b++) {
    
    gotoxy(0,0);
    cout << mapo;
    /*
    for (a = 0; a < height; a++) {
      cout << map[a];
    }
    */
    /*    cout << players.size() << endl;
    for(vector<Player>::const_iterator itr = players.begin();
	itr < players.end();
	++itr)
    {
      cout << "Player " << a << ": " << *itr << endl;
      }*/
     cout << players.size() << "\n";
      for (a = 0; a < players.size(); a++) {
	cout << "Player " << a << ": " << players[a] << endl;
      }


    for (a = 0; a < 1; a++) {
      cout << "Bombs " << a << ": " << bombs[a];
    }
    for (a = 0; a < players.size(); a++) {
      cout << "Action Player " << a << ": " << ais[a].action << endl;
    }

    for (a = 0; a < players.size(); a++) {
      //      cout << players[a].x << " " << players[a].y << endl;
      gotoxy(players[a].x, players[a].y);
      cout << "X";
    }

    gotoxy(0,25);
    
    for (int player_id=0; player_id < ais.size(); player_id++) {
      if(b==0 && player_id == 1)
	break;

      ais[player_id] << mapo;
      /*
      for (a = 0; a < height; a++) {
	ais[player_id] << map[a];
      }
      */
      ais[player_id] << players.size() << "\n";
      for (a = 0; a < players.size(); a++) {
	ais[player_id] << a << " " << players[a];
      }
      for (a = 0; a < 1; a++) {
	ais[player_id] << bombs[a];
      }
      for (a = 0; a < players.size(); a++) {
	ais[player_id] << a << " " << ais[a].action << "\n";
      }
  
      string ret;
      //      ais[player_id] >> ret;

      LOG_DEBUG("Recieved \"%s\" from %d    ", ret.c_str(), player_id);

      players.at(player_id).move(mapo, ais[player_id].getMovement());
    }
    usleep(100000);
  }
  //  ais[0] << "out";
  
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
