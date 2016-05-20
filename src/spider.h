#ifndef _SPIDER_H_
#define _SPIDER_H_

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "bscan.h"
#include "urlqueue.h"


spider_t* spider_init(char *url);
void spider_start(spider_t *sp);

#endif
