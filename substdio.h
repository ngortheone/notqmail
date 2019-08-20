#ifndef SUBSTDIO_H
#define SUBSTDIO_H

#include <sys/types.h>
#include <unistd.h>

typedef struct substdio {
  char *x;
  int p;
  int n;
  int fd;
  union {
    ssize_t (*op)(int,void*,size_t);
    ssize_t (*opw)(int,const void*,size_t);
  };
} substdio;

#undef _QMAIL_HAS_C99
#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define _QMAIL_HAS_C99
#endif
#endif

#ifdef _QMAIL_HAS_C99
#define SUBSTDIO_FDBUF(o,f,buf,len) { .x = (buf), .p = 0, .n = (len), .fd = (f), .op = (o) }
#define SUBSTDIO_FDBUFW(o,f,buf,len) { .x = (buf), .p = 0, .n = (len), .fd = (f), .opw = (o) }
#else
#define SUBSTDIO_FDBUF(o,f,buf,len) { (buf), 0, (len), (f), (o) }
#define SUBSTDIO_FDBUFW(o,f,buf,len) { (buf), 0, (len), (f), (o) }
#endif

extern void substdio_fdbuf(substdio *s, ssize_t (*op)(int,void*,size_t), int fd, char *buf, int len);
static inline void substdio_fdbufw(substdio *s, ssize_t (*op)(int,const void*,size_t), int fd, char *buf, int len)
{
  substdio t = SUBSTDIO_FDBUFW(op, fd, buf, len);
  *s = t;
}

extern int substdio_flush();
extern int substdio_put(substdio *s, char *buf, size_t len);
extern int substdio_bput(substdio *s, char *buf, size_t len);
extern int substdio_putflush(substdio *s, char *buf, size_t len);
extern int substdio_puts();
extern int substdio_bputs();
extern int substdio_putsflush();

extern int substdio_get();
extern int substdio_feed();

extern char *substdio_peek();
extern void substdio_seek();

#define substdio_fileno(s) ((s)->fd)

#define SUBSTDIO_INSIZE 8192
#define SUBSTDIO_OUTSIZE 8192

#define substdio_PEEK(s) ( (s)->x + (s)->n )
#define substdio_SEEK(s,len) ( ( (s)->p -= (len) ) , ( (s)->n += (len) ) )

#define substdio_BPUTC(s,c) \
  ( ((s)->n != (s)->p) \
    ? ( (s)->x[(s)->p++] = (c), 0 ) \
    : substdio_bput((s),&(c),1) \
  )

extern int substdio_copy();

#endif
