/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:46:26 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 21:22:01 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stdlib.h>
# include "../libft/libft.h"

enum e_alloc
{
	ADD,
	FAIL,
	END,
	FREE,
	AT_EXIT,
};

void	lst_memory(void *mem, void (*del)(void *c), int mode);

#endif
