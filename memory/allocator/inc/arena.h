/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 12:45:17 by victor            #+#    #+#             */
/*   Updated: 2025/04/06 16:05:54 by victor           ###   ########.fr       */
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

typedef struct s_arena {
    void     *mem;
    size_t   cap;
    size_t   used;
    bool     grow;
    uint32_t count;
}   t_arena;

t_arena arena_create(size_t size);
t_arena arena_create_growing(size_t size);
void    *arena_alloc(t_arena *arena, size_t size);
void    arena_destroy(t_arena *arena);
void    arena_clear(t_arena *arena);
void    arena_reset(t_arena *arena);
void    arena_grow(t_arena *arena, size_t size);
void    arena_print(t_arena *arena);
void    print_memory(void *mem, size_t memstart, size_t memend);

#define ARENA_IMPLEMENTATION

# ifdef ARENA_IMPLEMENTATION


t_arena arena_create_growing(size_t size) {
    t_arena arena = {0};

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

    ptr = (uint8_t *)arena->mem + arena->used;
    arena->used += size;
    arena->count++;
    return ptr;
}

void    arena_clear(t_arena *arena) {
    arena->used = 0;
    arena->count = 0;
}

void arena_reset(t_arena *arena) {
    arena_clear(arena);
    memset(arena->mem, 0, arena->cap);
}

void    arena_destroy(t_arena *arena) {
    free(arena->mem);
    memset(arena, 0, sizeof(*arena));
}

void print_memory(void *mem, size_t memstart, size_t memend) {
    printf("---- Memory Section Start ----\n");
    for (uint32_t i = memstart; i < memend; i += DISPLAY_WIDTH) {
        printf("%p:", &((uint8_t *)mem)[i]);
        for (uint32_t j = 0; j < DISPLAY_WIDTH / 2; ++j) {
            uint16_t    val = ((uint16_t *)&(((uint8_t *)mem)[i]))[j];
            printf(" %04x", val);
        }
        printf(" ");
        printf("|");
        for (uint32_t j = 0; j < DISPLAY_WIDTH; ++j) {
            uint8_t    value = ((uint8_t *)mem)[i + j];
            if (isalnum(value)) {
                printf("%c", value);
            }
            else{
                printf(".");
            }
        }
        printf("|");
        printf("\n");
    }
    printf("---- Memory Section End ----\n");
}

void arena_print(t_arena *arena) {
    print_memory(arena->mem, 0, arena->cap);
}

# endif // !ARENA_IMPLEMENTATION
#endif // !ARENA_H
