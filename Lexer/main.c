#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define ARENA_SIZE 1000

enum TokenKind {
    TK_U32 = 0, 
    TK_LPAREN = 1, TK_RPAREN = 2,
    TK_LSQLR = 3, TK_RSQRL = 4,
    TK_SEMICOL = 5,
    TK_IDENT = 6
};

struct Arena {
    long size;
    long index;
    char* base;
};

struct Token {
    enum TokenKind kind;
    char* val;
};

int 
is_waste(char ch) {
    switch(ch) {
        case '\n': case '\r': case ' ': case '\t': {
            return 0;
        } break;
    }

    return 1;
}

int
is_number(char ch) {
    switch(ch) {
        case 0: case 1: case 2: case 3: case 4: 
        case 5: case 6: case 7: case 8: case 9: {
            return 0;
        } break;
    }

    return 1;
}

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
    arena->base[arena->index] = '\0';

    fclose(fp);

    iterator = 1;
    while((symbol = arena->base[iterator++])) {
        if(is_waste(symbol) == 0)
            continue;

        if(is_number(symbol) == 0)
            for()

        printf("Lexed char: %c\n", symbol);
    }

    return 0;
}
