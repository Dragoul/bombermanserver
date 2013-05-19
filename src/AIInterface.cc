
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class AIInterface
{
 public:

  pid_t pid;
  string executablePath;
  string name;

  AIInterface(string execPath)
  {
    executablePath = execPath;
  }

  ~AIInterface() {}

  int Start()
  {
    int pipe_in[2];
    int pipe_out[2];

    pipe(pipe_in);
    pipe(pipe_out);

    pid = fork();

    if(pid == 0) { // Ai process
      /* Child process closes up input side of pipe */
      close(pipe_in[1]);
      dup2(pipe_in[0],0); // redirect standard in to read from pipe

      close(pipe_out[0]);
      dup2(pipe_out[1],1); // redirect standard out to write to pipe;

      char cmd[100];
      
      cin >> cmd;
      cerr << "Child Message: " << cmd << endl;
      execl(cmd, cmd, "-r", "-t", "-l", (char *) 0);

      exit(1);
    }
    else if(pid > 0) { // Parent process
      // setup aiStream communication

      close(pipe_in[0]);
      write(pipe_in[1], "/bin/ls", strlen("/bin/ls")+1);

      close(pipe_out[1]);
      /* Parent process closes up output side of pipe */
      close(pipe_in[1]); // should not be closed :(

      for(int i = 0; i < 1; i++) {
	char rdb[1000];
	int n = read(pipe_out[0], rdb, sizeof(rdb));
	printf("Parent Message : \"%s\" %d \n", rdb, n);
	}

      // register child-killed-callback
      return 0;
    }
    //    LOG_DEBUG("Forking to create AI process failed");
    return 1;
  }


  template <class DataType> AIInterface& operator<< (const DataType& variable)
  {
    cout << variable;
    //    aiStream << variable;
    return *this;
  }

  template <class DataType> AIInterface& operator>> (DataType& variable)
  {
    //    aiStream >> variable;
    return *this;
  }

};

ostream& operator << (ostream &out, const AIInterface& ai)
{
  out << "Name: " << setw(20) << ai.name << endl;
  out << "Executable: " << setw(13) << ai.executablePath << endl;
  out << "Pid: " << setw(20) << ai.pid;

  return out;
}

istream& operator >> (istream &in, AIInterface& ai)
{
  return in;
}



