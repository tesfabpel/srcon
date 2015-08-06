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
#ifndef SRCON_RCON_PACKET_H_H
#define SRCON_RCON_PACKET_H_H

#include "main.h"

enum rcon_packet_type
{
	RCON_TYPE_SERVERDATA_AUTH = 3,
	RCON_TYPE_SERVERDATA_AUTH_RESPONSE  = 2,
	RCON_TYPE_SERVERDATA_EXECCOMMAND    = 2,
	RCON_TYPE_SERVERDATA_RESPONSE_VALUE = 0
};

struct rcon_packet
{
    int32_t size;
    int32_t id;
    enum rcon_packet_type type : sizeof(int32_t)*8;
    char body[UINT16_MAX];
	char nul;
};

void rcon_init_packet(struct rcon_packet *p);
struct rcon_packet rcon_create_packet();
void rcon_prepare_packet(struct rcon_packet *p);

#endif //SRCON_RCON_PACKET_H_H
