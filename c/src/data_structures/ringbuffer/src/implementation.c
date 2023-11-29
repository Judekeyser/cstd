#include "./interface.h"


void cstd_ringbuffer_initialize(CstdRingBuffer self, Index capacity)
{
    struct CstdRingBuffer this = {
        .capacity = capacity,
        .read_cursor = 0u,
        .write_cursor = 0u
    };

    *self = this;
}

int cstd_ringbuffer_write(CstdRingBuffer restrict self, Index * restrict index)
{
    if(cstd_ringbuffer_is_full(self)) {
        return 1;
    } else {
        struct CstdRingBuffer this = *self;
        const Index shift = this.write_cursor >= this.capacity ? this.capacity : 0u;

        *index = this.write_cursor - shift;

        this.write_cursor += 1u;

        *self = this;
        return 0;
    }
}

int cstd_ringbuffer_read(CstdRingBuffer restrict self, Index * restrict index)
{
    if(cstd_ringbuffer_is_empty(self)) {
        return 1;
    } else {
        struct CstdRingBuffer this = *self;
        const Index shift = this.read_cursor >= this.capacity ? this.capacity : 0u;

        *index = this.read_cursor - shift;

        this.read_cursor += 1u;
        this.read_cursor -= shift;
        this.write_cursor -= shift;

        *self = this;
        return 0;
    }
}

int cstd_ringbuffer_is_empty(const CstdRingBuffer self)
{
    return self->read_cursor == self->write_cursor;
}

int cstd_ringbuffer_is_full(const CstdRingBuffer self)
{
    return self->read_cursor + self->capacity == self->write_cursor;
}
