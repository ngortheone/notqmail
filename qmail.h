#ifndef QMAIL_H
#define QMAIL_H

#include "substdio.h"

struct qmail {
  int flagerr;
  unsigned long pid;
  int fdm;
  int fde;
  substdio ss;
  char buf[1024];
} ;

extern int qmail_open();
extern void qmail_put(struct qmail *qq, const char *s, unsigned int len);
extern void qmail_puts(struct qmail *qq, const char *s);
extern void qmail_from(struct qmail *qq, const char *s);
extern void qmail_to(struct qmail *qq, const char *s);
extern void qmail_fail();
extern char *qmail_close();
extern unsigned long qmail_qp();

#endif
