/*client.c*/
/*Ryan Scopio*/
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <gmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    
    /*ENCODE MESSAGE WITH RSA*/   
    mpz_t nn, e, pt, ct;
    mpz_init(pt);
    mpz_init(ct);
    mpz_init_set_str(nn, "9516311845790656153499716760847001433441357", 10);
    mpz_init_set_str(e, "65537", 10);
    const char *plaintext = buffer;
    mpz_import(pt, strlen(plaintext), 1, 1, 0, 0, plaintext);
    if (mpz_cmp(pt, nn) > 0) error("ERROR encoding plaintext");
    mpz_powm(ct, pt, e, nn);
    gmp_printf("Encoded: %Zd\n", ct);

    char output[64];
    mpz_get_str(output, 10, ct);

    n = write(sockfd,output,strlen(output));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    mpz_clears(pt, ct, nn, e, NULL, NULL);
    return 0;
}
