#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define ARENA_SIZE 10000
#define MAX_INPUT 1000
#define MAX_TOK 100

enum Kind {
    IDENT, NUMBER
};

struct Arena {
    char* base;
    int index;
    int size;
};

struct Token {
    enum Kind kind;
    int start;
    int end;
};

int
is_waste(char c) {
    if(c == ' ' || c == '\n' || c == '\t' || c == '\r')
        return 0;

    return 1;
}

int
is_ident(char c) {
    switch (c) {
        case 'A': case 'a': case 'B': case 'b': case 'C': case 'c': case 'D': case 'd':
        case 'E': case 'e': case 'F': case 'f': case 'G': case 'g': case 'H': case 'h':
        case 'I': case 'i': case 'J': case 'j': case 'K': case 'k': case 'L': case 'l':
        case 'M': case 'm': case 'N': case 'n': case 'O': case 'o': case 'P': case 'p':
        case 'Q': case 'q': case 'R': case 'r': case 'S': case 's': case 'T': case 't':
        case 'U': case 'u': case 'V': case 'v': case 'W': case 'w': case 'X': case 'x':
        case 'Y': case 'y': case 'Z': case 'z': return 0;
    }

    return 1;
}

int
is_number(char c) {
    switch (c) {
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        case 9: return 0;
    }

    return 1;
}

int main(void) {
    struct Arena *arena;
    struct Token *token;
    struct Token *tok;
    char symbol;
    int inp_len;
    int tok_cnt;
    FILE *fp;
    int tmp;
    int idx;

    arena = malloc(sizeof(struct Arena));
    memset(arena, 0xcd, sizeof(struct Arena));

    arena->base = malloc(ARENA_SIZE);
    arena->size = ARENA_SIZE;
    arena->index = 0;
    memset(arena->base, 0xcd, ARENA_SIZE);

    fp = fopen("input/main.sa", "r");

    while((symbol = getc(fp)) != EOF) {
        arena->base[arena->index] = symbol;
        arena->index++;
    }

    arena->base[arena->index] = '\0';
    inp_len = arena->index;

    fclose(fp);

    idx = 0;
    tok_cnt = 0;
    while ((symbol = arena->base[idx]) != '\0') {
        if(is_waste(symbol) == 0) {
            idx++;
            continue;
        }

        if(is_number(symbol) == 0) {
            tmp = 0;

            token = (struct Token *)(arena->base + arena->index);
            token->kind = NUMBER;
            token->start = idx;
            token->end = idx;
            arena->index += sizeof(struct Token);
            tok_cnt++;

            for(tmp = idx; is_waste(arena->base[tmp]) != 0; tmp++)
                token->end++;

            assert(token->end != idx && "Number token end should not be zero.");

            idx = tmp;
            continue;
        }

        if(is_ident(symbol) == 0) {
            tmp = 0;

            /*
            Maybe I could use p* and len of string not start end.
            It would be nice to get rid of tok_cnt and inp_len.
            */
            token = (struct Token *)(arena->base + arena->index);
            token->kind = IDENT;
            token->start = idx;
            token->end = idx;
            arena->index += sizeof(struct Token);
            tok_cnt++;

            for(tmp = idx; is_waste(arena->base[tmp]) != 0; tmp++)
                token->end++;

            assert(token->end != idx && "Ident end should not be zero.");

            idx = tmp;
            continue;
        }

        idx++;
    }

    for(idx = inp_len; idx < inp_len + tok_cnt * sizeof(struct Token); idx += sizeof(struct Token)) {
        tok = (struct Token *)(arena->base + idx);
        printf("Kind: %i, Start: %i, End: %i\n", tok->kind, tok->start, tok->end);
    }

    /*
    x Allocate arena (10KB)
    x Read file to part of arena (base => index)
    x     - store index to tmp
    Tokenize arena (base => tmp)
    Push T_ to arena from tmp
    */

    return 0;
}
