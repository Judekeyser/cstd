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

int cstd_ringbuffer_write(CstdRingBuffer restrict self, Index * restrict index);

int cstd_ringbuffer_read(CstdRingBuffer restrict self, Index * restrict index);

int cstd_ringbuffer_is_empty(const CstdRingBuffer self);

int cstd_ringbuffer_is_full(const CstdRingBuffer self);

#endif
