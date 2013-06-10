
#include <iostream>
#include <string>
#include <sstream>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#include "../include/log.h"
#include "player.h"

using namespace std;





class AIInterface
{
 public:

  pid_t pid;
  string executablePath;
  string name;
  string socketName;
  string action;

  int connection_fd;

  AIInterface(string execPath) : executablePath(execPath) {
    action = "pass";
  }
  ~AIInterface() {}

  int StartClientAi()
  {
      struct sockaddr_un address;
      int  socket_fd;
      int nbytes;
      char buffer[256];

      socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
      if(socket_fd < 0) {
	LOG_ERROR("socket() failed\n");
	return 1;
      }

      /* start with a clean address structure */
      memset(&address, 0, sizeof(struct sockaddr_un));

      address.sun_family = AF_UNIX;
      snprintf(address.sun_path, UNIX_PATH_MAX, socketName.c_str());

      usleep(100000);
      LOG_DEBUG("Trying to connect");

      if(connect(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un)) != 0) {
	LOG_ERROR("connect() failed\n");
	return 1;
      }
      LOG_DEBUG("Connection complete");

      dup2(socket_fd,0); // redirect standard in to read from pipe
      dup2(socket_fd,1); // redirect standard out to write to pipe;

      cout << "PING" << flush;

      string pong;
      cin >> pong;

      /*
      char rdb[1000];
      int n = read(0, rdb, sizeof(rdb));
      printf("Parent Message : \"%s\" %d \n", rdb, n);
      cmd = rdb;
      */
      if(pong != "PONG") {
	LOG_ERROR("Ping failed, got %s, killing client", pong.c_str());
      }
      else {
	LOG_DEBUG("Staring AI: %s", executablePath.c_str());
	if(0 != execl(executablePath.c_str(),
		      executablePath.c_str(), "-r", "-t", "-l", (char *) 0)) {
	  LOG_ERROR("Ai failed to execute");
	}
      }
      
      sleep(1);
      close(socket_fd);
  }


  int connection_handler(int connection_fd)
  {
    char rdb[1000];

    operator>>(rdb);
      //    int n = read(connection_fd, rdb, sizeof(rdb));
    if(strcmp(rdb, "PING")){
      LOG_ERROR("PING Failed, got %s", rdb);
      return 1;
    }

    strcpy(rdb,"PONG\n");
    operator<<(rdb);
    return 0;
  }


  int StartServer()
  {
    struct sockaddr_un address;
    int socket_fd;
    socklen_t address_length;


    socket_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0) {
      LOG_ERROR("socket() failed");
      return 1;
    }

    unlink(socketName.c_str());

    /* start with a clean address structure */
    memset(&address, 0, sizeof(struct sockaddr_un));

    address.sun_family = AF_UNIX;
    snprintf(address.sun_path, UNIX_PATH_MAX, socketName.c_str());

    // bind socket to be able to receive connections
    if(bind(socket_fd, (struct sockaddr *) &address, sizeof(struct sockaddr_un)) != 0) {
      LOG_ERROR("bind() failed");
      return 1;
    }

    int nrPlayers = 1;
    if(listen(socket_fd, nrPlayers) != 0) {
      LOG_ERROR("listen() failed");
      return 1;
    }


    pid_t child;

    while((connection_fd = accept(socket_fd,
				  (struct sockaddr *) &address,
				  &address_length)) > -1) {

      LOG_DEBUG("Connection received %d", connection_fd);
      return connection_handler(connection_fd);
    }

    LOG_DEBUG("Connection fd = %d", connection_fd);

    close(socket_fd);
    unlink(socketName.c_str());
    return 0;
  }

  int Start()
  {
    pid = fork();

    if(pid == 0) { // Ai process
      // Child process closes up input side of pipe
      LOG_DEBUG("Starting AI client");
      StartClientAi();
      LOG_ERROR("Killing AI client");

      exit(1);
    }
    else if(pid > 0) { // Parent process
      // setup aiStream communication
      StartServer();

      /*int status;

      if ((pid = wait(&status)) == -1)
	LOG_ERROR("wait error");
      else {
	if (WIFSIGNALED(status) != 0)
	  LOG_WARNING("Child process ended because of signal %d", WTERMSIG(status));
	else if (WIFEXITED(status) != 0)
	  LOG_WARNING("Child process ended normally (status = %d)", WEXITSTATUS(status));
	else
	  LOG_ERROR("Child process did not end normally");
	  }*/
      
      LOG_DEBUG("Returning from Start");
      return 0;
    }
    LOG_ERROR("Forking to create AI process failed");

    return 1;
  }

  template <class DataType> AIInterface& operator<< (const DataType& variable)
  {
    stringstream s;
    s << variable << "\n";
    //cout << "Sent: " << s.str().c_str();
    write(connection_fd, s.str().c_str(), s.str().length());
    return *this;
  }

  template <class DataType> AIInterface& operator>> (DataType& variable)
  {
    char rdb[1000];
    int n = read(connection_fd, rdb, sizeof(rdb));

    if (n >= 1000) {
      LOG_ERROR("INDEX OUT OF BOuNNDS=");
    }
    rdb[n]='\0';
    stringstream s;
    s << rdb;
    s >> variable;
    return *this;
  }

  PlayerMotionType getMovement()
  {
    //    operator>>(action);

    if (action == "pass") {
      return PASS;
    }
    else if (action == "left"){
      return LEFT;
    }
    else if (action == "right"){
      return RIGHT;
    }
    else if (action == "down") {
      return DOWN;
    }
    else if (action == "up") {
      return UP;
    }
    else {
      LOG_ERROR("Invalid motion: %s", action);
      action = "pass";
      return PASS;
    }
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
