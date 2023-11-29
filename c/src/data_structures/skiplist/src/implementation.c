#include "./interface.h"


void cstd_skiplist_initialize(CstdSkipList list, Index max_depth)
{
    while(max_depth) {
        struct CstdSkipList head_prototype = {
            .object = 0,
            .next = 0,
            .depth = max_depth
        };
        *list = head_prototype;
        list += 1;
        max_depth -= 1u;
    }
}

CstdSkipList cstd_skiplist_head(CstdSkipList list)
{
    while(list -> depth != 1u) list += 1;
    return list -> next;
}

void cstd_skiplist_push(CstdSkipList list, CstdSkipList new_element, Comparator cmp)
{
    Index depth;
    void *object;
    {
        struct CstdSkipList base_element = *new_element;
        depth = base_element.depth;
        object = base_element.object;

        base_element.next = 0;

        for(Index i = 0u; i < depth; i++) {
            new_element[i] = base_element;
            base_element.depth -= 1u;
        }
    }

    CstdSkipList head = list;
    if(depth == 0u || depth > head->depth) return;

    while(depth < head->depth)
        head += 1;

    for(Index i = 0u; i < depth; i++) {
        CstdSkipList cursor = head;
        for(;;) {
            CstdSkipList seek_next = cursor->next;
            const int comparison = seek_next ? cmp(object, seek_next->object) : -1;
            if(comparison <= 0) {
                break;
            } else {
                cursor = seek_next;
            }
        }
        new_element[i].next = cursor -> next;
        cursor -> next = new_element + i;
        head = cursor + 1;
    }
}
