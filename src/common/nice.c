
#include "nice.h"

// hvis vi ikke kjener SYS_ioprio_get har vi en gammel gcc/glibc (for eks bbh-001) gj�mmer hele nice systemet
#ifdef SYS_ioprio_get

#include "../logger/logger.h"


static inline int ioprio_set(int which, int who, int ioprio)
{
        return syscall(SYS_ioprio_set, which, who, ioprio);
}

static inline int ioprio_get(int which, int who)
{
        return syscall(SYS_ioprio_get, which, who);
}

enum {
        IOPRIO_CLASS_NONE,
        IOPRIO_CLASS_RT,
        IOPRIO_CLASS_BE,
        IOPRIO_CLASS_IDLE,
};

enum {
        IOPRIO_WHO_PROCESS = 1,
        IOPRIO_WHO_PGRP,
        IOPRIO_WHO_USER,
};

#define IOPRIO_CLASS_SHIFT      13

void

ionice_benice(void)
{
	int ioprio = 7;
	int ioclass = IOPRIO_CLASS_BE;

	bblog(INFO, "Setting ionice for process to IDLE.");
	if (ioprio_set(IOPRIO_WHO_PROCESS, getpid(), ioprio | (ioclass << IOPRIO_CLASS_SHIFT))) {
		bblog_errno(ERROR, "ioprio_set(): Unable to set idle io priority");
	}
	if (nice(15) == -1) {
		bblog_errno(ERROR, "nice(15): Unable to increment cpu nice");
	}
}

#endif