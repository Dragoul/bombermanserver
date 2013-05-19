

void Command::printCommandHelp(string longCommand, string paramaterString, string helpText)
{
  const int MAXWIDTH = 45;
  string example = "";

  stringstream s;

  s << longCommand;


  vector<string> parameters;

  parameters.push_back("test");
  parameters.push_back("[sko | groda]");

  vector<string>::const_iterator itr;

  int i =1;
  for(itr = parameters.begin(); itr != parameters.end(); itr++) {
    s << " \033[3" << i << ";1m" << *itr;
    i++;
  }
  s << "\033[0m";

  outstr << "\t" << std::left << setw(MAXWIDTH) << setfill('.') << s.str()
	 << " : " << helpText
	 << example << endl;
}
void Command::show()
{
  printCommands();
}

void Command::printCommands()
{
  //  string BOLD="\033[4m";
  outstr << "Available commands to use to interact with the match" << endl;
  outstr << endl;
  printCommandHelp("restart", "","restarts the match");
  printCommandHelp("pause","","pauses the match");
  printCommandHelp("resumes","","resumes the match");
  printCommandHelp("previous","","previous turn");
  printCommandHelp("next","","next turn");
  outstr << endl;
  outstr << "Player commands: (PLAYER = [name | id | all | other]" << endl;
  printCommandHelp("resurrect", "PLAYER", "resurrects the player specified");
  printCommandHelp("kill", "PLAYER", "kills the player specified");
  printCommandHelp("changeai", "PLAYER ai", "kills the player specified");
  printCommandHelp("disable", "PLAYER [bombs | movement]", "kills the player specified");
  outstr << endl;
  outstr << "Map commands:" << endl;
  printCommandHelp("load", "map", "restarts the match on the a new map)");
  printCommandHelp("clear", "[bomb | shit | all]", "removes all the bombs from the map");
  outstr << endl;
  printCommandHelp("run", "script", "runs a script");
}
