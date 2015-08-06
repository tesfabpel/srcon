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
#include "rcon_packet.h"

uint32_t id = 1;

void rcon_init_packet(struct rcon_packet *p)
{
	memset(p, 0, sizeof(struct rcon_packet));
}

struct rcon_packet rcon_crate_packet()
{
	struct rcon_packet p;
	rcon_init_packet(&p);

	p.id = id++;

	return p;
}

void rcon_prepare_packet(struct rcon_packet *p)
{
	p->nul = '\0';
	p->size = sizeof(*p) - sizeof(p->size);
}
