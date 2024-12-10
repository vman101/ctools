/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:23:40 by anarama           #+#    #+#             */
/*   Updated: 2024/11/11 15:20:32 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

void	prompt_destroy(void *prompt)
{
	t_prompt	*prompt_ptr;

	prompt_ptr = (t_prompt *)prompt;
	ft_free(&prompt_ptr);
}

#ifdef _WIN32
uint32_t	prompt_display_string_set_internal(t_prompt *prompt, const char *prompt_string)
{
	uint32_t	prompt_string_length;

	prompt_string_length = ft_strlen(prompt_string);
	prompt->prompt = (char *)prompt_string;
	return (prompt_string_length);
}

#else

uint32_t	prompt_display_string_set_internal(t_prompt *prompt, const char *prompt_string)
{
	uint32_t	prompt_string_length;

	prompt_string_length = ft_strlen(prompt_string) + 1;
	prompt->prompt = (char *)prompt_string;
	return (prompt_string_length);
}

#endif
t_prompt	prompt_create_internal(char const *prompt)
{
	t_prompt	tmp;

	tmp = (t_prompt){0};
	tmp.history = (t_history_buffer){0};
	tmp.history.buffer_capacity = BUFFER_CAPACITY;
	tmp.exists = true;
	if (!prompt)
		tmp.prompt = "> ";
	tmp.prompt_display_func = prompt_print_custom_string_internal;
	return (tmp);
}

char	*prompt_get(const char *prompt)
{
	char			*input;
	static t_prompt	_prompt = {0};

	if (!_prompt.exists)
		_prompt = prompt_create_internal(prompt);
	_prompt.prompt = NULL;
	lst_memory(&_prompt, prompt_destroy, ADD);
	_prompt.prompt_length = prompt_display_string_set_internal(&_prompt, prompt);
	prompt_get_input_internal(&_prompt, PROMPT_INPUT_BUFFER_SIZE, "\n");
	if (!_prompt.command || !*_prompt.command)
		return (NULL);
	ft_putstr_fd(SCREEN_CLEAR_TO_EOF, 1);
	input = ft_strdup(_prompt.command);
	if (!input)
		return (perror("malloc"), lst_memory(NULL, NULL, FAIL), NULL);
	return (input);
}

