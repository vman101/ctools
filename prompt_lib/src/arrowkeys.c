/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowkeys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarama <anarama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:02:39 by victor            #+#    #+#             */
/*   Updated: 2024/11/11 15:25:23 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../prompt.h"

static void	prompt_handle_arrow_key_up_internal(	t_history_buffer *history,
								char **input,
								uint32_t cursor_position_current[2])
{
	if (cursor_position_current[0] > 0)
		ft_putstr_fd(CURSOR_MOVE_UP, 1);
	if (history->read == 0)
		history->read = history->buffer_capacity - 1;
	else
		history->read -= 1;
	if (history->buffer[history->read] == 0)
	{
		history->read = (history->read + 1) % history->buffer_capacity;
		return ;
	}
	if (history->buffer[history->write] == 0)
		history->buffer[history->write] = *input;
	*input = history->buffer[history->read];
	cursor_position_current[1] = ft_strlen(*input);
}

static void	prompt_handle_arrow_key_down_internal(t_history_buffer *history, uint32_t cursor_position[2], char **input)
{
	if (history->read == history->write)
		return ;
	history->read = (history->read + 1) % history->buffer_capacity;
	*input = history->buffer[history->read];
	cursor_position[1] = ft_strlen(*input);
}

static void	prompt_handle_arrow_key_right_internal(uint32_t *cursor_position_current, uint32_t prompt_length_current, uint32_t prompt_string_length)
{
	if (cursor_position_current[1] < prompt_length_current)
		cursor_position_current[1]++;
	cursor_position_set(cursor_position_current[0], cursor_position_current[1] + prompt_string_length);
}

static void	prompt_handle_arrow_key_left_internal(	uint32_t *cursor_position_current, uint32_t prompt_string_length)
{
	if (cursor_position_current[1] > 0)
		cursor_position_current[1]--;
	cursor_position_set(cursor_position_current[0], cursor_position_current[1] + prompt_string_length);
}

bool	prompt_handle_escape_sequence_internal(t_prompt *prompt, char buffer[], char **input, uint32_t cursor_position_current[2])
{
	uint32_t	prompt_length_current;

	prompt_length_current = ft_strlen(*input);
	if (buffer[0] == 91 && buffer[1] == 65)
		return (prompt_handle_arrow_key_up_internal(&prompt->history, \
					input, cursor_position_current), 1);
	else if (buffer[0] == 91 && buffer[1] == 66)
		return (prompt_handle_arrow_key_down_internal(&prompt->history, \
					cursor_position_current, input), 1);
	else if (buffer[0] == 91 && buffer[1] == 67)
		prompt_handle_arrow_key_right_internal(cursor_position_current, prompt_length_current, prompt->prompt_length);
	else if (buffer[0] == 91 && buffer[1] == 68)
		prompt_handle_arrow_key_left_internal(cursor_position_current, prompt->prompt_length);
	return (0);
}
