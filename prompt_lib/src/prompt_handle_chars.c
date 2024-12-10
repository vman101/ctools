/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_handle_chars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:11:28 by vvobis            #+#    #+#             */
/*   Updated: 2024/11/11 13:13:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

uint8_t	prompt_handle_single_char_input_internal(	char **input, char buffer[], uint32_t cursor_position_current[2], bool *do_refresh)
{
	uint32_t	input_length_current;
	uint32_t	new_buffer_length;

	input_length_current = ft_strlen(*input);
	new_buffer_length = ft_strlen(buffer);
	if (new_buffer_length == 1)
	{
		if (ft_isprint(buffer[0]) || buffer[0] == '\n')
			return (*do_refresh = prompt_handle_new_character_to_input_internal(input, buffer[0],
											cursor_position_current, input_length_current), 1);
		else if (buffer[0] == EOT \
				&& (input_length_current == 0 \
				|| (*input)[input_length_current - 1] == '\n'))
			return (ft_putstr_fd(NL, STDIN_FILENO), \
					terminal_raw_mode_disable_internal(), \
					1);
	}
	else
	{
		*do_refresh = prompt_handle_multiple_character_internal(input, buffer, \
							cursor_position_current, input_length_current);
		return (1);
	}
	return (0);
}

bool	prompt_handle_new_character_to_input_internal(char **input, char character, uint32_t *cursor_position_current, uint32_t prompt_length_current)
{
	bool	do_refresh;

	do_refresh = false;
	*input = buffer_size_manage(input, prompt_length_current, prompt_length_current + 1, PROMPT_INPUT_BUFFER_SIZE);
	if (cursor_position_current[1] < prompt_length_current)
	{
		ft_memmove(&(*input)[cursor_position_current[1] + 1], &(*input)[cursor_position_current[1]], \
					prompt_length_current - cursor_position_current[1]);
	}
	(*input)[cursor_position_current[1]] = character;
	cursor_position_current[1]++;
	do_refresh = true;
	return (do_refresh);
}

bool	prompt_handle_multiple_character_internal(char **input, char buffer[], uint32_t cursor_position_current[2], uint32_t prompt_length_current)
{
	bool		do_refresh;
	uint32_t	buffer_length;

	do_refresh = false;
	buffer_length = ft_strlen(buffer);
	buffer_size_manage(input, prompt_length_current, prompt_length_current + buffer_length + 1, PROMPT_INPUT_BUFFER_SIZE);
	if (cursor_position_current[1] < prompt_length_current - 1)
	{
		ft_memmove(&(*input)[cursor_position_current[1] + buffer_length], &(*input)[cursor_position_current[1]], \
						prompt_length_current - cursor_position_current[1] + buffer_length);
		do_refresh = true;
	}
	ft_memcpy(&(*input)[cursor_position_current[1]], buffer, buffer_length);
	(cursor_position_current[1]) += buffer_length;
	return (do_refresh);
}

void	prompt_handle_backspace_internal(char *input, uint32_t *cursor_position_current, uint32_t input_length_current)
{
	if (cursor_position_current[1] <= 0)
		return ;
	cursor_position_current[1]--;
	ft_memmove(&input[cursor_position_current[1]], &input[cursor_position_current[1] + 1], input_length_current - cursor_position_current[1]);
	ft_putstr_fd(CURSOR_MOVE_LEFT, STDOUT_FILENO);
}

void	prompt_handle_rapid_input_internal(char buffer[], uint32_t cursor_position[2], char **input, uint32_t cursor_position_base)
{
	int32_t	bytes_read;
	bool	do_refresh;

	blocking_mode_toggle(STDIN_FILENO, 1);
	bytes_read = 1;
	do_refresh = true;
	while (bytes_read > 0)
	{
		prompt_handle_multiple_character_internal(input, buffer, cursor_position, ft_strlen(*input));
		ft_bzero(buffer, 100);
		bytes_read = ft_read(STDIN_FILENO, buffer, 99);
	}
	blocking_mode_toggle(STDIN_FILENO, 1);
	if (do_refresh)
		prompt_refresh_line_internal(*input, cursor_position_base, cursor_position);
}
