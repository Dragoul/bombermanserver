#include "engine.hpp"
#include "game.hpp"

#include <iostream>
#include <string>

using namespace std;
int main() {
  unsigned player_id;
  std::cin >> player_id;

  unsigned number_of_players;
  unsigned max_number_of_turns;
  size_t width;
  size_t height;
  std::cin >> number_of_players
	   >> max_number_of_turns
	   >> width
	   >> height;

  std::cerr << "np: " << number_of_players << std::endl
  	    << "max turns: " << max_number_of_turns << std::endl
  	    << "size: " << width << "x" << height << std::endl;

  Game game(number_of_players, max_number_of_turns, width, height);
  Engine engine(player_id, game);
  while (game.read_round(std::cin)) {
    std::string action = engine.generate_action();
    std::cout << action << std::endl;
    std::cerr << "\"" << action << "\" action sent from " << player_id << std::endl;
  }
}
