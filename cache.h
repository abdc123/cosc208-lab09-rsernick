/****
 * Lab 09: Cache simulator
 * COSC 208, Introduction to Computer Systems, Fall 2026
 ****/

#ifndef __CACHE_H__
#define __CACHE_H__

#include "list.h"

#define CACHE_HIT -2
#define EVICT_NONE -1 

struct cache {
    struct list *entries;
    int capacity;
    int (*miss)(struct cache *, unsigned int);
    void (*hit)(struct cache *, unsigned int);
};

int lru_miss(struct cache *, unsigned int);
void lru_hit(struct cache *, unsigned int);
int fifo_miss(struct cache *, unsigned int);
void fifo_hit(struct cache *, unsigned int);

#endif // __CACHE_H__
