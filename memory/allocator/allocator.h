/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor </var/spool/mail/victor>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:04:18 by victor            #+#    #+#             */
/*   Updated: 2025/04/06 16:30:24 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_H
# define ALLOCATOR_H


# include "inc/arena.h"

typedef struct s_alloc {
    void    *mem;
    size_t  size;
}   t_alloc;

typedef t_arena t_vector ;

typedef struct s_allocator {
    void        *mem;
    t_vector    allocs;
    size_t      cap;
    t_vector    free; // this will be used as Array of t_alloc
}   t_allocator;

//global allocator that will be used by this lib
static t_allocator *allocator_get(void) {
    static t_allocator a = { 0 };
    return &a;
}

void    allocator_init(size_t base_mem);
void    *alloc(uint64_t size);
void    *zalloc(uint32_t size);
void    dealloc(void *ptr);
void    allocator_shutdown(void);

#ifdef ALLOCATOR_IMPLEMENTATION

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "allocator.h"
#include <stddef.h>

void    allocator_init(size_t base_mem) {
    t_allocator *allocator = allocator_get();

    allocator->free = arena_create_growing(sizeof(t_alloc) * 1000);
    allocator->mem = calloc(base_mem, sizeof((char)0));
    allocator->allocs = arena_create_growing(sizeof(t_alloc) * 1000);
    allocator->cap = base_mem;
}

void vector_push(t_vector *vec, void *mem, size_t memsize) {
    assert(memsize < (vec->cap - vec->used));
    void *ptr = arena_alloc(vec, memsize);
    assert(ptr);
    memmove(ptr, mem, memsize);
}

void vector_pop(t_vector *vec, size_t memsize) {
    assert(memsize <= vec->used);
    memset(&((uint8_t *)vec->mem)[vec->used - memsize], 0, memsize);
}

// offset is used to know where to dereference the memory to find the value to be sorted by
void vector_insert_sorted(t_vector *vec, void *mem, uint32_t memsize, uint32_t offset) {
    uint32_t low_pos = 0;
    uint32_t high_pos = vec->count - (vec->count > 0);
    int32_t position = 0;
    t_alloc *cursor = &((t_alloc *)vec->mem)[high_pos];
    uint32_t new_alloc_size = *((uint8_t *)mem + offset);

    if (new_alloc_size > cursor->size || vec->count == 0) {
        vector_push(vec, mem, memsize);
    } else {
        while (low_pos < high_pos) {
            position = low_pos + (high_pos - low_pos) / 2;
            cursor = &((t_alloc *)vec->mem)[position];
            assert((uint8_t *)cursor - (uint8_t *)vec->mem >= 0);
            assert((uint8_t *)vec->mem + vec->used - (uint8_t *)cursor >= 0);
            if (cursor->size < new_alloc_size) {
                low_pos = position + 1;
            } else if (cursor->size > new_alloc_size) {
                high_pos = position - 1;
            } else {
                break ;
            }
        }
        void *ptr = arena_alloc(vec, memsize);
        memmove(ptr, &cursor, sizeof(*cursor) * (vec->count - low_pos));
        memmove(&cursor, mem, memsize);
    }
}

void vector_remove(t_vector *vec, uint32_t index, size_t memsize) {
    assert(index <= vec->count);
    void *item = (void *)&((uint8_t *)vec->mem)[index * memsize];
    memmove(item, (uint8_t *)item + memsize, (vec->count - index) * memsize);
    vec->count--;
    vec->used -= memsize;
}

void    *alloc(uint64_t size) {
    void *ptr = NULL;
    t_allocator *allocator = allocator_get();

    if (size > 0) {
        t_alloc     *tail = &((t_alloc *)allocator->free.mem)[allocator->free.count - (allocator->free.count > 0)];
        if (allocator->free.count > 0 && tail->size >= size) {
            assert(tail->mem);
            uint32_t    position = allocator->free.count / 2;
            t_alloc     *candidate = NULL;
            uint32_t    range = size / 20;
            uint32_t    last_pos = position;
            while (1) {
                t_alloc     *cursor = &((t_alloc *)allocator->free.mem)[position];
                if (cursor->size > size + range) {
                    if (cursor->size < candidate->size) {
                        candidate = cursor;
                    }
                    position <<= 1;
                } else if (cursor->size < size) {
                    position += position >> 1;
                } else if ((cursor->size >= size && cursor->size <= size + range) || position == last_pos) {
                    ptr = cursor->mem;
                    t_alloc new = { ptr, size };
                    t_alloc old = { (uint8_t *)ptr + size, cursor->size - size };
                    vector_insert_sorted(&allocator->allocs, &new, sizeof(new), offsetof(t_alloc, size));
                    vector_insert_sorted(&allocator->allocs, &old, sizeof(old), offsetof(t_alloc, size));
                    vector_insert_sorted(&allocator->free, &old, sizeof(old), offsetof(t_alloc, size));
                    vector_remove(&allocator->free, position, sizeof(*cursor));
                    break ;
                }
            }
        } else {
            t_alloc *tail = &((t_alloc *)allocator->allocs.mem)[allocator->allocs.count - (allocator->allocs.count > 0)];
            if (tail->mem == NULL) {
                ptr = allocator->mem;
            } else {
                ptr = (uint8_t *)tail->mem + tail->size;
            }
            t_alloc new = (t_alloc){ ptr, size };
            vector_push(&allocator->allocs, &new, sizeof(new));
        }
    }
    return ptr;
}

void *zalloc(uint32_t size) {
    uint8_t *ptr = NULL;

    ptr = alloc(size);
    for (uint i = 0; i < size; ++i) {
        ptr[i] = 0;
    }
    return ptr;
}

void    dealloc(void *ptr) {
    t_allocator *allocator = allocator_get();
    for (uint32_t i = 0; i < allocator->allocs.count; ++i) {
        if (((t_alloc *)allocator->allocs.mem)[i].mem == ptr) {
            t_alloc move = ((t_alloc *)allocator->allocs.mem)[i];
            memset(move.mem, 'X', move.size);
            vector_remove(&allocator->allocs, i, sizeof(move));
            vector_insert_sorted(&allocator->free, &move, sizeof(move), offsetof(t_alloc, size));
            break ;
        }
    }
}

void    allocator_print(void) {
    t_allocator *allocator = allocator_get();
    printf( "---- Allocator ----\n"
            "capacity: %lu\n", allocator->cap);
    printf("currently used mem: \n");
    arena_print(&allocator->allocs);
    printf("currently freed mem: \n");
    arena_print(&allocator->free);
    printf("alloc mem start: %p\n", allocator->mem);

    print_memory(allocator->mem, 0, allocator->cap);
}

void    allocator_shutdown() {
    t_allocator *allocator = allocator_get();

    arena_destroy(&allocator->free);
    arena_destroy(&allocator->allocs);
    free(allocator->mem);
    memset(allocator, 0, sizeof(*allocator));
}

#endif // ALLOCATOR_IMPLEMENTATION
#endif // !ALLOCATOR_H
