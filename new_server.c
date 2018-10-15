#include <errno.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>
#include "netinet/in.h"

#define MAXPENDING 3

int main(int argc, char const *argv[]){
  int sckt;
  struct sockaddr_in ServAddr;
  unsigned short servPort;


  // Assign port Number
  servPort = atoi(argv[1]);

  // Create socket
  if((sckt = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    printf("There was an error trying to create the socket.\n %s \n", strerror(errno));
  }

  // Assign server address value
  memset(&ServAddr, 0, sizeof(ServAddr)); // zero out the address
  ServAddr.sin_family = AF_INET;
  ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  ServAddr.sin_port = htons(servPort);

  // Assign  a port to socket w/ bind
  if(bind(sckt,  (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0){
    printf("There was an error when trying to assign a port to the socket. \n %s \n", strerror(errno));
  }

  // Tell system to allow for connections with Listen
  if (listen(sckt, MAXPENDING) < 0){
    printf("There was an error when trying to allow the server to listen..\n %s \n", strerror(errno));
  }

  //


  return 0;
}
