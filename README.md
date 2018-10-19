# datacom-tcp-prog-project

In this project, you will develop two network programs, one for client and one for server. The client
program sends a file containing units as defined in the practice project to the server. The server
translates the units to the format specified by the client, and saves the units to a file of the name
also specified by the client. Before translating the units, the server checks if received units have a
correct format. If not, the server sends back an error message immediately without saving the file.
If yes, the server sends back a confirmation message after saving the file. The client prints the result,
"Format error" or "Success", after getting the message from the server, then quits. The server keeps
running and waits for another client to connect.
The client should be invoked by the following command:
<client> <server IP> <server port> <file path> <to format> <to name>
Where <client> is the name of the client executable file name, <server IP> is the IP address
of the server, <server port> is the TCP port of the server, and <file path> is the path of
the file to be sent to the server. (The file path indicates the location of the file in the system on
which the server runs. It includes the file name, and possibly the hierarchy of directories.) There is
no size limit of the file. <to format> indicates how the server should translate the received units.
0 means no translation, 1 means to only translate type 0 units to type 1 with type 1 units unchanged,
2 means to only translate type 1 units to type 0 with type 0 units unchanged, and 3 means to translate
type 0 to 1 and type 1 to 0. <to name> is the name of the file the server should save the units to.
The server should be invoked by the following command:
<server> <port>
Where <server> is the name of the server executable file name, <port> is the port the server
listens to.
The parameters provided by the command line arguments must NOT be hard-coded.

Command to Run the project
./client 66.44.94.193 80 infile 1 outfile
