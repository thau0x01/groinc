/* This file is a part of groinc
 * 
 * Copyright (C) 2006, 2007 Sarzyniec Luc <olbat@xiato.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * see the COPYING file for more informations */

/*
 * For further informations about this implementation please take a look to the following RFC :
 * 	RFC 768 - User Datagram Protocol (http://ietf.org/rfc/rfc768.txt)
 */

#include "proto_udp.h"
#include "printp.h"
#include <netinet/in.h>

void scan_udp(struct data *datagram, struct protocol_header *transport_layerph, struct protocol_header *application_layerph)
{
	transport_layerph->len = sizeof(struct udp_header);
}

void print_udp(int fd, char *datagram)
{
	struct udp_header *udph;
	udph = (struct udp_header *) datagram;
	print_proto(fd,"[UDP/ source port:%hu dest port:%hu udpdatalen:%hd checksum:%#x]",ntohs(udph->sourceport),ntohs(udph->destport),ntohs(udph->udpdatalen),udph->udpchecksum);
}
