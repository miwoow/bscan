#ifndef _URL_QUEUE_H
#define _URL_QUEUE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "blist.h"

typedef struct _url_queue_s
{
  blist_t *ll;
}url_queue_t;

url_queue_t* url_queue_init();
int url_queue_add(url_queue_t *q, char *url);
size_t url_queue_elenum(url_queue_t *q);
void url_queue_clean(url_queue_t *q);


#endif
