/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_get_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:00:19 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/10 21:29:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

char	*find_next_match(	char *current_word, \
								uint32_t current_word_length)
{
	(void)current_word_length, (void)current_word;
	ft_printf("UNIMPLEMENTED: %s %s" NL, __FILE__, __LINE__);
	return (NULL);
}

uint32_t	get_current_word_length(char *word)
{
	char	*word_end;

	if (!word)
		return (0);
	else if (*word == ' ')
		return (1);
	word_end = ft_strchr(word, ' ');
	if (word_end)
		return (word_end - word);
	return (ft_strlen(word));
}

void	prompt_get_next_word_match_internal(char **input, t_prompt *prompt, char *input_path, bool *is_directory)
{
	(void)input, (void)prompt,(void)input_path, (void)is_directory;
	ft_printf("UNIMPLEMENTED: %s %s" NL, __FILE__, __LINE__);
}
