#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle,
				size_t len)
{
	size_t	szn;

	if (!*needle)
		return ((char *)haystack);
	szn = ft_strlen(needle);
	while (*haystack && len >= szn)
	{
		len--;
		if (ft_strncmp(haystack, needle, szn) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return ((void *)0);
}
