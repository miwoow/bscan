#include "urlqueue.h"

url_queue_t *url_queue_init()
{
  url_queue_t *q = (url_queue_t*)calloc(1, sizeof(url_queue_t));
  q->ll = blist_init(10);
  return q;
}

int url_queue_add(url_queue_t *q, char *url)
{
  if (strlen(url) > 1023) {
    fprintf(stderr, "url too long %s\n", url);
    return 1;
  }
  char *data = calloc(1, strlen(url) + 1);
  memcpy(data, url, strlen(url));
  blist_append_data(q->ll, strlen(url) + 1, data);
  return 0;
}

void url_queue_clean(url_queue_t *q)
{
  if (q) {
    if (q->ll) {
      blist_clean(q->ll);
      q->ll = NULL
    }
    free(q);
    q = NULL;
  }
}
