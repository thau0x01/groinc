/* This file is a part of groinc
 * Copyright 2006 Sarzyniec Luc <olbat@xiato.com>
 * This software is released under GPL the license
 * see the COPYING file for more informations */

#ifndef _SNIFFER_H
#define _SNIFFER_H

int start_sniff(int inputfd,int outputfd);
int stop_sniff();
int cleanup_sniff();

#endif

