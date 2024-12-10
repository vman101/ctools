/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_blocking_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:14:46 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 21:21:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

#include <windows.h>

void blocking_mode_toggle(int fd, int enable)
{
	HANDLE hStd;
	DWORD mode;
	
	if (fd == 0)
	{
		hStd = GetStdHandle(STD_INPUT_HANDLE);
	}
	else if (fd == 1)
	{
		hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else
	{
		return ;
	}
	if (hStd == INVALID_HANDLE_VALUE)
	{
	    fprintf(stderr, "Error getting standard input handle." NL);
	    exit(1);
	}
	
	if (!GetConsoleMode(hStd, &mode))
	{
	    fprintf(stderr, "Error getting console mode." NL);
	    exit(1);
	}
	if (enable)
	{
		mode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	}
	else
	{
	    mode |= (ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	}
	
	if (!SetConsoleMode(hStd, mode))
	{
	    fprintf(stderr, "Error setting console mode." NL);
	    exit(1);
	}
}

#else

# include <sys/ioctl.h>

void	blocking_mode_toggle(int fd, int flag)
{
	if (ioctl(fd, FIONBIO, &flag) == -1)
	{
		perror("ioctl");
		exit(1);
	}
}

#endif
