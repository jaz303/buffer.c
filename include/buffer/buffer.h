#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

typedef enum {
    BUFFER_OWNS_SELF    = 1,        /* buffer struct will be freed by buffer_destroy() */
    BUFFER_OWNS_DATA    = 2,        /* buffer data will be freed by buffer_destroy() */
    BUFFER_GROWABLE     = 4         /* buffer can grow dynamically to accommodate new data */
} buffer_flags_t;

typedef struct {
    int             flags;
    unsigned char   *data;
    size_t          capacity;
    size_t          written;
    size_t          read;
} buffer_t;

/* initialise an existing buffer with an existing data array of given length
 */
void        buffer_init_static(buffer_t *buffer, char *data, size_t size);

/* initial an existing buffer with dynamically allocated data array of a known size
 * implies BUFFER_OWNS_DATA
 */
int         buffer_init(buffer_t *buffer, size_t size, int flags);

/* allocate a new buffer with a given initial size and flags
 * implies BUFFER_OWNS_SELF | BUFFER_OWNS_DATA
 */
buffer_t*   buffer_create(size_t size, int flags);

/* destroy buffer - possible free()'s both data and buffer struct, depending
 * on buffer->flags */
void        buffer_destroy(buffer_t *buffer);

/* reset buffer - remove all data and reset read head to start */
void        buffer_reset(buffer_t *buffer);

/* append a single byte to buffer, returns 1 on success, 0 on failure */
int         buffer_append(buffer_t *buffer, char byte);

/* write len bytes from data to buffer. all or nothing operation; returns 0
 * if remaining capacity of buffer is < len, or 1 if write was successful */
int         buffer_write(buffer_t *buffer, const char *data, size_t len);

/* reads a single character buffer from the buffer */
char        buffer_get(buffer_t *buffer);

/* read maxlen bytes from the buffer to dest. read head is advanced by maxlen.
 * returns number of bytes read
 */
int         buffer_read(buffer_t *buffer, size_t maxlen, void *dest);

/* returns the buffer's capacity (i.e. max number of bytes it can contain) */
size_t      buffer_capacity(buffer_t *buffer);

/* returns the number of bytes which have been written to the buffer */
size_t      buffer_size(buffer_t *buffer);

/* returns number of bytes that can still be written to this buffer */
size_t      buffer_remain(buffer_t *buffer);

/* 1 = buffer empty, 0 = not empty */
int         buffer_is_empty(buffer_t *buffer);

/* 1 = buffer full, 0 = not full */
int         buffer_is_full(buffer_t *buffer);

/* get position of read head */
size_t      buffer_tell(buffer_t *buffer);

/* is read head at end of buffer? */
int         buffer_eof(buffer_t *buffer);

/* rewind read head to beginning of buffer. data in buffer is unaffected. */
void        buffer_rewind(buffer_t *buffer);

/* seek read head to arbitrary point in buffer. data is unaffected */
void        buffer_seek(buffer_t *buffer, size_t offset);

#endif