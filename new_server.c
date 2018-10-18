#include <errno.h>
#include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>
#include "netinet/in.h"

#define MAXPENDING 3

int main(int argc, char const *argv[]){
  char * amount_str, *to_format, *out_file_name;
  int serverSckt, clntSckt, amount, outfile, bytes_written;
  struct sockaddr_in ServAddr;
  unsigned short servPort;
  unsigned int clntLen;
  long * file_size;
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

  // Open Output File


  // Continue to run until inturupted
  while(1){
    clntLen = sizeof(clntAddr); // Set the size of the in-out parameter
    if ((clntSckt = accept(serverSckt, (struct sockaddr *) &clntAddr, &clntLen)) < 0){
      printf("There was an error when trying to accept the client connection.\n %s \n", strerror(errno));
      continue;
    }
    // Client has successfully connected to a client
    printf("successfully connected to client IP: %o", clntAddr.sin_addr.s_addr);

    // Read the file <to_format> char
    to_format = (char*) malloc(sizeof(char));
    recv(clntSckt, to_format, sizeof(char), 0);

    // Read the file size
    file_size = (long*) malloc(sizeof(long));
    recv(clntSckt, file_size, sizeof(long), 0);

    // Read the file name
    out_file_name = (char*) malloc(100 * sizeof(char));
    recv(clntSckt, out_file_name, sizeof(out_file_name), 0);

    //Open the outfile
    if((outfile = open(out_file_name, O_CREAT) >= 0)){
      printf("There was an error when trying to create outfile.\n %s \n", strerror(errno));
    }


    bytes_written= 0;
    while(bytes_written < *file_size){
      // Read in the type of unit
      char * type = malloc(sizeof(char));
      recv(clntSckt, type,  sizeof(char), 0);
      // Check for input file type
      if(*type == 1){ //Read from file format 1
        // Read the <to_format> byte
        to_format = malloc(sizeof(char));
        recv(clntSckt, to_format, sizeof(char), 0);

        //

        // Read three byte amount
        amount_str = malloc(3 * sizeof(char));
        recv(clntSckt, amount_str, sizeof(amount_str), 0);
        amount = atoi(amount_str);
        // for()

        //
      }
      else if(*type == 0){ // Read from file format 2
        // Read one byte amount
        amount_str = malloc(sizeof(char));
        // fread(amount_str, 1, 1, infptr);
        amount = (int) amount_str;

      }
      else{
        printf("Improper file format given");
        exit(1);
      }
    }
  }
  return 0;
}
