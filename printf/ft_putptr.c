/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:53:53 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 20:42:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(void *ptr, int *count, int fd)
{
	void	**to_print;

	if (!ptr)
	{
		*count += ft_fprintf(fd, "(nil)");
		return ;
	}
	to_print = &ptr;
	*count += ft_printf("0x");
	ft_puthex_lower((unsigned long long)*to_print, count, fd);
}
