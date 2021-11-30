// Preetesh Verma
// 2018eeb1171
// including the libraries for the server
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <unistd.h> //unistd.h is the name of the header file that provides access to the POSIX operating system API. 
// Portable Operating System Interface POSIX
// definig the PORT to work for the server 
#define PORT 8090 
// Driver code 
int main() 
{ 
    // declaring the necessary variables for establishing the socket connection
    int server_fd, n_sock; 
    char str[100]; // Assumption input string being of atmost 100 characters
    char* hello = "Hello from server"; 
    printf("%s\n",hello);
    // Creating socket file descriptor 
    // AF_INET is is used for IPv4 protocol while AF_INET6 is used for IPv6 protocol
    // SOCK_STREAM is used for setting up TCP connection 
    // Protocol value for Internet Protocol(IP), which is the 0.
    if ((server_fd = socket(AF_INET,SOCK_STREAM, 0)) == 0) { 
        // negative output indicates socket creation faiure
        printf("Error in Socket Creation \n"); 
        return -1; 
    } 
    struct sockaddr_in address; // struct to store the deatails of the newly created server socket.
    // telling the values of server PORT i.e. 8090 to the struct address and the family as well i.e IPv6
    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; //will listen to any IP address
    address.sin_port = htons(PORT); 
  
    // binding the socket to  the port 8090 and address 
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0) { 
        // negative output indicates socket binding faiure
        printf("bind failed \n"); 
        return -1; 
    } 
  
    // If the socket is successfully bound, the socket is turned into listening socket using listen system call 
    if (listen(server_fd, 3) < 0) { 
        // negative output indicates socket listening faiure
        printf("listen\n"); 
        return -1; 
    } 
    // Now the server socket is in passive mode. 
    // It waits for the client to approach the server to make a connection. 
    // Now it extracts the first connection request on the queue of pending connections 
    // Now the server socket is accepting the incoming client socket connection 
    if ((n_sock = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&sizeof(address))) < 0) { 
        // negative output indicates socket accepting faiure
        printf("accept\n"); 
        return -1; 
    } 
    // Now after accepting clients connection request the server can receive the data packets from it to process.
    // read string send by client 
    int valuereceived = recv(n_sock, str, sizeof(str),0); 
    printf("String sent by client:%s\n", str); 
    int temp; 
    int len = strlen(str); 
    int i=0;
    int j=len-1;
    // loop to reverse the string 
    while(i<j){
        temp = str[i]; 
        str[i] = str[j]; 
        str[j] = temp; 
        i++;
        j--;
    } 
    // send reversed string to client by send system call 
    send(n_sock, str, sizeof(str), 0); 
    printf("Reverse string sent to client\n"); 
    return 0; 
} 