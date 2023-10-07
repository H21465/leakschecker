#ifndef LEAKDETECT_H
# define LEAKDETECT_H

# include <stdlib.h>


# define MAX_NUM 500

typedef struct s_mem
{
	void			*ptr;
	size_t			size;
	const char		*file;
	unsigned int	line;
}	t_mem;

void	leak_detect_init(void);
void	*leak_detelc_malloc(size_t size, const char *file, unsigned int line);
void	leak_detect_free(void *ptr);
void	leak_detect_check(void);


#endif