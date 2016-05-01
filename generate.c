#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Use whatever type is most efficient on your system.
// Values stay between 0 and 4 unless you plan to run
// this for longer than the life of the universe
typedef int term_t; 

// Compute the next term in the list
term_t max_k(term_t *lst, size_t size) {
    term_t record = 1;
    term_t cur_max;
    term_t *curr_chunk;
    size_t pos;

    for(size_t ln = 1; ln < size/2 + 1; ln++) {
        cur_max = 1;
        pos = size;
        curr_chunk = lst + pos-ln;
        pos -= ln;
        while(pos >= ln) {
            if(memcmp(curr_chunk, lst+(pos-ln), sizeof(term_t)*ln) != 0) {
                break;
            }
            cur_max += 1;
            pos -= ln;
        }
        record = record > cur_max ? record : cur_max;
    }
    return record;
}

void fast_generate(term_t *lst, size_t n) {
    size_t running_size = 1;
    term_t next;
    lst[0] = 1;

    while(running_size < n) {
        if(2*running_size <= n) {
            memcpy(lst + running_size, lst, sizeof(term_t)*running_size);
            running_size *= 2;
        } else {
            memcpy(lst + running_size, lst, sizeof(term_t)*(n - running_size));
            running_size = n;
        }
        next = max_k(lst, running_size);
        while(next != 1 && running_size < n) {
            lst[running_size] = next;
            running_size++;
            if(running_size < n) {
                next = max_k(lst, running_size);
            }
        }
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Pass in one argument (an integer)\n");
    } else {
        size_t count = atoi(argv[1]);
        term_t *buffer;

        buffer = calloc(count, sizeof(term_t));

        // Do stuff

        fast_generate(buffer, count);

        // Stop doing stuff

        for(int i = 0; i < count; i++) {
            if(i%100 == 0 && i != 0) { printf("\n"); }
            printf("%d ", buffer[i]);
        }

        free(buffer);
    }
}