#include <errno.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>
#include "netinet/in.h"

#define MAXPENDING 3

int main(int argc, char const *argv[]){
  int serverSckt, clntSckt;
  struct sockaddr_in ServAddr;
  unsigned short servPort;
  unsigned int clntLen;
  struct sockaddr_in clntAddr;
  
  
  // Assign port Number
  servPort = atoi(argv[1]);
  
  // Create socket
  if((serverSckt = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    printf("There was an error trying to create the socket.\n %s \n", strerror(errno));
  }
  
  // Assign server address value
  memset(&ServAddr, 0, sizeof(ServAddr)); // zero out the address
  ServAddr.sin_family = AF_INET;
  ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  ServAddr.sin_port = htons(servPort);
  
  // Assign  a port to socket w/ bind
  if(bind(serverSckt,  (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0){
    printf("There was an error when trying to assign a port to the socket. \n %s \n", strerror(errno));
  }
  
  // Tell system to allow for connections with Listen
  if (listen(serverSckt, MAXPENDING) < 0){
    printf("There was an error when trying to allow the server to listen.\n %s \n", strerror(errno));
  }
  
  // Continue to run until inturupted
  while(1){
    clntLen = sizeof(clntAddr); // Set the size of the in-out parameter
    if ((clntSckt = accept(serverSckt, (struct sockaddr *) &clntAddr, &clntLen)) < 0){
      printf("There was an error when trying to accept the client connection.\n %s \n", strerror(errno));
      continue;
    }
    // Client has successfully connected to a client
    printf("successfully connected to client IP: %o", clntAddr.sin_addr.s_addr);
  }
  
  //
  
  //  if (check_size == 0) {
  //    printf("Input file is empty\n");
  //    exit(1);
  //  }
  //
  //  while(feof(infptr) == 0){
  //    // Read in the Type formart of the file
  //    type = (char *) malloc(sizeof(char));
  //    fread(type, 1, 1 , infptr);
  //    // Check for input file type
  //    if(*type == 1){ //Read from file format 1
  //      // Read three byte amount
  //      amount_str = malloc(3 * sizeof(char));
  //      fread(amount_str, 3, 1, infptr);
  //      amount = atoi(amount_str);
  //
  //      //
  //    }
  //    else if(*type == 0){ // Read from file format 2
  //      // Read one byte amount
  //      amount_str = malloc(sizeof(char));
  //      fread(amount_str, 1, 1, infptr);
  //      amount = (int) amount_str;
  //
  //    }
  //    else{
  //      printf("Improper file format given");
  //      exit(1);
  //    }
  //  }
  //
  
  
  return 0;
}
