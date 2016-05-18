#include "urlqueue.h"

static FILE *fp;

url_queue_t* url_queue_init()
{
  url_queue_t *q = (url_queue_t*)calloc(1, sizeof(url_queue_t));
  q->ll = blist_init(10);
  fp = fopen("/tmp/urls.ok", "w+");
  return q;
}

int url_queue_add(url_queue_t *q, char *url)
{
  if (strlen(url) > 1023) {
    fprintf(stderr, "url too long %s\n", url);
    return 1;
  }
  fputs(url, fp);
  fputs("\n", fp);
  fflush(fp);
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
      q->ll = NULL;
    }
    free(q);
    q = NULL;
  }
}

size_t url_queue_elenum(url_queue_t *q)
{
  return blist_elenum(q->ll);
}

char* url_queue_get(url_queue_t *q, size_t ind)
{
  blist_node_t *node = NULL;
  if (ind < url_queue_elenum(q) - 1) {
    node = blist_get(q->ll, ind);
    if (node)
      return node->data;
    else
      return NULL;
  }
  return NULL;
}

int url_queue_uniq_add(url_queue_t *q, char *url)
{
  blist_t *lst = q->ll;
  int i=0;
  blist_node_t *node;

  for (i=0; i<lst->index; i++) {
    node = lst->nodes + i;
    if (urlp_is_similar(url, node->data)) {
      return 0;
    }
  }
  url_queue_add(q, url);
  return 0;
}
