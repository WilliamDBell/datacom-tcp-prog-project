#include "stdio.h"
#include "string.h"
#include <sys/socket.h>


int main(int argc, char const *argv[]) {
  int server_ip[6];
  // Get '.' Deliminated Server IP
  char *  token = strtok(argv[1], ".");
  server_ip[0] = atoi(token);
  int i = 1;
  while(i < 4){
    token = strtok(NULL, ".");
    server_ip[i] = atoi(token);
    i++;
  }
  // Get Server Port
  int server_port = atoi(argv[2]);

  //Create tcp socket using socket
  int sckt = socket(PF_INET, SOCK_STREAM, 0);

  // Make a Connection to the server
  connect(sckt, )

  return 0;
}
