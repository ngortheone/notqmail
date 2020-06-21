#include "readwrite.h"
#include "substdio.h"
#include "subfd.h"

char subfd_outbuf[SUBSTDIO_OUTSIZE];
static substdio it = SUBSTDIO_FDBUFW(write,1,subfd_outbuf,SUBSTDIO_OUTSIZE);
substdio *subfdout = &it;
