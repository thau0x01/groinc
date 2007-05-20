/* This file is a part of groinc
 * 
 * Copyright (C) 2006, 2007 Sarzyniec Luc <olbat@xiato.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * see the COPYING file for more informations */

#include <netinet/in.h>
#include "parsers.h"
#include "../protocols/scan_proto.h"

void parse_datalink_layer(struct data *datagram,struct protocol_header *datalink_layerph,struct protocol_header *network_layerph)
{
	datalink_layerph->id = PROTO_ETHER;

	datalink_layerph->header = (datagram->data + datagram->len);
	switch (datalink_layerph->id)
	{
		case PROTO_ETHER :
			scan_ether(datagram,datalink_layerph,network_layerph);
			break;
	}
	if ((datagram->len + datalink_layerph->len) < datagram->totlen)
		datagram->len = (datagram->len + datalink_layerph->len);
}

void parse_network_layer(struct data *datagram,struct protocol_header *network_layerph,struct protocol_header *transport_layerph)
{
	network_layerph->header = (datagram->data + datagram->len);
	switch (network_layerph->id)
	{
		case ETHPROTO_IP :
			scan_ipv4(datagram,network_layerph,transport_layerph);
			break;
		case ETHPROTO_ARP :
			scan_arp(datagram,network_layerph,transport_layerph);
			break;
	}
	if ((datagram->len + network_layerph->len) < datagram->totlen)
		datagram->len = (datagram->len + network_layerph->len);
} 

void parse_transport_layer(struct data *datagram,struct protocol_header *transport_layerph)
{
	transport_layerph->header = (datagram->data + datagram->len);
	switch (transport_layerph->id)
	{
		case IPPROTO_ICMP :
			scan_icmp(datagram,transport_layerph);
			break;
		case IPPROTO_TCP :
			scan_tcp(datagram,transport_layerph);
			break;
		case IPPROTO_UDP :
			scan_udp(datagram,transport_layerph);
			break;
	}
	if ((datagram->len + transport_layerph->len) < datagram->totlen)
		datagram->len = (datagram->len + transport_layerph->len);
}

__u16 get_source_port(struct protocol_header *transport_layerph)
{
	return ntohs(*((__u16 *)transport_layerph->header));
}

__u16 get_dest_port(struct protocol_header *transport_layerph)
{
	return ntohs(*((__u16 *)(transport_layerph->header + sizeof(__u16))));
}