# Lab 09: Cache simulator

## Overview
In this lab, you'll implement two cache replacement algorithms—First In, First Out (FIFO) and Least Recently Used (LRU)—and run some experiments to study how the algorithms perform under various workloads.

Please complete this lab **on your own**.

### Learning objectives
After completing this lab, you should be able to:
* Determine whether memory accesses will result in a cache hit or a cache miss
* Explain how an item is selected for eviction under various cache replacement algorithms
* Explain what metadata a cache must track in order to implement various cache replacement algorithms

## Getting started
Create a new codespace for this assignment.

Run `make` to compile the code, and run a command similar to the following to run the cache simulator:
```bash
LD_LIBRARY_PATH=. ./cache fifo 3 traces/test.txt
```

## Part 1: Implementing cache replacement algorithms
Your first task is to complete the `fifo_miss`, `lru_miss` and `lru_hit` functions in `cache.c`.

We have provided you with a partially written cache simulator (in `cache.c`).

The simulator takes as input:
* Which replacement algorithm to use: `fifo` or `lru`
* How many entries the cache holds
* A path to a file containing a sequence of unsigned integers that correspond to memory locations that are accessed by a program

A cache is represented by a `struct cache` (defined in `cache.h`), which contains:
* A linked-list of cache `entries`, where each entry stores a memory location—we have provided a [library of functions that can be used to manage the list](#list-functions)
* The maximum number of entries the cache can hold (i.e., its `capacity`)
* Pointers to functions for handling a cache `miss` and a cache `hit`

The `struct cache` is initialized in `main` in `cache.c` based on the provided input. Then, `main` calls the `simulate` method to process the memory locations listed in the file. 

If a memory location does not already exist in the cache, then the miss function for the selected cache replacement algorithm (`fifo_miss` or `lru_miss`) is called. Otherwise, the appropriate hit function (`fifo_hit` or `lru_hit`) is called. Each cache replacement algorithm handles cache misses and cache hits as follows:

### First In First Out (FIFO)
When a cache miss occurs:
* If the current number of cache entries has not yet reached the cache's `capacity`, then the new memory location is simply added to the cache. `fifo_miss` should return `EVICT_NONE` since no entry is evicted.
* Otherwise, the oldest entry in the cache is removed and the new memory location is added to the cache. `fifo_miss` should return the memory location that was stored in the evicted entry.

It is important for the cache entries to be ordered according to when they were added to the cache, such that the oldest entry is at the beginning of the list and the newest entry is at the end of the list.

A cache hit does not change the order in which entries are selected for eviction, so nothing needs to be done to the cache entries when a cache hit occurs.

### Least Recently Used (LRU)
When a cache miss occurs:
* If the current number of cache entries has not yet reached the cache's `capacity`, then the new memory location is simply added to the cache. `lru_miss` should return `EVICT_NONE` since no entry is evicted.
* Otherwise, the least recently accessed memory location is removed from the cache, and the new memory location is added to the cache. `lru_miss` should return the memory location that was stored in the evicted entry.

It is important for the cache entries to be ordered according to the order in which the corresponding memory locations were accessed, such that the least recently used entry is at the beginning of the list and the most recently used entry is at the end of the list.

When a cache hit occurs, the order of the cache entries must be updated to maintain the aforementioned ordering.

### List Functions
We have provided a library of functions for managing linked lists, which includes:
* `struct list *list_new()`—creates a new, empty list
* `void list_free(struct list *lst)`—deallocates a list and all of its nodes
* `int list_length(struct list *lst)`—returns the current number of nodes in the list
* `void list_append(struct list *lst, int value)`—adds a new node with the provided value to the end of the list
* `void list_insert(struct list *lst, int value, unsigned int idx)`—adds a new node with the provided value at the specified index; if the index is greater than or equal to the length of the list, the node is added to the end of the list
* `int list_index(struct list *lst, int value)`—returns the index of the first node in the list containing the specified value, or -1 if the value does not exist in the list
* `int list_pop(struct list *lst, unsigned int idx)`—removes the node at the specified index and returns the value contained in that node; triggers an assertion failure if the index is invalid
* `void list_remove(struct list *lst, int value)`—removes the first node in the list containing the specified value; the list is not modified if the value does not exist in the list

### Testing
You can test your miss and hit functions using the sequence of memory accesses in the `traces/test.txt` file with a cache size of `3`. The commands to run and the expected output is shown below.

```bash
$ LD_LIBRARY_PATH=. ./cache fifo 3 traces/test.txt
Miss 1
Miss 2
Miss 3
 Hit 1
Miss 4 (evicted 1)
 Hit 3
Miss 1 (evicted 2)
Miss 2 (evicted 3)
Miss 3 (evicted 4)
 Hit 2
Hit Ratio: 30%
```

```bash
$ LD_LIBRARY_PATH=. ./cache lru 3 traces/test.txt
Miss 1
Miss 2
Miss 3
 Hit 1
Miss 4 (evicted 2)
 Hit 3
 Hit 1
Miss 2 (evicted 4)
 Hit 3
 Hit 2
Hit Ratio: 50%
```

## Part 2: Experimenting with cache replacement algorithms
Use your cache simulator and the provided sequences of memory accesses (in the `traces` folder) to answer the questions in `questions.md`.

## Submission
Push changes in your `cache.c` and `questions.md` files to git by **11:59 PM on Friday, October 30**.
