#ifndef __FOO_HEADER__
#define __FOO_HEADER__

void foo();
/** Set random seed of rand0() */
void srand(unsigned int seed);
/** Generate pseudo random number in range (0~22767) */
int rand0();
/** Generate pseudo random number in range [0, 1) */
double randf();

#endif