//Ryan Scopio
/* server - edit */

#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#define SIZE sizeof(struct sockaddr_in)
#define BUFFER (sizeof(int) * 2)

main()
{
	int sockfd;
	char values[BUFFER];

	/*the local server port*/
	struct sockaddr_in server = {AF_INET, 7000, INADDR_ANY};

	/*the structure to put in process2's address*/
	struct sockaddr_in client;
	int client_len = SIZE;

	/*set up the transport end point*/
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket call failed");
		exit(1);
	}

	/*bind the local address to the end point*/
	if (bind(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		perror("bind call failed");
		exit(1);
	}

	/*sit in a continual loop waiting for messages*/
	for (;;)
	{
		/*receives the message and stores the address of the client*/
		if (recvfrom(sockfd, &values, BUFFER, 0, &client, &client_len) == -1)
		{
			perror("server: receiving");
			continue;
		}

		char match = 1;
		for (int i = 0; i < sizeof(int); i++)
		{
			if (values[i] != values[i + sizeof(int)])
			{
				match = 0;
			}
		}

		/*sends back the message to where it came from*/
		if (sendto(sockfd, &match, 1, 0, &client, &client_len) == -1)
		{
			perror("server: sending");
			continue;
		}
	}
}
