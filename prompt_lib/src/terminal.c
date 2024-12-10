/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:56:10 by marvin            #+#    #+#             */
/*   Updated: 2024/11/11 14:26:30 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

#ifdef _WIN32

void		terminal_raw_mode_enable_internal(void)
{
	HANDLE hStd = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;

	GetConsoleMode(hStd, &mode);
	mode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT);
	mode |=  ENABLE_VIRTUAL_TERMINAL_INPUT;
	SetConsoleMode(hStd, mode);
	_setmode(_fileno(stdin), _O_RAW);
}

void		terminal_raw_mode_disable_internal(void)
{
	HANDLE hStd = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;

	GetConsoleMode(hStd, &mode);
	mode |= (ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);
	mode &= ~(ENABLE_PROCESSED_INPUT | ENABLE_VIRTUAL_TERMINAL_INPUT);
	SetConsoleMode(hStd, mode);
	_setmode(_fileno(stdin), _O_TEXT);
}

#else

void	terminal_raw_mode_enable_internal(void)
{
	struct termios	raw;

	if (isatty(0) && isatty(1))
	{
		tcgetattr(STDIN_FILENO, &raw);
		raw.c_lflag &= ~(ECHOCTL | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
}

void	terminal_raw_mode_disable_internal(void)
{
	struct termios	orig;

	if (isatty(0) && isatty(1))
	{
		tcgetattr(STDIN_FILENO, &orig);
		orig.c_lflag |= (ECHO | ECHOCTL | ICANON);
		tcsetattr(STDIN_FILENO, TCSANOW, &orig);
	}
}

#endif
