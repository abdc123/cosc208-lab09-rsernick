# Lab 09: Part 2: Experimenting with cache replacement algorithms

**Please limit your answers to 4 sentences or less.**

1. Briefly describe the pattern of memory accesses in each of the provided trace files.
    1. `bounce.txt`
        Memory with spatial locality are recursively accessed back and forth.
    2. `scan.txt`
        Memory with spatial locality are recursively accessed only in the forwards direction
    3. `uncollated.txt`
        Memory locations are accessed multiple times in a row before moving on to the next location.

2. Run the simulator with the `bounce.txt` trace file, the `lru` replacement algorithm,  and varying cache sizes (as small as 1 and as large as 14). What do you observe about the hit ratio? How may the pattern of memory accesses impact it?

    The hit ratio increases a lot as you increase the capacity because of the structure of the memory calls. When the calls reach 13 they go back through from 13 back to 1 again and from 1 back to 13, so lru is a good algorithm because calls to memory locations are made close to each other.

3. Run the simulator with the `bounce.txt` trace file, a cache size of 10, and the `fifo` and `lru` cache replacement algorithms. What do you observe about the hit ratio between the two algorithms? How may the pattern of memory accesses impact it?

    fifo has a much lower hit ratio, because once capacity is reached and the memory calls start to reverse direction the cache removes memory locations that will be called in the next few lines. lru has a higher hit ratio because the least recently called location is removed and the least recently called location is the location that will be called again furthest in the future.

4. Run the simulator with the `scan.txt` trace file, `lru` replacement algorithm, and cache sizes of 12, 13, and 14. What do you observe about the hit ratio as you change cache sizes? How may the pattern of memory accesses impact it?

    lru does not work for scan at all if the capaciity is not the entire size of the list because the next call to a memory location is 13 calls away so it is removed from the cache before it is called again.

5. Run the simulator with the `uncollated.txt` trace file, the `lru` replacement algorithm, and varying cache sizes (as small as 1 and as large as 14). What do you observe about the hit ratio as you change cache sizes? How may the pattern of memory accesses impact it?

    Both lru and fifo reach maximum hit ratio with a cache size of only 1 because each location is called multiple times in a row and then not called again so when a new location is found it is stored and then it is called multiple times then the next location is called and stored then called multiple times.
