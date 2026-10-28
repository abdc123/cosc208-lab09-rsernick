/****
 * Lab 09: Cache simulator
 * COSC 208, Introduction to Computer Systems, Fall 2026
 ****/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "cache.h"

/**
 * Update the cache's state when a First In First Out (FIFO) replacement 
 * algorithm is used and a cache miss occurs. Return the memory location stored
 * in the evicted entry, or EVICT_NONE if no entry is evicted.
 */
int fifo_miss(struct cache *c, unsigned int to_insert) {    
    struct list *l = c -> entries;
    list_append(l, to_insert);
    int len = list_length(l);

    if(len > c -> capacity){
        return list_pop(l, 0);
    }

    return EVICT_NONE;
}

/**
 * Update the cache's state when a First In First Out (FIFO) replacement 
 * algorithm is used and a cache hit occurs.
 * 
 * Note: to_find is a memory location, not an index
 */
void fifo_hit(struct cache *c, unsigned int to_find) {    
    // DO NOTHING
    return;
}

/**
 * Update the cache's state when a Least Recently Used (LRU) replacement
 * algorithm is used and a cache miss occurs. Return the memory location stored
 * in the evicted entry, or EVICT_NONE if no entry is evicted.
 */
int lru_miss(struct cache *c, unsigned int to_insert) {    
    struct list *l = c -> entries;
    int len = list_length(l);
    list_append(l, to_insert);
    if(len > c -> capacity){
        return (list_pop(l, len - 1));
    }
    return EVICT_NONE;
}

/**
 * Update the cache's state when a Least Recently Used (LRU) replacement 
 * algorithm is used and a cache hit occurs.
 *
 * Note: to_find is a memory location, not an index
 */
void lru_hit(struct cache *c, unsigned int to_find) {    
    struct list *l = c -> entries;
    list_prepend(l ,list_pop(l, list_index(l, to_find)));
    return;
}

/**
 * Run a cache simulation
 */
void simulate(struct cache *c, FILE *data) {    
    int hits = 0;
    int misses = 0;
    unsigned int memloc = -1;

    // Process the sequence of memory locations in listed in the file
    int result = fscanf(data, "%u", &memloc);
    while (result != EOF) {
        // Look for the desired memory location in the cache
        int idx = list_index(c->entries, memloc);
        if (idx < 0) {
            // Handle cache miss
            int evicted = c->miss(c, memloc);
            printf("Miss %d", memloc);
            if (evicted >= 0) {
                printf(" (evicted %d)\n", evicted);
            } else {
                printf("\n");
            }
            misses++;
        } else {
            // Handle cache hit
            c->hit(c, memloc);
            printf(" Hit %d\n", memloc);
            hits++;
        }
        result = fscanf(data, "%d", &memloc);
    }

    // Compute the cache hit ratio
    int ratio = hits * 100 / (hits + misses);
    printf("Hit Ratio: %d%%\n", ratio);
}

int main(int argc, char *argv[]) {    
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: cache (fifo|lru) SIZE TRACE_FILEPATH\n");
        return 1;
    }
    char *algorithm = argv[1];
    char *size = argv[2];
    char *filepath = argv[3];

    // Initialize cache
    struct cache c;
    if (0 == strncmp(algorithm, "fifo", 5)) {
        c.hit = &fifo_hit;
        c.miss = &fifo_miss;
    } else if (0 == strncmp(algorithm, "lru", 5)) {
        c.hit = &lru_hit;
        c.miss = &lru_miss;
    } else {
        printf("ERROR: replacement algorithm must be one of the following: fifo, lru\n");
        return 1;
    }
    c.capacity = atoi(size);
    if (c.capacity <= 0) {
        printf("ERROR: cache size must be greater than 0\n");
        return 1;
    }
    c.entries = list_new();

    // Run simulation 
    FILE *data = fopen(filepath, "r");
    if (data == NULL) {
        printf("ERROR: invalid filepath: %s\n", filepath);
        return 1;
    }
    simulate(&c, data);

    // Clean up
    fclose(data);
    list_free(c.entries);
}
