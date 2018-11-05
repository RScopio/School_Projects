#include <stdio.h>   
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/wait.h>

int main (void)
{
   
int ls;                         
int s;                          
char buffer [256];              
char* ptr = buffer;             
int len = 0;                    
int maxLen = sizeof (buffer);   
int n = 0;                      
int waitSize = 16;              
struct sockaddr_in serverAddr;  
struct sockaddr_in clientAddr;                

struct sockaddr_in servAddr; 
int SERV_PORT = 49999; 

ls = socket (AF_INET, SOCK_STREAM, 0);
if (ls < 0)
{
    perror ("Error: Listen socket failed!");
    exit (1);
}

memset(&servAddr, '0', sizeof(servAddr));
servAddr.sin_family = AF_INET;
servAddr.sin_addr.s_addr = INADDR_ANY; 
servAddr.sin_port = htons (SERV_PORT);
memset( &( servAddr.sin_zero ), '\0', 8 );

if (bind (ls, ( struct sockaddr * ) &servAddr, sizeof (servAddr)) < 0)
{
    perror ("Error: binding failed!");
    exit (1);
}

if (listen (ls, waitSize) < 0)
{
    perror ("Error: listening failed!");
    exit (1);
}

struct sockaddr_in clntAddr; 
socklen_t clntAddrLen = sizeof(clntAddr); 

for ( ; ; )  
{

    if ((s = accept (ls, (struct sockaddr *)&clntAddr, &clntAddrLen)) < 0)
    {
        
        perror ("Error: accepting failed!");
        exit (1);
    }
    printf("accept\n");


    if(( n = recv( s, buffer, sizeof( buffer ), 0 ) ) <= 0 )
    {
        perror("recv");
    }
    else
    {
        printf("Recv %d byte \n", n);
    }

    int dataSend=0;
    dataSend = send (s, buffer, n, 0);
    if(dataSend==-1)
    {
        printf("dataSend==-1 \n");
        perror("send");
    }
    else
    {
        printf("Send %d byte \n", dataSend);
    }


    close (s);                                   
} 

}