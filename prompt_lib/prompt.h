/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvobis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 14:40:41 by vvobis            #+#    #+#             */
/*   Updated: 2024/12/10 21:19:14 by vvobis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <stdlib.h>
# include <sys/types.h>
# include <stdint.h>
# include <stdio.h>
# include "../memory/memory.h"
# include <errno.h>
# include "../printf/ft_printf.h"
# include "../libft/libft.h"
# include <fcntl.h>

# include <stdbool.h>


# ifdef _WIN32

#  include <windows.h>
#  include <io.h>

#  define NL "\r\n"

#  undef STDOUT_FILENO
#  undef STDIN_FILENO

#  define STDIN_FILENO _fileno(stdin)
#  define STDOUT_FILENO _fileno(stdout)

# else

#  include <unistd.h>
#  include <termios.h>
#  define NL "\n"

# endif

# define EOT 4
# define ESC 27
# define DEL 127

# define SCREEN_DISBLE_WRAPPING "\033[?7l"
# define SCREEN_ENABLE_WRAPPING "\033[?7h"
# define SCREEN_CLEAR_TO_EOL "\033[K"
# define SCREEN_CLEAR "\033[2J"
# define SCREEN_CLEAR_TO_EOF "\033[J"

# define PROMPT_COMMAND_STACK_SIZE 16
# define PROMPT_INPUT_BUFFER_SIZE 4096
# define CURSOR_MOVE_HOME "\033[H"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define CURSOR_MOVE_UP "\033[A"
# define CURSOR_MOVE_DOWN "\033[B"
# define CURSOR_MOVE_RIGHT "\033[C"
# define CURSOR_MOVE_LEFT "\033[D"
# define CURSOR_POSITION_GET "\033[6n"
# define CURSOR_POSITION_SET "\033[%d;%dH"
# define CURSOR_POSITION_SAVE "\033[s"
# define CURSOR_POSITION_RESTORE "\033[u"

# define BUFFER_CAPACITY 64

typedef struct s_history_buffer
{
	uint32_t	write;
	uint32_t	read;
	uint32_t	buffer_capacity;
	char		*buffer[BUFFER_CAPACITY];
}	t_history_buffer;

typedef struct s_prompt
{
	bool				exists;
	char				*prompt;
	t_history_buffer	history;
	uint32_t			cursor_position[2];
	void				(*prompt_display_func)(char *);
	uint32_t			prompt_length;
	char				*command;
}	t_prompt;

/* The Main function, all other ones shouldnt be used outside this module */
/* Returns string of input that has to be freed. Internally, this stores a static prompt struct */
/* that stores the current state and history of the input buffer	*/
char		*prompt_get(const char *prompt);
void		prompt_destroy(void *prompt);

int64_t		ft_read(int fd, char *character, uint32_t size_to_read);

t_prompt	prompt_create_internal(const char *prompt);
char		*prompt_get_input_internal(t_prompt *prompt, uint32_t prompt_initial_size, const char *delimiter);

uint32_t	prompt_display_string_set_internal(t_prompt *prompt, const char *prompt_string);
void		prompt_print_custom_string_internal(char *string);

/* Cursor Manipulation */
void		cursor_position_get(uint32_t cursor_position[2]);
void		cursor_position_save(void);
void		cursor_position_restore(void);
void		cursor_position_set(uint32_t row, uint32_t column);

/* Prompt Buffer Management */
bool		prompt_handle_escape_sequence_internal(t_prompt *prompt, char buffer[], char **input, uint32_t cursor_position[2]);
bool		prompt_handle_new_character_to_input_internal(char **input, char character, uint32_t *cursor_position, uint32_t prompt_length);
uint8_t		prompt_handle_single_char_input_internal(char **input, char buffer[], uint32_t cursor_position[2], bool *do_refresh);
bool		prompt_handle_multiple_character_internal(char **input, char buffer[], uint32_t cursor_position[2], uint32_t prompt_length);
void		prompt_handle_rapid_input_internal(char buffer[], uint32_t cursor_position[2], char **input, uint32_t cursor_position_base);
void		prompt_handle_backspace_internal(		char *input, uint32_t *cursor_position_current, uint32_t input_length_current);
void		prompt_refresh_line_internal(char *input, uint32_t cursor_position_base, uint32_t cursor_position[2]);
char		*buffer_size_manage(char **input, uint32_t old_size, uint32_t size_to_add, uint32_t scalar);
void		prompt_src_string_insert_internal(char *string_to_insert, char **current_input, char *position_to_insert, uint32_t current_word_length);

/* Non Blocking mode */
void		blocking_mode_toggle(int fd, int flag);

/* Tab Completion */
void		prompt_handle_tab_internal(char **input, t_prompt *prompt);
void		prompt_handle_tab_no_match_internal(const char *input_path, uint32_t cursor_position_current[2], t_prompt *prompt);
void		prompt_handle_tab_yes_match_internal(t_prompt *prompt, const char *next_word_match, char **input, uint32_t current_word_length);
char		*prompt_determine_word_internal(char *input, char **input_path, uint32_t cursor_position_current);
void		prompt_get_next_word_match_internal(char **input, t_prompt *prompt, char *input_path, bool *is_directory);

/* Termios */
void		terminal_raw_mode_enable_internal(void);
void		terminal_raw_mode_disable_internal(void);

#endif
