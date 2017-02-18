// Create a list from n things on the stack.

#include "../Headers/defs.h"

void
list(int n)
{
	int i;
	push(symbol(NIL));
	for (i = 0; i < n; i++)
		cons();
}
