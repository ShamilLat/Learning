#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

static int
superuser(unsigned uid)
{
    if (uid == 0) {
        return 1;
    }
    return 0;
}

static int
check_id(unsigned uid, unsigned st_uid)
{
    if (uid == st_uid) {
        return 1;
    }
    return 0;
}

static int
check_mask(unsigned user, unsigned task, int off) {
    if((user & (task >> off)) == user) {
        return 1;
    }
    return 0;
}

enum
{
    HOST_OFF = 6,
    GROUP_OFF = 3,
    USER_OFF = 0
};

int
myaccess(const struct stat *stb, const struct Task *task, int access)
{
    if (superuser(task->uid)) {
        return 1;
    } else if (check_id(task->uid, stb->st_uid)) {
        return check_mask(access, stb->st_mode, HOST_OFF);
    } else {
        for (int i = 0; i < task->gid_count; i++) {
            if (check_id(task->gids[i], stb->st_gid)) {
                return check_mask(access, stb->st_mode, GROUP_OFF);
            }
        }
    }

    return check_mask(access, stb->st_mode, USER_OFF);
}
