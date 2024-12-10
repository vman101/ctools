/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:06:24 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/11 12:22:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

# include <io.h>
# include <fcntl.h>

int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
{
	int64_t	bytes_read;
	char	*tmp;

	if (fd == 0)
		fd = _fileno(stdin);
	else if (fd == 1)
		fd = _fileno(stdout);
	bytes_read = _read(fd, character, size_to_read);
	if (bytes_read == -1)
	{
		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
			return (0);
		perror("read");
		lst_memory(NULL, NULL, FAIL);
	}
	if ((tmp = ft_strrchr(character, '\r')))
	{
		*tmp = '\n';
	}
	return (bytes_read);
}

// int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
// {
// 	int64_t	bytes_read;
// 	char	*tmp;
//
// 	if (fd == 0)
// 		fd = _fileno(stdin);
// 	else if (fd == 1)
// 		fd = _fileno(stdout);
// 	bytes_read = _read(fd, character, size_to_read);
// 	if (bytes_read > 0)
// 	{
// 		character[bytes_read] = '\0';
// 		tmp = ft_strrchr(character, '\r');
// 		if (tmp && (tmp - character < bytes_read - 1) && *(tmp + 1) == '\n')
// 		{
// 			ft_memmove(tmp, tmp + 1, bytes_read - (tmp - character) - 1);
// 			bytes_read--;
// 		}
// 	}
// 	if (bytes_read == -1)
// 	{
// 		if (errno == EINTR || errno == EAGAIN || errno == EWOULDBLOCK)
// 			return (0);
// 		perror("read");
// 		lst_memory(NULL, NULL, FAIL);
// 	}
// 	return (bytes_read);
// }
//

# else

# include <unistd.h>

int64_t	ft_read(int fd, char *character, uint32_t size_to_read)
{
	int64_t	bytes_read;

	bytes_read = read(fd, character, size_to_read);
	if (bytes_read == -1)
	{
		if (errno == EINTR \
			|| errno == EAGAIN \
			|| errno == EWOULDBLOCK)
			return (0);
		perror("read");
		lst_memory(NULL, NULL, FAIL);
	}
	return (bytes_read);
}

#endif
