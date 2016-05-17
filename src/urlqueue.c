#include "urlqueue.h"

url_queue_t *url_queue_init()
{
  url_queue_t *q = (url_queue_t*)calloc(1, sizeof(url_queue_t));

  return q;
}

int url_queue_add(url_queue_t *q, char *url)
{
  if (strlen(url) > 1023) {
    fprintf(stderr, "url too long %s\n", url);
    return 1;
  }
  
}

void url_queue_clean(url_queue_t *q)
{
  if (q) {
    free(q);
  }
}
