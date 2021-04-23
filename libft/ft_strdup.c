#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		lenchar;
	char	*malchar;

	lenchar = ft_strlen(s1);
	malchar = (char *)malloc(sizeof(char) * lenchar + 1);
	if (malchar == (void *)0)
		return (malchar);
	while (lenchar >= 0)
	{
		malchar[lenchar] = s1[lenchar];
		--lenchar;
	}
	return (malchar);
}
