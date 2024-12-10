/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:48:59 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 15:08:38 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_C
# define LIST_C

# include <stdlib.h>
# include <stdio.h>

typedef struct s_clean
{
	void			*content;
	void			(*clean)(void *del);
	struct s_clean	*next;
}					t_clean;

/* List */
t_clean		*lst_node_new(void *content, void (*del)(void *));
void		lst_node_del(t_clean **lst);
void		lst_node_del_clean(t_clean **lst, void *mem);
void		lst_list_clean(t_clean **head);
int			lst_add_back(t_clean **node, t_clean *node_new);

#endif
