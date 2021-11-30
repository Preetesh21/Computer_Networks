// Preetesh Verma
// 2018eeb1171
// including the libraries for the client
#include <arpa/inet.h> 
#include <netinet/in.h> //Internet address family
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> //Internet Protocol family
#include <unistd.h> 
// defining the PORT for work for client
#define PORT 8090 
int main() 
{ 
    // declaring the necessary variables for establishing the socket connection
    char* hello = "Hello from client";
    int sock=0; 
    struct sockaddr_in address; // struct to store the details for the socket created for client
    printf("%s\n",hello);

    // Creating socket file descriptor 
    // AF_INET is is used for IPv4 protocol while AF_INET6 is used for IPv6 protocol
    // SOCK_STREAM is used for setting up TCP connection
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        // if negative output, socket creation failed
        printf("socket creation failed\n"); 
        return -1;
    } 
    // telling the values of server PORT to which we would connect to the struct serv_addr and the family as well i.e IPv4
    memset(&address, '0', sizeof(address)); 
    address.sin_family = AF_INET; 
    address.sin_port = htons(PORT); 
    // checking if IP address is valid or not
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0) { 
        // negative output indicates socket address faiure
        printf("Address is not supported \n"); 
        return -1;
    } 
    //Connecting to the socket
    if (connect(sock, (struct sockaddr*)&address, sizeof(address)) < 0) { 
        // negative output indicates socket connection failure
        printf("Connection Failed \n"); 
        return -1; 
    } 
    //if successfully connected, let's send the request to server
    while(1){
        char str[1000];
        printf("Enter your message here\n");
        fgets(str,1000,stdin);
        int len = strlen(str); 
        // send string to server side 
        send(sock, str, sizeof(str), 0); 
        // read string sent by server side
        int x;
        int serverResult = recv(sock, &x, sizeof(x),0); 
        printf("Server responded with : %d\n", x); 
    }
    
} 
