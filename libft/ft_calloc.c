#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned long long	sum;
	void				*ptr;

	sum = count * size;
	ptr = (void *)malloc(sum);
	if (ptr)
		ft_memset(ptr, '\0', sum);
	return (ptr);
}
