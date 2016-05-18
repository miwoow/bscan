#ifndef _SPIDER_H_
#define _SPIDER_H_

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "urlqueue.h"

#define MAX_URL_LEN 1023

typedef struct _spider_s
{
  char root_url[MAX_URL_LEN+1];
  url_queue_t *urlq;
}spider_t;

spider_t* spider_init(char *url);
void spider_start(spider_t *sp);

#endif
