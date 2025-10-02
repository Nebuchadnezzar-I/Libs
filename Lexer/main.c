#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define ARENA_SIZE 1000

struct Arena {
    long size;
    long index;
    char* base;
};

int main(void) {
    FILE *fp;
    int iterator;
    char symbol;
    struct Arena *arena;

    arena = malloc(sizeof(struct Arena));
    memset(arena, 0xcd, sizeof(struct Arena));
    arena->size = ARENA_SIZE;
    arena->index = 0;
    arena->base = malloc(ARENA_SIZE);
    memset(arena->base, 0xcd, ARENA_SIZE);

    fp = fopen("./input/main.sa", "r");
    assert(fp != NULL && "FP is null.");

    while((symbol = getc(fp)) != EOF && arena->index < ARENA_SIZE) {
        arena->index += 1;
        arena->base[arena->index] = symbol;
    }

    fclose(fp);
    return 0;
}
