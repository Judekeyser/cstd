#ifndef CSTD_RING_BUFFER
#define CSTD_RING_BUFFER


struct CstdRingBuffer
{
    Index capacity;
    Index read_cursor;
    Index write_cursor;
};
typedef struct CstdRingBuffer * CstdRingBuffer;

void cstd_ringbuffer_initialize(CstdRingBuffer self, Index capacity);

int cstd_ringbuffer_write(CstdRingBuffer self, Index *index);

int cstd_ringbuffer_read(CstdRingBuffer self, Index *index);

Index cstd_ringbuffer_length(CstdRingBuffer self);

#endif
