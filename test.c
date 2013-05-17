#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	time_t ts;
	time(&ts);
	srand((unsigned int) ts);
	int r = rand();
	printf("%d\n", r);
	return 0;
}
