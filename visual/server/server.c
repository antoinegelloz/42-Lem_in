#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <fcntl.h>

#define CONNMAX 1000
#define BYTES 1024

char	*root;
int		listenfd;
int		clients[CONNMAX];

void start_server(char *port)
{
	struct addrinfo hints, *res, *p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, port, &hints, &res) != 0)
	{
		perror ("getaddrinfo() error");
		exit(1);
	}
	for (p = res; p != NULL; p = p->ai_next)
	{
		listenfd = socket (p->ai_family, p->ai_socktype, 0);
		if (listenfd == -1)
			continue;
		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) 
			break;
	}
	if (p == NULL)
	{
		perror("socket() or bind()");
		exit(1);
	}
	freeaddrinfo(res);
	if (listen(listenfd, 1000000) != 0)
	{
		perror("listen() error");
		exit(1);
	}
}

void respond(int n)
{
	char	mesg[99999], *reqline[3], data_to_send[BYTES], path[99999];
	int		rcvd, fd, bytes_read;

	memset((void*)mesg, (int)'\0', 99999);
	rcvd = recv(clients[n], mesg, 99999, 0);
	if (rcvd < 0)
		fprintf(stderr, "recv() error\n");
	else if (rcvd == 0)	
		fprintf(stderr, "Client disconnected upexpectedly.\n");
	else
	{
		printf("%s", mesg);
		reqline[0] = strtok(mesg, " \t\n");
		if (strncmp(reqline[0], "GET\0", 4) == 0)
		{
			reqline[1] = strtok(NULL, " \t");
			reqline[2] = strtok(NULL, " \t\n");
			if (strncmp(reqline[2], "HTTP/1.0", 8) != 0 && strncmp(reqline[2], "HTTP/1.1", 8) != 0)
				write(clients[n], "HTTP/1.0 400 Bad Request\n", 25);
			else
			{
				if (strncmp(reqline[1], "/\0", 2) == 0)
					reqline[1] = "/index.html";
				strcpy(path, root);
				strcpy(&path[strlen(root)], reqline[1]);
				printf("file: %s\n", path);
				if ((fd = open(path, O_RDONLY)) != -1)
				{
					send(clients[n], "HTTP/1.0 200 OK\n\n", 17, 0);
					while ((bytes_read = read(fd, data_to_send, BYTES)) > 0)
						write(clients[n], data_to_send, bytes_read);
				}
				else
					write(clients[n], "HTTP/1.0 404 Not Found\n", 23);
			}
		}
	}
	shutdown(clients[n], SHUT_RDWR);
	close(clients[n]);
	clients[n] = -1;
}

int main(int ac, char **av)
{
	struct sockaddr_in clientaddr;
	socklen_t addrlen;
	char port[6];
	int slot;
	char c;
	int i;

	root = getenv("PWD");
	strcpy(port, "8888");
	while ((c = getopt(ac, av, "p:r:")) != -1)
	{
		switch (c)
		{
			case 'r':
				root = malloc(strlen(optarg));
				strcpy(root, optarg);
				break;
			case 'p':
				strcpy(port, optarg);
				break;
			case '?':
				fprintf(stderr, "Wrong arguments given!\n");
				exit(1);
			default:
				exit(1);
		}
	}
	printf("Server started and listening on port %s%s%s with root directory %s%s%s\n", "\033[92m", port, "\033[0m", "\033[92m", root, "\033[0m");

	for (i = 0; i < CONNMAX; i++)
		clients[i] = -1;

	start_server(port);

	slot = 0;
	while (1)
	{
		addrlen = sizeof(clientaddr);
		clients[slot] = accept(listenfd, (struct sockaddr *)&clientaddr, &addrlen);

		if (clients[slot] < 0)
			perror("accept() error");
		else
		{
			if (fork() == 0)
			{
				respond(slot);
				exit(0);
			}
		}
		while (clients[slot] != -1) 
			slot = (slot + 1) % CONNMAX;
	}
	return (EXIT_SUCCESS);
}
