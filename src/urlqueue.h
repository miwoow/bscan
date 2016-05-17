#ifndef _URL_QUEUE_H
#define _URL_QUEUE_H

typedef struct _url_queue_s
{
  
}url_queue_t;

url_queue_t *url_queue_init();
int url_queue_add(url_queue_t *q, char *url);
void url_queue_clean(url_queue_t *q);


#endif
