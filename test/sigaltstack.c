#include <signal.h>
#include <errno.h>

int sigaltstack(const stack_t *restrict ss, stack_t *restrict old)
{
	errno = EINVAL;
	return -1;
}
