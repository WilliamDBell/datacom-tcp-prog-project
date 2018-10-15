#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char const *argv[]) {
  unsigned short server_port;
  int sckt;
  const char * svr_ip = argv[1];

  // // Get '.' Deliminated Server IP
  // char *  token = strtok(argv[1], ".");
  // server_ip[0] = atoi(token);
  // int i = 1;
  // while(i < 4){
  //   token = strtok(NULL, ".");
  //   server_ip[i] = atoi(token);
  //   i++;
  // }
  // Get Server Port
  server_port = atoi(argv[2]);

  //Create tcp socket using socket
  if((sckt = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    printf("Socket Creation Failed");
  }

  // Declare socket address for server
  struct sockaddr_in server_address;
  memset(&server_address, '0', sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = server_port;
  server_address.sin_addr.s_addr = inet_addr(svr_ip);

  // Make a Connection to the server
  if(connect(sckt,(struct sockaddr *) &server_address, sizeof(struct sockaddr_in)) < 0) {
    printf("There was an error when trying to connect with the server.\n %s \n", strerror(errno));
  }

  // Communicate using the send() and recv()

  // Close the connection
  close(sckt);
  exit(0);
}
