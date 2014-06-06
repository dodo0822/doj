#ifndef DOJ_JUDGER_H
#define DOJ_JUDGER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include "DOJ_compile.h"
#include "DOJ_execute.h"

namespace DOJ {
	namespace judger {
		void catch_alarm(int signum);
		void judge(int pro_id, int sub_id);
	}
}

#endif
