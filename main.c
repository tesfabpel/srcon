/*
srcon: Simple Valve RCON client
Copyright (C) 2015 TesX <tesfabpel@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"
#include <readline/readline.h>

#include "rcon_packet.h"

// https://developer.valvesoftware.com/wiki/Source_RCON_Protocol

int sockfd = -1;

void cleanup(int exitno)
{
	if(sockfd >= 0) close(sockfd);
	exit(exitno);
}

bool authenticate()
{
	struct rcon_packet p;

	char *pwd = readline("Password: ");

	p = rcon_create_packet();
	p.type = RCON_TYPE_SERVERDATA_AUTH;

	// Set the password. If this field is larger than sz, set the last char to \0
	uint32_t sz = sizeof(p.body);
	memcpy(&p.body, pwd, sz);
	p.body[sz-1] = '\0';

	rcon_prepare_packet(&p);
	ssize_t sent = send(sockfd, &p, sizeof(p), 0);
	if(sent < 0) return false;

	struct rcon_packet recvp;
	rcon_init_packet(&recvp);

	ssize_t recvd = recv(sockfd, &recvp, sizeof(struct rcon_packet), 0);

	return false;
}

void loop()
{

}

void start_connection(char *addr, char *port)
{
	printf("Getaddrinfo\n");

	struct addrinfo *result, *rp;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	int res = getaddrinfo(addr, port, &hints, &result);
	if (res != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(res));
		cleanup(EXIT_FAILURE);
	}

	int sfd = 0;
	for(rp = result; rp != NULL; rp = rp->ai_next)
	{
		//printf("Trying to connect to: %s\n", rp->ai_addr->sa_data);

		sfd = socket(rp->ai_family, rp->ai_socktype,
					 rp->ai_protocol);

		if(sfd == -1) continue; // Try the next one

		if(connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
		{
			// Success
			break;
		}

		close(sfd);
		sfd = 0;
	}

	if(rp == NULL)
	{
		// No address succeeded
		fprintf(stderr, "Could not connect\n");
		cleanup(EXIT_FAILURE);
	}

	sockfd = sfd;
}

int main(int argc, char *argv[])
{
	printf("HELLO, WORLD!\n");

	if(argc < 3)
	{
		fprintf(stderr, "ERR! USAGE: srcon <ip> <port>\n");
		return -1;
	}

	char *host = argv[1];
	char *port = argv[2];

	start_connection(host, port);
	if(sockfd < 0)
	{
		return -2;
	}

	if(!authenticate())
	{
		cleanup(EXIT_FAILURE);
	}

	loop();

	cleanup(EXIT_SUCCESS);
	return 0;
}
