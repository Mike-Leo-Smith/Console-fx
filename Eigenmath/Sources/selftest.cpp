// self test functions

#include "../Headers/defs.h"

static jmp_buf jbuf;

void
selftest(void)
{
	// for handling "errout"
	
	if (setjmp(jbuf))
		return;
	
	mini_test();
	
	logout("OK, all tests passed.\n");
}

void
logout(char *s)
{
	printstr(s);
}

void
errout(void)
{
	logout("\n");
	longjmp(jbuf, 1);
}

void
test(char *file, char **s, int n)
{
	
}

// these tests do not use "run" but still need a "stop" context

extern jmp_buf stop_return;

void
test_low_level(void)
{
	
}
