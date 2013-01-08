#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <sys/time.h>
#include "vector.h"

int main(int argc, char **argv)
{
    int i, len;
    int value;
    vector_ptr v;
    int data[] = {100, 200, 300, 500, 1000, 5000, 8000, 12000};
    
    struct timeval tv_start, tv_end;
    double d_start, d_end;
    
    /* Setup Random */
    gettimeofday(&tv_start, NULL);
    srand(tv_start.tv_usec);
    
    v = vector_new(1024, sizeof(int));
    gettimeofday(&tv_start, NULL);
    for (i = 0; i < 1000; i++) {
        value = random();
        vector_append(v, &value);
    }
    
    gettimeofday(&tv_end, NULL);
    
    d_start = tv_start.tv_sec + (tv_start.tv_usec / 1000000.0);
    d_end = tv_end.tv_sec + (tv_end.tv_usec / 1000000.0);
    printf("Time: %2.8f\n", (d_end - d_start));
    
    /*
    vector_del(v, 3);
    len = vector_get_len(v);
    for (i = 0; i < len; i++) {
        printf("%d\n", *(int*)vector_getptr(v, i));
    }
    */
    
    vector_delete(v);
    exit(0);
}
