/*
 * Theme include for sockets.
 *
 * Copyright (c) 2007-2009 Marko Kreen, Skype Technologies OÜ
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */ 

#ifndef _USUAL_SOCKET_H_
#define _USUAL_SOCKET_H_

#include <usual/base.h>


#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <usual/socket_win32.h>
#endif

#include <fcntl.h>

#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_POLL_H
#include <poll.h>
#endif
#ifdef HAVE_SYS_POLL_H
#include <sys/poll.h>
#endif
#ifdef HAVE_SYS_UN_H
#include <sys/un.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_NETINET_TCP_H
#include <netinet/tcp.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

bool socket_setup(int sock, bool non_block);
bool socket_set_nonblocking(int sock, bool non_block);

const char *sa2str(const struct sockaddr *sa, char *buf, int buflen);

#ifndef HAVE_INET_NTOP
#define inet_ntop(a,b,c,d) compat_inet_ntop(a,b,c,d)
const char *inet_ntop(int af, const void *src, char *dst, int cnt);
#endif

#ifndef HAVE_GETPEEREID
#define getpeereid(a,b,c) compat_getpeereid(a,b,c)
int getpeereid(int fd, uid_t *uid_p, gid_t *gid_p);
#endif

#if !defined(HAVE_POLL)
#define POLLIN		(1 << 0)
#define POLLOUT		(1 << 1)
#define POLLHUP		(1 << 2)
#define POLLPRI		(1 << 3)
#define POLLNVAL	(1 << 4)
#define POLLERR		(1 << 5)
#define poll(a,b,c)	compat_poll(a,b,c)
struct pollfd {
	int fd;
	short events;
	short revents;
};
typedef unsigned long nfds_t;
int poll(struct pollfd *fds, nfds_t nfds, int timeout_ms);
#endif

#ifdef WIN32
int win32_socketpair(int d, int typ, int proto, int sv[2]);
#define socketpair(a,b,c,d) win32_socketpair(a,b,c,d)
#endif

#endif

