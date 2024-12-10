/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:47:33 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/11 11:53:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "list.h"
# include "memory.h"
# include <stdlib.h>
# include <stdio.h>

void	lst_memory(void *mem, void (*del)(void *c), int mode)
{
	static t_clean	*list;
	t_clean			*new;

	if (mode == FAIL)
		return (lst_list_clean(&list), exit(EXIT_FAILURE));
	else if (mode == END)
		return (lst_list_clean(&list));
	else if (mode == FREE)
		return (lst_node_del_clean(&list, mem));
	else if (!mem && mode != AT_EXIT)
		return (lst_list_clean(&list), perror("malloc"), exit(EXIT_FAILURE));
	new = lst_node_new(mem, del);
	if (!new)
		return (del(mem), lst_list_clean(&list), \
				perror(""), exit(EXIT_FAILURE));
	lst_add_back(&list, new);
}
