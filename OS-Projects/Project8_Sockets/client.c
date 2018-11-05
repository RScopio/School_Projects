//Ryan Scopio
/* client process - edit */

#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE sizeof(struct sockaddr_in)
#define BUFFER (sizeof(int) * 2)

main()
{
	int sockfd;
	char c, rc;
	int val1, val2;
	char values[BUFFER];
	struct sockaddr_in server = {AF_INET, 7000};

	/*convert and sore the server's IP address*/
	server.sin_addr.s_addr = inet_addr("197.45.10.2");

	/*set up the transport end point*/
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket call failed");
		exit(1);
	}

	/* connect the socket to the server's address */
	if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
	{
		perror("connect call failed");
		exit(1);
	}

	/*send and receive information with the server*/
	for (; rc == '\n';)
	{
		if (rc == '\n')
		{
			printf("Input first number\n");
			scanf("%d", &val1);
			printf("Input a second number\n");
			scanf("%d", &val2);
			for (int i = 0; i < BUFFER; i++)
			{
				if (i < sizeof(int))
				{
					values[i] = ((char *)val1)[i];
				}
				else
				{
					values[i] = ((char *)val2)[i - sizeof(int)];
				}
			}

			send(sockfd, &values, BUFFER, 0);
		}
		if (recv(sockfd, &rc, 1, 0) > 0)
		{
			if (rc == 0)
			{
				printf("The values are not equal\n");
			}
			else
			{
				printf("The values are equal\n");
			}
		}
		else
		{
			printf("server has died\n");
			close(sockfd);
			exit(1);
		}
	}
}