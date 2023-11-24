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

int cstd_ringbuffer_write(CstdRingBuffer self, Index *index)
{
    struct CstdRingBuffer this = *self;

    if(this.capacity + this.read_cursor == this.write_cursor) {
        return 1;
    } else {
        *index = this.write_cursor - (
            this.write_cursor >= this.capacity ? this.capacity : 0u
        );

        this.write_cursor += 1u;

        *self = this;
        return 0;
    }
}

int cstd_ringbuffer_read(CstdRingBuffer self, Index *index)
{
    struct CstdRingBuffer this = *self;

    if(this.read_cursor == this.write_cursor) {
        return 1;
    } else {
        *index = this.read_cursor - (
            this.read_cursor >= this.capacity ? this.capacity : 0u
        );

        this.read_cursor += 1u;
        if(this.read_cursor >= this.capacity) {
            this.read_cursor -= this.capacity;
            this.write_cursor -= this.capacity;
        }

        *self = this;
        return 0;
    }
}

Index cstd_ringbuffer_length(CstdRingBuffer self)
{
    return self->write_cursor - self->read_cursor;
}
