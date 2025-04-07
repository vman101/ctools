/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:45:17 by victor            #+#    #+#             */
/*   Updated: 2025/04/05 17:07:03 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stdlib.h>
# include <stdbool.h>
# include <assert.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <ctype.h>

# define BYTE_WIDTH 8
# define DISPLAY_WIDTH sizeof((void *)0) * 2

typedef struct s_alloc {
    void    *ptr;
    size_t  size;
}   t_alloc;

typedef struct s_arena {
    void    *mem;
    size_t  cap;
    size_t  used;
    bool    grow;
}   t_arena;

t_arena arena_create(size_t size);
t_arena arena_create_growing(size_t size);
void    *arena_alloc(t_arena *arena, size_t size);
void    arena_destroy(t_arena *arena);
void    arena_clear(t_arena *arena);
void    arena_reset(t_arena *arena);
void    arena_grow(t_arena *arena, size_t size);
void    arena_print(t_arena *arena);

# ifdef ARENA_IMPLEMENTATION

t_arena arena_create_growing(size_t size) {
    t_arena arena;

    arena.cap = size;
    arena.used = 0;
    arena.mem = calloc(1, size);
    arena.grow = true;
    if (!arena.mem) {
        return (t_arena){0};
    }
    return (arena);
}

t_arena arena_create(size_t size) {
    t_arena arena = {0};

    arena.cap = size;
    arena.used = 0;
    arena.mem = calloc(1, size);
    arena.grow = false;
    if (!arena.mem) {
        return (t_arena){0};
    }
    return (arena);
}

void    arena_grow(t_arena *arena, size_t size) {
    void    *new_mem;
    uint    new_size;

    new_size = arena->cap * (size / arena->cap + 1);

    new_mem = realloc(arena->mem, new_size);
    arena->mem = new_mem;
    assert(new_mem != NULL);
    arena->cap = new_size;

    // size = 58, cap = 8
}

void    *arena_alloc(t_arena *arena, size_t size) {
    void *ptr = NULL;

    if (arena->used + size > arena->cap) {
        if (arena->grow == true) {
            arena_grow(arena, size);
        } else {
            assert(false && "Arena overflow detected");
        }
    }

    ptr = arena->mem + arena->used;
    arena->used += size;
    return ptr;
}

void    arena_clear(t_arena *arena) {
    arena->used = 0;
}

void arena_reset(t_arena *arena) {
    arena_clear(arena);
    memset(arena->mem, 0, arena->cap);
}

void    arena_destroy(t_arena *arena) {
    free(arena->mem);
    memset(arena, 0, sizeof(*arena));
}

void    arena_print(t_arena *arena) {
    printf("---- Arena Start ----\n");
    for (uint i = 0; i < arena->cap; i += DISPLAY_WIDTH) {
        printf("%p\t", arena->mem + i);
        for (uint j = 0; j < DISPLAY_WIDTH; ++j) {
            printf("%02x ", *(char *)(arena->mem + i + j));
        }
        printf("\t");
        printf("|");
        for (uint j = 0; j < DISPLAY_WIDTH; ++j) {
            uint8_t value = *(char *)(arena->mem + i + j);
            if (isalnum(value)) {
                printf("%c", value);
            } else {
                printf(".");
            }
        }
        printf("|");
        printf("\n");
    }
    printf("---- Arena End ----\n");
}

# endif // !ARENA_IMPLEMENTATION
#endif // !ARENA_H
