#ifndef CSTD_SKIP_LIST
#define CSTD_SKIP_LIST


typedef struct CstdSkipList * CstdSkipList;
struct CstdSkipList
{
    void *object;
    CstdSkipList next;
    Index depth;
};

typedef int(*Comparator)(const void *x, const void *y);

#endif
