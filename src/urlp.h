#ifndef _URLP_H_
#define _URLP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _url_s
{
  char proto[16];
  char host[256];
  int port;
  char path[1024];
  char query[1024];
}url_t;

int urlp_parse(char *url, url_t *uobj);
int urlp_get_pre_path(char *url, char *host);
int urlp_is_similar(char *url1, char *url2);

#endif
