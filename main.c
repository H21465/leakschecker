#include <stdio.h>
#include <stdlib.h>
#include "leakdetect.h"

#define LEAK_DETECT
#ifdef LEAK_DETECT
# define init leak_detect_init
# define malloc(s) leak_detelc_malloc(s, __FILE__, __LINE__)
# define free leak_detect_free
# define check leak_detect_check
#else
# define init()
# define check()
#endif

int	main(void)
{
	int	*p[8];

	init();
	p[0] = (int *)malloc(sizeof(int));
	p[1] = (int *)malloc(sizeof(int));
	p[2] = (int *)malloc(sizeof(int));
	p[3] = (int *)malloc(sizeof(int));
	p[4] = (int *)malloc(sizeof(int));
	p[5] = (int *)malloc(sizeof(int));
	p[6] = (int *)malloc(sizeof(int));
	p[7] = (int *)malloc(sizeof(int));
	free(p[4]);
	free(p[7]);
	check();
	return (0);
}
