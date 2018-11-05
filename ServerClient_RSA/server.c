/*server.c*/
/*Ryan Scopio*/
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <gmp.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen, pid;
     struct sockaddr_in serv_addr, cli_addr;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     int counter = 0;
     while (counter < 1) {
         newsockfd = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) 
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
	     
	     int r;
	     char buffer[256];
	     bzero(buffer,256);
	     r = read(newsockfd,buffer,255);
	     if (r < 0) error("ERROR reading from socket");
	     printf("Encoded: %s\n",buffer);
	     r = write(newsockfd, "I got your message",18);
	     if (r < 0) error("ERROR writing to socket");

	     //decode
	     mpz_t n, d, pt, ct;
	     mpz_init(pt);
	     mpz_init(ct);
	     mpz_init_set_str(n, "9516311845790656153499716760847001433441357", 10);
	     mpz_init_set_str(d, "5617843187844953170308463622230283376298685", 10);

	     mpz_set_str(ct,buffer,10);
	     mpz_powm(pt,ct,d,n);
	     gmp_printf("Decoded: %Zd\n", pt);

	     char buff[64];
	     mpz_export(buff, NULL, 1,1,0,0,pt);
	     printf("As String: %s\n", buff);

	     mpz_clears(pt, ct, n, NULL, d, NULL);

             exit(0);
         }
         else close(newsockfd);
	 counter++;
     } /* end of while */
     return 0;
}
