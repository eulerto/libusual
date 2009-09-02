/*
 * Theme include for time.
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

#ifndef _USUAL_TIME_H_
#define _USUAL_TIME_H_

#include <usual/base.h>

#include <sys/time.h>
#include <time.h>

typedef uint64_t usec_t;
#define USEC 1000000ULL

char *format_time_ms(usec_t time, char *dst, unsigned dstlen);
char *format_time_s(usec_t time, char *dst, unsigned dstlen);

usec_t get_time_usec(void);
usec_t get_cached_time(void);
void reset_time_cache(void);

#ifdef WIN32
int gettimeofday(struct timeval * tp, void * tzp);
struct tm *localtime_r(const time_t *tp, struct tm *buf);

static inline void usleep(long usec) { Sleep(usec / 1000); }

struct rusage {
	struct timeval ru_utime;
	struct timeval ru_stime;
};

#define RUSAGE_SELF 0
int getrusage(int who, struct rusage *dst);

#endif

#endif
