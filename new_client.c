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
  int sckt, bytes_written;
  long check_size;
  char *buffer;
  const char * svr_ip = argv[1];
  FILE * infptr;

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
    exit(1);
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
    exit(1);
  }

  // Open file to send
  if((infptr = fopen(argv[3], "r")) != NULL){
    printf("There was an error when trying to open the file to be sent.\n %s \n", strerror(errno));
    exit(1);
  }

  // Check if the file is empty
  fseek (infptr, 0, SEEK_END);
  check_size = ftell(infptr);
  rewind(infptr); // reset file pointer to begining of file

  // Send the file to the client
  buffer = malloc(check_size * sizeof(char));
  void *p = buffer;
  while (check_size > 0) {
    bytes_written = write(sckt, p, check_size);
    check_size -= bytes_written;
    p += bytes_written;
  }

  close(sckt);
  exit(0);
}
