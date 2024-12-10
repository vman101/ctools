/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:11:25 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/11 11:40:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

void	prompt_print_custom_string_internal(char *string)
{
	ft_putstr_fd(string, STDOUT_FILENO);
}
