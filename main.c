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

	p = rcon_crate_packet();
	p.type = RCON_TYPE_SERVERDATA_AUTH;

	// Set the password. If this field is larger than sz, set the last char to \0
	uint32_t sz = sizeof(p.body);
	memcpy(&p.body, pwd, sz);
	p.body[sz-1] = '\0';

	return false;
}

void loop()
{

}

void start_connection(char *ip, uint16_t port)
{
	printf("Trying to connect to: %s:%d\n", ip, port);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		//errno // TODO: Check?
		cleanup(EXIT_FAILURE);
	}

	// http://stackoverflow.com/questions/19071358/tcp-c-client-not-connecting-using-the-ip-address-you-entered
	struct sockaddr_in connaddr;
	memset(&connaddr, 0, sizeof(struct sockaddr_in));
	connaddr.sin_family = AF_INET;
	connaddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &connaddr.sin_addr);

	int cres = connect(sockfd, (struct sockaddr *)&connaddr, sizeof(connaddr));
	if(cres < 0)
	{
		fprintf(stderr, "Cannot establish connection\n");
		cleanup(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	printf("HELLO, WORLD!\n");

	if(argc < 3)
	{
		fprintf(stderr, "ERR! USAGE: srcon <ip> <port>\n");
		return -1;
	}

	char *ip = argv[1];
	char *port_s = argv[2];
	uint16_t port;
	int matched = sscanf(port_s, "%hu", &port);
	if(matched != 1) cleanup(EXIT_FAILURE);

	start_connection(ip, port);
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
