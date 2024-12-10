
#include "../prompt.h"

int	is_space(char const c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char const *s)
{
	int			nb;
	char const	*tmp;

	nb = 0;
	while (is_space(*s))
		s++;
	tmp = s;
	if (*tmp == '+' || *tmp == '-')
		tmp++;
	while (*tmp >= '0' && *tmp <= '9')
	{
		nb *= 10;
		nb += (*tmp - '0');
		tmp++;
	}
	if (*s == '-')
		nb = -nb;
	return (nb);
}

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*str++)
	{
		i++;
		if (i == SIZE_MAX)
			break ;
	}
	return (i);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	char	*d;
	char	*s;

	if (n == 0 || (dest == NULL && src == NULL))
		return (dest);
	if (dest == NULL || src == NULL)
	{
		*(char *)dest = 1;
		*(char *)src = 1;
	}
	d = (char *) dest;
	s = (char *) src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (s < d)
		while (n--)
			d[n] = s[n];
	else
		ft_memcpy(dest, (void *)src, n);
	return (dest);
}

char	*ft_strchr(char const *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strrchr(char const *s, int c)
{
	char	*n;
	int		i;

	i = 0;
	n = NULL;
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			n = (char *)&s[i];
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	if (n)
		return (n);
	return (NULL);
}

void	*ft_calloc(size_t n, size_t s)
{
	char				*tmp;
	unsigned long		i;

	i = 0;
	if (n == 0)
		return (malloc(0));
	if (SIZE_MAX / n < s)
		return (NULL);
	tmp = malloc(n * s);
	if (tmp)
		while (i < n * s)
			tmp[i++] = 0;
	return ((void *)tmp);
}

int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(char const *s)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(ft_strlen(s) + 1, sizeof(*tmp));
	if (!tmp)
		return (NULL);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!s || start >= ft_strlen(s) || len <= 0)
	{
		tmp = malloc(1);
		if (!tmp)
			return (NULL);
		tmp[i] = 0;
		return (tmp);
	}
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	tmp = malloc(sizeof(*tmp) * len + 1);
	if (!tmp)
		return (NULL);
	while (i < len && s[i])
	{
		tmp[i] = s[i + start];
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
