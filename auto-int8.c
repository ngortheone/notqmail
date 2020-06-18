#include "substdio.h"
#include "readwrite.h"
#include "exit.h"
#include "scan.h"
#include "fmt.h"

char buf1[256];
substdio ss1 = SUBSTDIO_FDBUFW(write,1,buf1,sizeof(buf1));

void puts(s)
char *s;
{
  if (substdio_puts(&ss1,s) == -1) _exit(111);
}

int main(int argc, char **argv)
{
  char *name;
  char *value;
  unsigned long num;
  char strnum[FMT_ULONG];

  if (argc != 3) return 100;
  name = argv[1];
  if (!name) return 100;
  value = argv[2];
  if (!value) return 100;

  scan_8long(value,&num);
  strnum[fmt_ulong(strnum,num)] = 0;

  puts("int ");
  puts(name);
  puts(" = ");
  puts(strnum);
  puts(";\n");
  if (substdio_flush(&ss1) == -1) return 111;
  return 0;
}
