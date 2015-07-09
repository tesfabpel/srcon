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

#include <sys/types.h>

struct rcon_packet
{
    int32_t size;
    int32_t id;
    int32_t type;
    char *body;
    char nul;
};

#endif //SRCON_RCON_PACKET_H_H
