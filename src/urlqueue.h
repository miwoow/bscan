#ifndef _URL_QUEUE_H
#define _URL_QUEUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "blist.h"

typedef struct _url_queue_s
{
  blist_t *ll;
  size_t spider_index;
  size_t check_index;
}url_queue_t;

url_queue_t* url_queue_init();
int url_queue_add(url_queue_t *q, char *url);
size_t url_queue_elenum(url_queue_t *q);
void url_queue_clean(url_queue_t *q);
char* url_queue_get(url_queue_t *q, size_t ind);
int url_queue_uniq_add(url_queue_t *q, char *url);


#endif
