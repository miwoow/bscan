#ifndef _BSCAN_H_
#define _BSCAN_H_

#include "urlqueue.h"

#define MAX_URL_LEN 1023

struct struct_parts {
  char *access;
  char *host;
  char *absolute;
  char *relative;
  char *search;               /* treated normally as part of path */
  char *anchor;
};

typedef struct _spider_s
{
  char root_url[MAX_URL_LEN+1];
  char *root_url_buf;
  struct struct_parts root_url_obj;
  url_queue_t *urlq;
  char *cur_url;
}spider_t;

#endif
