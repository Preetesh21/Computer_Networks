// Preetesh Verma
// 2018eeb1171
// including the libraries for the server
#include <netinet/in.h> //internet address family
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> //for socket programming, Internet Protocol family
#include <unistd.h> //unistd.h is the name of the header file that provides access to the POSIX operating system API. 
// Portable Operating System Interface POSIX
// definig the PORT to work for the server
#include <math.h>
#include <stdio.h>
#include <ctype.h>
//#include <time.h>
#define CLIENTSS 100
#define PORT 8090
//Evaluation of Postfix expression by stack in C
// here I am doing in the postfix evaluation
// global decalrations for the same 
int stacks[50]; //ASsuming stack size is 50
int top=-1;
int f=0;
int pop()
{ // Function for POP operation 
  return(stacks[top--]);
}
 
int push(int elem)
{ // Function for PUSH operation 
  if(f==1){
    int num;
    num=pop();
    stacks[++top]=elem+10*num;
  }
  else if(f==0){
    stacks[++top]=elem;
    f=1;
  }
}
 
 // the real calculation is performed here 
int evaluate(char postfix[100])
{ 
  top = -1;
  f=0;                
  char ch;
  int i=0,operation1,operation2;
  while( (ch=postfix[i++]) != '\n')
  {
    // Push the operand which would be in numeric form 
    if(isdigit(ch)) push(ch-'0'); 
    else if(ch==' ')
      f=0;
    else
    {        
      // Operator,pop two  operands 
      f=0;
      operation2=pop();
      operation1=pop();
      // switch case to decide the operation out of +-*/
      switch(ch)
      {
        case '+':push(operation1+operation2);break;
        case '-':push(operation1-operation2);break;
        case '*':push(operation1*operation2);break;
        case '/':push(operation1/operation2);break;
        default:
        printf("Input invalid\n");
        return 0;
      }
    }
  }
  return stacks[top];
} 


int main() 
{
  // declaring the necessary variables for establishing the socket connection
  // creating file for storing data
   /* File pointer to hold reference to our file */
    // FILE * fPtr;
    // /* 
    //  * Open file in w (write) mode. 
    //  * "file1.txt" is complete path to create file
    //  */
    // fPtr = fopen("file1.txt", "w");
    // /* fopen() return NULL if last operation was unsuccessful */
    // if(fPtr == NULL)
    // {
    //     /* File not created hence exit */
    //     printf("Unable to create file.\n");
    //     exit(EXIT_FAILURE);
    // }
    char clients[CLIENTSS];
    pid_t c_pid;
    char* hello = "Hello from server"; 
    printf("%s\n",hello);
    int s_fd;
    struct sockaddr_in address,temp_address;  // struct to store the deatails of the newly created server socket.
    // Creating socket file descriptor 
    // AF_INET is is used for IPv4 protocol while AF_INET6 is used for IPv6 protocol
    // SOCK_STREAM is used for setting up TCP connection 
    // Protocol value for Internet Protocol(IP), which is the 0.
    if ((s_fd = socket(AF_INET,  SOCK_STREAM, 0)) == 0) { 
        // if file descriptor is 0, the socket is not created successfully
        printf("socket creation failed"); 
        return -1; 
    } 
    // telling the values of server PORT i.e. 8090 to the struct address and the family as well i.e IPv6
    address.sin_family = AF_INET; //IPv4
    address.sin_addr.s_addr = INADDR_ANY; //will listen to any IP
    // htons - host-to-network short
    address.sin_port = htons(PORT); //specific port 

    // binding the socket to  the port 8090 and address
    if (bind(s_fd, (struct sockaddr*)&address, sizeof(address)) < 0) { 
        // negative output indicates socket binding faiure
        printf("socket binding failed"); 
        return -1; 
    } 
    // Now the socket is successfully bind
    // converting the socket into listening socket using listen system call 
    if (listen(s_fd, 3) < 0) { 
        // If listening failed
        printf("Could not listen"); 
        return -1; 
    } 
    // Now the port is a listening port and ready to accept client query
    while(1){
        int client_socket;
        int addrlen = sizeof(temp_address);
        if ((client_socket = accept(s_fd, (struct sockaddr*)&temp_address, (socklen_t*)&addrlen)) < 0) { 
            // If coudn't accept successfully, function would return negative value
            printf("Could not accept"); 
            return -1; 
        } 
        printf("Connection accepted\n");
        inet_ntop(AF_INET, &(temp_address.sin_addr), clients, CLIENTSS);
        // Now server is accepting client's requests and forking it for multithreading
        if ((c_pid = fork()) == 0){
            close(s_fd);//terminating the connection
            while(1){
                char str[1000];
                // receiving the string sent by client
                int client_request = recv(client_socket, str, sizeof(str),0); 
                printf("String sent by client:%s\n", str); 
                // calling the funciton for postfix evaluation created above
                // clock_t tt; 
                // tt = clock(); 
                int ans = evaluate(str);
                // double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
                // fprintf(fptr, "%s %s %s %d\n", address,temp_address ,ans,time_taken);
                send(client_socket, &(ans), sizeof(int), 0);
            }
        }
    }
    
} 
