// Preetesh Verma
// 2018eeb1171
// including the libraries for the client
#include <arpa/inet.h> 
#include <netinet/in.h> //Internet address family
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h>  //Internet Protocol family
#include <unistd.h> 
// defining the PORT for work for client
#define PORT 8090 
  
// Driver code 
int main() 
{  
    // declaring the necessary variables for establishing the socket connection
    int sock = 0, valread;  
    struct sockaddr_in serv_addr; 
    char* hello = "Hello from client"; 
    printf("%s\n",hello);
    // Creating socket file descriptor 
    // AF_INET is is used for IPv4 protocol while AF_INET6 is used for IPv6 protocol
    // SOCK_STREAM is used for setting up TCP connection 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        // negative output indicates socket creation faiure
        printf("Error in Socket Creation \n"); 
        return -1; 
    } 
    // telling the values of server PORT to which we would connect to the struct serv_addr and the family as well i.e IPv4
    memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 

    // checking if IP address is valid or not
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) { 
        // negative output indicates socket address faiure
        printf("Address not supported \n"); 
        return -1; 
    } 
  
    // connect the socket 
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        // negative output indicates socket connection faiure 
        printf("Connection Failed \n"); 
        return -1; 
    } 
    // taking input string
    char str[100]; 
    printf("\nInput the string:"); 
    scanf("%[^\n]s", str); 
    // length computation of the input string by the user
    int l = strlen(str); 
    // send string to server side 
    send(sock, str, sizeof(str), 0); 
    // read string sent by server 
    valread = recv(sock, str, l,0); 
    // printing the output i.e. the reverse string
    printf("%s\n", str); 
    return 0; 
} 