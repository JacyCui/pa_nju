#include "trap.h"

int main()
{

	float a = 1.2, b = 1;
	float c = a + b;
	if (-1e-6 < c - 2.2 && c - 2.2 < 1e-6)
		;
	else
		HIT_BAD_TRAP;
	c = a * b;
	if (-1e-6 < c - 1.2 && c - 1.2< 1e-6)
		;
	else
		HIT_BAD_TRAP;

	c = a / b;
	if (-1e-6 < c - 1.2 && c - 1.2 < 1e-6)
		;
	else
		HIT_BAD_TRAP;

	c = a - b;
	if (-1e-6 < c - 0.2 && c- 0.2 < 1e-6) // this will fail, and also fails for native program, interesting, can be used as a quiz
		;
	else
		HIT_BAD_TRAP;

	HIT_GOOD_TRAP;
	return 0;
}
