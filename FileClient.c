/*Implementation Of Client Server Model*/
/*Parth Naik - 201001185*/
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#define SERVERPORT 8888
#define MAXBUF 1024

int main()
	{
	int sockd, socket1;
	int counter, counter1,countertemp;
	int fd, fdtemp;
	struct sockaddr_in xferServer;
	char buf[MAXBUF], buftemp[MAXBUF];
	int returnStatus;
	char ip[15];
	char file1[20];
	char file2[20];
	char list[10]="file.list";

	/* create a socket */

	sockd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockd == -1)
		{
		fprintf(stderr, "Could not create socket!\n");
		exit(1);
		}
	else{
		printf("Socket created! Please enter server IP below:\n");
		scanf("%s",ip);
		}

	/* set up the server information */

	xferServer.sin_family = AF_INET;
	xferServer.sin_addr.s_addr = inet_addr(ip);
	xferServer.sin_port = htons(SERVERPORT);

	/* connect to the server */


	returnStatus = connect(sockd,(struct sockaddr*)&xferServer,sizeof(xferServer));
	if (returnStatus == -1)
		{
		fprintf(stderr, "Could not connect to server!\n");
		exit(1);
		}
	else
		{
		fprintf(stderr,"Connected to the server!\nBelow is the list of files available to download.\n:");

		/*Download File list from server*/

		returnStatus = write(sockd, list, strlen(list)+1);
		fdtemp = open(list, O_WRONLY | O_CREAT);
		while ((countertemp = read(sockd, buftemp, MAXBUF)) > 0)
			{

			/*Send to stdout*/	

			write(fdtemp, buftemp, countertemp);
			}

			/*Change the path of filelist.sh accordingly*/

			system("/home/blademaster/Desktop/filelist.sh");
			printf("Please choose a file to download:\n");
			scanf("%s",file1);

		/* send the name of the file we want to the server */
		close(sockd);
		socket1 = socket(AF_INET, SOCK_STREAM, 0);
		returnStatus = connect(socket1,(struct sockaddr*)&xferServer,sizeof(xferServer));
		if (returnStatus == -1)
		{
		fprintf(stderr, "Could not connect to server!\n");
		exit(1);
		}
		else
		{
		fprintf(stderr,"File name recieved.\n");
		}
		returnStatus = write(socket1, file1, strlen(file1)+1);
		if (returnStatus == -1)
			{
			fprintf(stderr, "Could not send filename to server!\n");
			exit(1);
			}
		else
			{
			printf("Enter the name of file in which you want to copy contents of the file you requested:");
			scanf("%s",file2);
	
		/* call shutdown to set our socket to read-only */

		
	/* open up a handle to our destination file to receive the contents */
	/* from the server*/
	
	fd = open(file2, O_WRONLY | O_CREAT | O_APPEND);
	if (fd == -1)
		{
		fprintf(stderr, "Could not open destination file, using stdout.\n");
		fd = 1;
		}

	/* read the file from the socket as long as there is data */
	counter=0;
	while ((counter = read(socket1, buf, MAXBUF)) > 0)
		{

		/* send the contents to stdout */

		write(fd, buf, counter);
		}
	if (counter == -1)
		{
		fprintf(stderr, "Could not read file from socket!\n");
		exit(1);
		}
	}
	shutdown(socket1, SHUT_WR);	
	}
	close(socket1);
	return 0;
}
