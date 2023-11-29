#include <stdio.h>
#include <assert.h>

/**
 * This module illustrates how to use a RingBuffer abstraction
 * to make it work along with data. In this example, we use a `char[]` data storage,
 * although different combination are possible.
 *
 * Resizing the data chunk is not a concern here, and might be handled by another
 * proxy or a specific error handling when writing into the buffer.
 * The `cstd_ringbuffer_initialize` method would be called with the new capacity.
 */

typedef size_t Index;
#include "./src/implementation.c"

struct CharRingBuffer
{
    struct CstdRingBuffer ring_algebra;
    char data[6];
};

static Index length(struct CharRingBuffer *buffer)
{
    const Index read = (buffer -> ring_algebra).read_cursor;
    const Index write = (buffer -> ring_algebra).write_cursor;
    return write - read;
}

int write(struct CharRingBuffer *buffer, char character)
{
    Index index;
    int error = cstd_ringbuffer_write(&(buffer->ring_algebra), &index);

    if(!error) {
        buffer->data[index] = character;
    }

    return error;
}

int read(struct CharRingBuffer *buffer, char *character)
{
    Index index;
    int error = cstd_ringbuffer_read(&(buffer->ring_algebra), &index);

    if(!error) {
        *character = buffer->data[index];
    }

    return error;
}

void init(struct CharRingBuffer *buffer)
{
    cstd_ringbuffer_initialize(
        &(buffer -> ring_algebra),
        sizeof(buffer -> data)/sizeof(*(buffer -> data))
    );
}

/* -------- TEST SCENARIO --------*/

int main()
{
    printf("* Test scenario for RingBuffer interface *\n");
    int error;
    struct CharRingBuffer _buffer;
    struct CharRingBuffer *buffer = &_buffer;
    init(buffer);

    assert(length(buffer) == 0);

    error = write(buffer, 'H')
         || write(buffer, 'e')
         || write(buffer, 'l')
         || write(buffer, 'l')
         || write(buffer, 'o')
    ;
    assert(!error);
    assert(length(buffer) == 5);

    error = write(buffer, '\0');
    assert(!error);
    assert(length(buffer) == 6);

    error = write(buffer, '?');
    assert(error);
    assert(length(buffer) == 6);

    char bucket;
    error = read(buffer, &bucket);
    assert(!error);
    assert(bucket == 'H');
    assert(length(buffer) == 5);

    error = read(buffer, &bucket)
         || read(buffer, &bucket)
         || read(buffer, &bucket)
         || read(buffer, &bucket)
         ;
    assert(!error);
    assert(bucket == 'o');
    assert(length(buffer) == 1);

    error = write(buffer, '!');
    assert(!error);
    assert(length(buffer) == 2);

    error = read(buffer, &bucket) || read(buffer, &bucket);
    assert(!error);
    assert(length(buffer) == 0);
    assert(bucket == '!');

    error = read(buffer, &bucket);
    assert(error);
    assert(length(buffer) == 0);
    printf("    All good\n");
}
