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

int main (int argc, char* argv[  ]) 
{
  
int s;                      
int  n;                     
char* servName;             
int servPort;               
char* string;               
int len;                    
char buffer [256 + 1];      
char* ptr = buffer;         
struct sockaddr_in serverAddr;  
int maxLen = 256; 


if (argc != 4)
{                                              
    printf ("Error: three arguments are needed!");                           
    exit (1);
}                  

servName = argv[1];
servPort = atoi(argv[2]);
string = argv[3];

struct sockaddr_in servAddr; 



if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
{
    printf("\n Error : Could not create socket \n");
    return 1;
}
memset(&servAddr, '0', sizeof(servAddr));
servAddr.sin_family = AF_INET;
servAddr.sin_port = htons(servPort);

if(inet_pton(AF_INET, argv[1], &servAddr.sin_addr)<=0)
{
    printf("\n inet_pton error occured\n");
    return 1;
}
if( connect(s, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
{
    perror ("Error: connection failed!");
    exit (1);
}


printf("connect\n");
int dataSend=0;
dataSend = send (s, string, strlen(string), 0);
if(dataSend==-1)
{
    printf("dataSend==-1 \n");
    perror("send");
}
else
{
    printf("else \n");
}
printf("while \n");

if(( n = recv( s, buffer, sizeof( buffer ), 0 ) ) <= 0 )
{
    perror("recv");
}
else
{
    printf("Recv %d byte \n", n);
}


buffer [n] = '\0';
printf ("Echoed string received: \n");
fputs (buffer, stdout);
printf ("\n");

close (s);

exit (0);

} 