#ifndef foomemblockqhfoo
#define foomemblockqhfoo

#include <sys/types.h>

#include "memblock.h"
#include "memchunk.h"

struct pa_memblockq;

/* Parameters:
   - maxlength: maximum length of queue. If more data is pushed into the queue, data from the front is dropped
   - length:    the target length of the queue.
   - base:      a base value for all metrics. Only multiples of this value are popped from the queue
   - prebuf:    before passing the first byte out, make sure that enough bytes are in the queue
   - minreq:    pa_memblockq_missing() will only return values greater than this value
*/
struct pa_memblockq* pa_memblockq_new(size_t maxlength,
                                      size_t tlength,
                                      size_t base,
                                      size_t prebuf,
                                      size_t minreq);
void pa_memblockq_free(struct pa_memblockq*bq);

/* Push a new memory chunk into the queue. Optionally specify a value for future cancellation. This is currently not implemented, however! */
void pa_memblockq_push(struct pa_memblockq* bq, const struct pa_memchunk *chunk, size_t delta);

/* Same as pa_memblockq_push(), however chunks are filtered through a mcalign object, and thus aligned to multiples of base */
void pa_memblockq_push_align(struct pa_memblockq* bq, const struct pa_memchunk *chunk, size_t delta);

/* Return a copy of the next memory chunk in the queue. It is not removed from the queue */
int pa_memblockq_peek(struct pa_memblockq* bq, struct pa_memchunk *chunk);

/* Drop the specified bytes from the queue */
void pa_memblockq_drop(struct pa_memblockq *bq, size_t length);

/* Shorten the pa_memblockq to the specified length by dropping data at the end of the queue */
void pa_memblockq_shorten(struct pa_memblockq *bq, size_t length);

/* Empty the pa_memblockq */
void pa_memblockq_empty(struct pa_memblockq *bq);

/* Test if the pa_memblockq is currently readable, that is, more data than base */
int pa_memblockq_is_readable(struct pa_memblockq *bq);

/* Test if the pa_memblockq is currently writable for the specified amount of bytes */
int pa_memblockq_is_writable(struct pa_memblockq *bq, size_t length);

/* The time memory chunks stay in the queue until they are removed completely in usecs */
uint32_t pa_memblockq_get_delay(struct pa_memblockq *bq);

/* Return the length of the queue in bytes */
uint32_t pa_memblockq_get_length(struct pa_memblockq *bq);

/* Return how many bytes are missing in queue to the specified fill amount */
uint32_t pa_memblockq_missing(struct pa_memblockq *bq);


uint32_t pa_memblockq_get_minreq(struct pa_memblockq *bq);

#endif
