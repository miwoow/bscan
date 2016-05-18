#include "blist.h"
#include <string.h>

blist_t *blist_init(uint8_t step)
{
  blist_t *l = NULL;
  if (step > 0 && step < 254) {
    l = (blist_t *)calloc(1, sizeof(blist_t));
    l->nodes = (blist_node_t*)calloc(step, sizeof(blist_node_t));
    l->index = 0;
    l->num = step;
    l->step = step;
  }
  return l;
}

void blist_append_data(blist_t *l, size_t len, char *data)
{
  blist_node_t *cur;

  if (l->index >= l->num) {
    void *n_mem = calloc(l->num + l->step, sizeof(blist_node_t));
    memcpy(n_mem, l->nodes, l->num * sizeof(blist_node_t));
    free(l->nodes);
    l->num += l->step;
    l->nodes = (blist_node_t*)n_mem;
  }
  cur = l->nodes + l->index;
  (l->index)++;
  cur->data = data;
  cur->len = len;
}

void blist_clean(blist_t *l)
{
  int i=0;
  blist_node_t *cur;
  if (l) {
    if (l->nodes) {
      for (i=0; i< l->index; i++) {
	cur = l->nodes + i;
	if (cur->data) {
	  free(cur->data);
	  cur->data = NULL;
	}
      }
      free(l->nodes);
      l->nodes = NULL;
    }
    free(l);
    l = NULL;
  }
}

size_t blist_elenum(blist_t *l)
{
  return l->index + 1;
}
