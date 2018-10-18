#include <errno.h>
#include <fcntl.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/socket.h>
#include "netinet/in.h"
#include <unistd.h>

#define MAXPENDING 3

int main(int argc, char const *argv[]){
  char * amount_str, *to_format, *out_file_name, * buff;
  int serverSckt, clntSckt, amount, outfile, bytes_written;
  struct sockaddr_in ServAddr;
  int servPort;
  unsigned int clntLen;
  long * file_size;
  struct sockaddr_in clntAddr;

  printf("************************************\n");
  printf("***** Running Will's Server ********\n");

  // Assign port Number
  servPort = atoi(argv[1]);
  printf("Server Port Number: %u\n", servPort);

  // Create socket
  if((serverSckt = socket(PF_INET, SOCK_STREAM, 0)) < 0){
    printf("There was an error trying to create the socket.\n %s \n", strerror(errno));
  }
  printf("Created Socket: %d \n", serverSckt);

  // Assign server address value
  memset(&ServAddr, 0, sizeof(ServAddr)); // zero out the address
  ServAddr.sin_family = AF_INET;
  ServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  ServAddr.sin_port = htons(servPort);

  // Assign  a port to socket w/ bind
  if(bind(serverSckt,  (struct sockaddr *)&ServAddr, sizeof(ServAddr)) < 0){
    printf("There was an error when trying to assign a port to the socket. \n %s \n", strerror(errno));
  }
  printf("Port %u assigned to socket\n", servPort);

  // Tell system to allow for connections with Listen
  if (listen(serverSckt, MAXPENDING) < 0){
    printf("There was an error when trying to allow the server to listen.\n %s \n", strerror(errno));
  }
  printf("Server now listening on port: %d\n", servPort);

  // Open Output File


  // Continue to run until inturupted
  while(1){
    clntLen = sizeof(clntAddr); // Set the size of the in-out parameter
    if ((clntSckt = accept(serverSckt, (struct sockaddr *) &clntAddr, &clntLen)) < 0){
      printf("There was an error when trying to accept the client connection.\n %s \n", strerror(errno));
      continue;
    }
    else {
      printf("Accepted Connection to Client Server: \n");
      printf("Network Address: %d\n", clntAddr.sin_addr.s_addr);
    }
    // Client has successfully connected to a client
    printf("successfully connected to client IP: %o\n", clntAddr.sin_addr.s_addr);

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

        // Read three byte amount
        amount_str = malloc(3 * sizeof(char));
        recv(clntSckt, amount_str, sizeof(3 * sizeof(char)), 0);
        amount = atoi(amount_str);
        // Write out the amount to the outfile
        if(*to_format == '0' || *to_format == '1'){ // No Translation
          write(outfile, amount_str, sizeof(3 * sizeof(char)));
        }
        else if(*to_format == '2' || *to_format == '3'){ // Translation from 0 to 1
          char buff = amount;
          write(outfile, &buff, sizeof(char));
        }
        for(int i = 0; i < amount - 1; i++){ // Iterate over number values
          if(*to_format == '0' || *to_format == '1'){ // No translation
            // Write each byte from this line to the outfile one at a time
            buff = malloc(sizeof(char));
            recv(clntSckt, buff, sizeof(char), 0);
            while(*buff != '\n'){
              write(outfile, &buff, sizeof(char));
              recv(clntSckt, buff, sizeof(char), 0);
            }
            *buff = '\n';
            write(outfile, &buff, sizeof(char));
          }
          else if(*to_format == '2' || *to_format == '3'){ // Translation from 0 to 1
            

          }

        }
        // Write out the last number on the line
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
