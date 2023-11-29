#include <stdio.h>
#include <assert.h>

/**
 * This module illustrates how to use a SkipList abstraction.
 * In this example, we use a structure type that compares like unsigned integer do.
 *
 * Memory is handled by a stack-allocator that uses the RingBuffer API defined here-aside.
 */

typedef size_t Index;
#include "./src/implementation.c"

struct Int {
    unsigned int value;
};

int int_comparator(const void *x, const void *y) {
    struct Int _x = *((struct Int *)x);
    struct Int _y = *((struct Int *)y);
    return _x.value - _y.value;
}

void iterate_all(CstdSkipList list) {
    for(CstdSkipList cursor = cstd_skiplist_head(list); cursor; cursor = cursor -> next) {
        struct Int *object = cursor -> object;
        printf(": %d", object->value);
    }
    printf("\n");
}


/* -------- TEST SCENARIO --------*/

int main()
{
    printf("* Test scenario for SkipList interface *\n");
    Comparator cmp = &int_comparator;
    struct Int data[7] = {
        { 45 },
        { 52 },
        { 46 },
        { 37 },
        { 38 },
        { 71 },
        { 45 }
    };
    struct CstdSkipList _list[2048] = {0};

    Index depths[8] = {3u, 1u, 2u, 2u, 1u, 3u, 1u, 2u};

    cstd_skiplist_initialize(_list, depths[0]);
    Index cursor = depths[0];

    for(Index i = 1u; i < sizeof(depths)/sizeof(*depths); i++)
    {
        _list[cursor].object = data+i-1;
        _list[cursor].depth = depths[i];
        cstd_skiplist_push(_list, _list + cursor, cmp);
        cursor += _list[cursor].depth;
    }

    iterate_all(_list);

    printf("    All good\n");
}
