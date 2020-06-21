#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include "prot.h"

int prot_gid(gid_t gid)
{
  if (setgroups(1,&gid) == -1) return -1;
  return setgid(gid); /* _should_ be redundant, but on some systems it isn't */
}

# define GROUP_COUNT 8
int prot_gids(const char *user, gid_t gid)
{
  gid_t gids[GROUP_COUNT];
  int gcount = GROUP_COUNT;
  int r = getgrouplist(user, gid, gids, &gcount);
  /* member of too many groups */
  if (r < 0)
    return r;
  if (setgroups(gcount,gids) == -1) return -1;
  return setgid(gid); /* _should_ be redundant, but on some systems it isn't */
}
